/*
 * "sbfread.c"
 *
 *        SBF reading and parsing functions
 *
 * (c) 2000-2002 Septentrio nv/sa, Belgium
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "crc.h"
#include "sbfread.h"
#include "sbfsigtypes.h"
#include "ssnchacha.h"

/* size of the SBF header in bytes */
#define HEADER_SIZE        8

/* SBF sync bytes */
static const char SYNC_STRING[3]="$@";
static int intCRCErrors = 0;

/*---------------------------------------------------------------------------*/
bool IsTimeValid(void* SBFBlock)
/* Returns true if none of the TOW and WNc fields are set to its don't use
   value */
{
  return ((((HeaderAndTimeBlock_t*)SBFBlock)->TOW != 0xffffffffUL)  &&
          (((HeaderAndTimeBlock_t*)SBFBlock)->WNc != (uint16_t)0xffff) );
}


/*---------------------------------------------------------------------------*/
/* check whether a given epoch needs to be included in the ASCII file. 

   An epoch can be included in the ASCII file if the epoch time meets
   the following conditions:

   1) it is a multiple of the ForcedInterval_ms

   2) it is larger or equal than ForcedFirstEpoch_ms.  If
      ForcedFirstEpoch_ms is lower than 86400000, only the time-of-day
      is controlled, not the date.  If ForcedFirstEpoch_ms is
      FIRSTEPOCHms_DONTCARE, it is ignored.

   3) it is lower or equal than ForcedLastEpoch_ms.  If
      ForcedLastEpoch_ms is lower than 86400000, only the time-of-day
      is controlled, not the date.  If ForcedLastEpoch_ms is
      LASTEPOCHms_DONTCARE, it is ignored.
 */
bool IncludeThisEpoch(void*   SBFBlock,
                      int64_t ForcedFirstEpoch_ms,
                      int64_t ForcedLastEpoch_ms,
                      int     ForcedInterval_ms,
                      bool    AcceptInvalidTimeStamp)
{
  bool    ret = (AcceptInvalidTimeStamp || IsTimeValid(SBFBlock));
  int     TOW_ms     = (int)(((HeaderAndTimeBlock_t*)SBFBlock)->TOW);
  int64_t GPSTime_ms = (int64_t)(((HeaderAndTimeBlock_t*)SBFBlock)->WNc)
                       *(86400LL*7LL*1000LL)+TOW_ms;
  
  /* check interval */
  if (TOW_ms%ForcedInterval_ms != 0)
  {
    ret = false;
  }
  
  /* check the first epoch time */
  if (ForcedFirstEpoch_ms != FIRSTEPOCHms_DONTCARE)
  {
    if (ForcedFirstEpoch_ms < 86400000)
    {
      if (((int)TOW_ms%86400000)<ForcedFirstEpoch_ms)
      {
        ret = false;
      }
    }
    else if (GPSTime_ms < ForcedFirstEpoch_ms)
    {
      ret = false;
    }
  }

  /* check the last epoch time */
  if (ForcedLastEpoch_ms != LASTEPOCHms_DONTCARE)
  {
    if (ForcedLastEpoch_ms < 86400000)
    {
      if (((int)TOW_ms%86400000) > ForcedLastEpoch_ms)
      {
        ret = false;
      }
    }
    else if (GPSTime_ms > ForcedLastEpoch_ms)
    {
      ret = false;
    }
  }

  return ret;
}


/*---------------------------------------------------------------------------*/
void RemoveSubBlockPadding(void*  SBFBlock,
                           unsigned int    N,
                           size_t SourceSBSize,
                           size_t TargetSBSize)

/* This function should be called to remove the padding bytes in the
 * sub-blocks contained in the SBF block pointed to by SBFBlock.  N is
 * the number of sub-blocks in that SBF block and SourceSBSize is the
 * size of these sub-blocks.  TargetSBSize is the desired size of the
 * sub-block: in this function, only the first TargetSBSize bytes from
 * the SBF sub-blocks are kept, the others are discarded.
 *
 * This function must be called when decoding SBF blocks containing
 * one type of sub-blocks, in order to ensure compatibility with
 * possible SBF upgrades.
 */
{
  uint32_t Length, i;
  
  Length = ((HeaderBlock_t*)SBFBlock)->Length;
  
  for (i=0; i<N; i++) {
    
    memmove(&(((uint8_t*)SBFBlock)[Length - N*SourceSBSize + TargetSBSize*i]),
            &(((uint8_t*)SBFBlock)[Length - (N-i)*SourceSBSize]),
            TargetSBSize);
  }
}

/*---------------------------------------------------------------------------*/
off_t GetSBFFilePos(SBFData_t* SBFData)
/* Get the current SBF file pointer position in bytes from the
 * beginning of the file.  */
{

  return (off_t)ssnftell(SBFData->F);

}

/*---------------------------------------------------------------------------*/
off_t GetSBFFileLength(SBFData_t* SBFData)
/* Get the length of the SBF file in bytes.
 */
{

  off_t CurrentPos = ssnftell(SBFData->F);
  off_t FileLength;

  if (ssnfseek(SBFData->F, 0, SEEK_END) != 0)
    Terminate;

  FileLength = (off_t)ssnftell(SBFData->F);

  if (ssnfseek(SBFData->F, CurrentPos, SEEK_SET) != 0)
    Terminate;

  return FileLength;

}

/*--------------------------------------------------------------------------*/
int GetCRCErrors()
/* Returns the number of CRC errors present */
{
    return intCRCErrors;    
}


/*--------------------------------------------------------------------------*/
int32_t CheckBlock(SBFData_t* SBFData, uint8_t* Buffer)

/* Check that the validity of a tentative SBF block in the file. When
 * calling this function, Buffer[0] has to contain the '$' character
 * which identifies the start of the tentative SBF block, and the file
 * pointer has to point to the character just after this '$'
 * character.
 *
 * When this function returns and the tentative block is valid, the
 * file pointer points to the first byte following the just-found SBF
 * block, and Buffer contains the bytes of the SBF block. If the
 * tentative block is not valid, the file pointer is not changed, nor
 * the contents of Buffer.
 *
 * Arguments:
 *   *SBFData: a pointer to the SBFData as initialized by
 *             InitializeSBFDecoding;
 *   *Buffer:  on success, contains the SBF block. Otherwise not
 *             changed
 *
 * Return:
 *    0   if the tentative block is indeed a valid SBF block. In this
 *        case the file pointer is moved to the byte just following
 *        the SBF block, and the SBF block is returned in the Buffer
 *        argument.
 *   -1   if the tentative block is not a valid SBF block. In
 *        this case the file pointer is not changed, neither SBFBlock.
 */
{
  VoidBlock_t* VoidBlock = (VoidBlock_t*)Buffer;
  off_t InitialFilePos;

  /* Remember the current file pointer to return there if needed */
  InitialFilePos = ssnftell(SBFData->F);

  /* Read the block header, remember that the first '$' is already
   * present in Buffer[0]. */
  if (fread(&Buffer[1], 1, HEADER_SIZE-1, SBFData->F) != HEADER_SIZE-1) {

    /* If the read could not be performed, we are probably at the end
     * of the file, go back to the initial file position and return
     * -1 */
    if (ssnfseek(SBFData->F, InitialFilePos, SEEK_SET) != 0)
      Terminate;

    return -1;
  }

  /* Check the block header parameters. If not valid, go back to the
   * initial file position and return -1. */
  if ((VoidBlock->Sync !=
       ((uint16_t)SYNC_STRING[0] | (uint16_t)SYNC_STRING[1]<<8)) || 
#if (MAX_SBFSIZE<65535)
      (VoidBlock->Length   > MAX_SBFSIZE)                        ||   
#endif
      (VoidBlock->Length   < sizeof(HeaderAndTimeBlock_t))) 
  {
    
    if (ssnfseek(SBFData->F, InitialFilePos, SEEK_SET) != 0)
      Terminate;

    return -2;
  }

  /* Fetch the block body */
  if ((uint16_t)fread(&Buffer[HEADER_SIZE], 1, VoidBlock->Length-HEADER_SIZE,
            SBFData->F) != VoidBlock->Length - HEADER_SIZE) {

    /* If the read could not be performed, we are probably at the end
     * of the file, return to the initial file position and return
     * -1 */
    if (ssnfseek(SBFData->F, InitialFilePos, SEEK_SET) !=0)
      Terminate;

    return -3;
  }

  /* Check the CRC field */
  if (CRCIsValid(Buffer) == false){
    /* Increase the number of CRC errors */
    intCRCErrors++;
    /* If CRC not valid, go back to the initial file position and
     * return -1. */
    if (ssnfseek(SBFData->F, InitialFilePos, SEEK_SET) !=0)
      Terminate;

    return -4;
  }

  /* Handle decryption */
  if (SBF_ID_TO_NUMBER(VoidBlock->ID) == sbfnr_ReceiverSetup_1 &&
      VoidBlock->Length >= sizeof(ReceiverSetup_1_0_t) )
  {
    /* All other versions of ReceiverSetup are compatible */
    ReceiverSetup_1_0_t *ReceiverSetup = (ReceiverSetup_1_0_t*) VoidBlock;
    SetSBFDecryptionKeyFromFile(SBFData, ReceiverSetup->RxSerialNbr);
  }
  else if (VoidBlock->ID == sbfid_MeasEpoch_2_1 &&
           VoidBlock->Length >= offsetof(MeasEpoch_2_1_t, Data) &&
           SBFData->has_key)
  {
    MeasEpoch_2_1_t *MeasEpoch = (MeasEpoch_2_1_t*) VoidBlock;
    (void)DecryptMeasEpoch(MeasEpoch, SBFData->key);
  }

  return 0;

}


/*--------------------------------------------------------------------------*/
int32_t GetNextBlock(SBFData_t* SBFData, void* SBFBlock,
                     uint16_t BlockNumber1, 
                     uint16_t BlockNumber2, 
                     uint32_t FilePos)

/* Scans the SBF file forward to find the next block having one of the
 * requested block numbers (the block number is coded in the 13 LSB of
 * the ID field). If such a block can be found, read it into
 * SBFBlock. If no block can be found with the required numbers, the
 * contents of SBFBlock is not modified.
 *
 * Arguments:
 *   *SBFData: a pointer to the SBFData as initialized by
 *             InitializeSBFDecoding
 *
 *   *SBFBlock: on success, contains the SBF block. Otherwise not
 *              changed
 *
 *   BlockNumber1 & BlockNumber2: the two possible block numbers this
 *            function is looking for. To search only one
 *            particular block number, set the two numbers to the same
 *            value.  If at least one of these arguments is
 *            BLOCKNUMBER_ALL, the function searches the next block,
 *            whatever its number.
 *
 *   FilePos: by default (if FilePos is set to 0), the SBF
 *            file is scanned from the current file position, and the
 *            file pointer is set to the first byte after the block
 *            header if a SBF block is found, or is kept unchanged if
 *            none is found. FilePos is used to change this behavior:
 *            - the start position for the search is either
 *              START_POS_CURRENT (default) or START_POS_SET depending
 *              on the search has to start from the current file
 *              pointer or from the beginning of the file;
 *            - the file position if no block found is always
 *              unchanged. If a valid SBF block is found, the end
 *              position is set according to the following value in
 *              FilePos:
 *                END_POS_AFTER_BLOCK: (default) the file position is
 *                    set at the first byte after the valid SBF block.
 *                END_POS_DONT_CHANGE: the file position is kept
 *                    unchanged by the function, even if a block is
 *                    found.
 *            The start position and end position can be ORed.
 *
 * Return:
 *    0  if a block having one of the two numbers has been found.
 *       In this case, the SBF block is returned in the SBFBlock argument
 *   -1  if no block could be found.
 */
{
  bool     BlockFound;
  off_t    InitialFilePos;
  union
  {
    VoidBlock_t VoidBlock; /* used to align the buffer data */
    uint8_t     Data[MAX_SBFSIZE];
  } Buffer;

  int c;

  BlockFound = false;

  /* Remember the current file position */
  InitialFilePos = ssnftell(SBFData->F);

  /* Do we have to start searching from the beginning of the file, or
   * from the current file pointer? */
  if ((FilePos & START_POS_FIELD) == START_POS_SET)
    if (ssnfseek(SBFData->F, 0, SEEK_SET) != 0)
      Terminate;

  do {
    /* Read the next character in the file */
    c = fgetc(SBFData->F);

    /* If it is '$', check if this is the first byte of a valid
     * block. */
    if (c==(int)SYNC_STRING[0]) {

      /* The '$' may be the first character of a valid SBF block. */
      Buffer.Data[0] = (uint8_t)c;

      /* Check if the file pointer is pointing to a valid SBF block. */
      if ((CheckBlock(SBFData, Buffer.Data) == 0) &&
          ((BlockNumber1 == BLOCKNUMBER_ALL)     ||
           (BlockNumber1 == SBF_ID_TO_NUMBER(Buffer.VoidBlock.ID)) ||
           (BlockNumber2 == BLOCKNUMBER_ALL)     ||
           (BlockNumber2 == SBF_ID_TO_NUMBER(Buffer.VoidBlock.ID)))
          ) {

        /* Valid block found, remember it. */
        BlockFound = true;

        /* Copy the block contents to the SBFBlock pointer. */
        memcpy(SBFBlock, Buffer.Data, (size_t)(Buffer.VoidBlock.Length));

      }
    }

  } while ((c != EOF) && (BlockFound == false));

  /* If the file position has to be maintained, or no block was found,
   * set the file pointer to its original value. */
  if (((FilePos & END_POS_FIELD) == END_POS_DONT_CHANGE)
      || (BlockFound == false)) {
    if (ssnfseek(SBFData->F, InitialFilePos, SEEK_SET) != 0)
      Terminate;
  }

  /*@-mustdefine@*/
  return (BlockFound) ? 0 : -1;
  /*@=mustdefine@*/

}


/*---------------------------------------------------------------------------*/
void InitializeSBFDecoding(char *FileName,
                           SBFData_t* SBFData)

/* Initialize the reading of a SBF file, and prepare the SBFData_t
 * structure which is used by most of the functions in this file.
 *
 * Arguments:
 *   *FileName: The name of the SBF file which has to be read.
 *
 *   *SBFData:  A pointer to a SBFData_t structure. The fields
 *              in this structure are initialized by this function.
 *              The FirstSec, LastSec and Interval fields of SBFData
 *              are set to -1.0 if irrelevant (i.e. when no
 *              measurement epoch is found in the file, or only one)
 *
 * Return : none
 */

{
  intCRCErrors = 0;
  /* Open the SBF file in read/binary mode. */
  if ((SBFData->F = fopen(FileName, "rb")) == NULL)
    Terminate;

  memset(SBFData->key, 0, sizeof(SBFData->key));
  SBFData->has_key = false;

  return;
}

void SetSBFDecryptionKey(SBFData_t* SBFData,
            /*@unique@*/ const uint8_t *key)
{
  memcpy(SBFData->key, key, sizeof(SBFData->key));
  SBFData->has_key = true;
}

void SetSBFDecryptionKeyFromFile(SBFData_t* SBFData,
                   /*@unique@*/  const char* RxSerialNbr)
{
  const char *keyfile = getenv("SSN_RECEIVER_KEY_FILE");

  if (keyfile != NULL)
  {
    FILE *keys = fopen(keyfile, "r");
    if (keys != NULL)
    {
      while (feof(keys) == 0 && ferror(keys) == 0)
      {
        char serialNbr[21];
        char hexkey[65];
        if (fscanf(keys, "%20s %64[0-9a-fA-F]\n", serialNbr, hexkey) == 2)
        {
          if (strncmp(serialNbr, RxSerialNbr, 20) == 0)
          {
            /* Found key, use it and terminate */
            uint8_t key[32];
            int i;
            for (i = 0; i < 32; i++)
            {
              unsigned digit;
              if (sscanf(&hexkey[2*i], "%2x", &digit) == 1)
              {
                key[i] = (uint8_t)digit;
              }
              else
              {
                break;
              }
            }
            /* Sanity check: all digits were scanned */
            if (i == 32)
            {
              SetSBFDecryptionKey(SBFData, key);
            }
          }
        }
        else
        {
          /* Discard input until EOL */
          int c = 0;
          while (c != '\n' && c != EOF)
          {
            c = getc(keys);
          }
        }
      }
      (void)fclose(keys);
    }
  }
}


/*---------------------------------------------------------------------------*/
void CloseSBFFile(SBFData_t* SBFData)
{
  /* Close the SBF file. */
  if (fclose(SBFData->F) !=0)
    Terminate;

}


/*---------------------------------------------------------------------------*/
/* The purpose of the following functions is to help decoding the
 * MeasEpoch_2 and GenMeasEpoch_1 blocks.  Below is a sample code
 * illustrating how to use these functions to print all the main
 * antenna CA pseudoranges from a MeasBlock.  Note: in this piece of
 * code, MeasEpoch is a pointer to a MeasEpoch_2 or GenMeasEpoch_1 SBF block.  

   {
     MeasEpochChannelType1_t* Type1SubBlock;

     Type1SubBlock = GetFirstType1SubBlock(MeasEpoch);

     while (Type1SubBlock != NULL) {

       double  PR, Carrier, Doppler, CN0, LockTime;
       bool    HalfCycleFlag;

       GetMeasEpochObservables(signalType | Antenna <<5,
                             MeasEpoch,
                             Type1SubBlock,
                             &PR,
                             &Carrier,
                             &Doppler,
                             &CN0,
                             &LockTime,
                             &HalfCycleFlag);
       printf("%f ", PR);
       Type1SubBlock = GetNextType1SubBlock(MeasEpoch,
                                            Type1SubBlock);
     }
   }
*/
/*---------------------------------------------------------------------------*/

static int Type1Counter = 0;

/*---------------------------------------------------------------------------*/
MeasEpochChannelType1_t*
GetFirstType1SubBlock(MeasEpoch_2_t *MeasEpoch)
/* returns a pointer to the first type-1 sub-block of a MeasEpoch SBF block.
 *
 * Arguments:
 *   *MeasEpoch: a pointer to a MeasEpoch_2 or GenMeasEpoch_1 SBF block
 *
 * Return : a pointer to the first type-1 sub-block, or NULL if there is
 *          no sub-block in this MeasEpoch
 */
{
  Type1Counter = 0;
  if (MeasEpoch->N != 0) {
    return (MeasEpochChannelType1_t*)(MeasEpoch->Data);
  } else {
    return NULL;
  }
}

/*---------------------------------------------------------------------------*/
MeasEpochChannelType1_t*
GetNextType1SubBlock(MeasEpoch_2_t           *MeasEpoch,
                     MeasEpochChannelType1_t *CurrentType1SubBlock)
/* returns a pointer to the next type-1 sub-block of a MeasEpoch_2 SBF block.
 *
 * Arguments:
 *   *MeasEpoch: a pointer to a MeasEpoch_2 or GenMeasEpoch_1 SBF block
 *
 *   *CurrentType1SubBlock: a pointer to a type-1 sub-block in the
 *          MeasEpoch.  The function will return a pointer to the type-1
 *          sub-block following the one pointed to by this argument.
 *
 * Return : a pointer to the next type-1 sub-block, or NULL if there is
 *          no next sub-block in this MeasEpoch (i.e. CurrentType1SubBlock
 *          points to the last type-1 sub-block of the MeasEpoch).
 */
{
  if (++Type1Counter < MeasEpoch->N) {
    return (MeasEpochChannelType1_t*)
      ((uint8_t*)CurrentType1SubBlock
       + CurrentType1SubBlock->N_Type2*MeasEpoch->SB2Size
       + MeasEpoch->SB1Size);
  } else {
    return NULL;
  }

}


/*---------------------------------------------------------------------------*/
static MeasEpochChannelType2_t*
SearchType2SubBlock(MeasEpochChannelType1_t *Type1SubBlock,
                    uint32_t                 SB1Size,
                    uint32_t                 SB2Size,
                    uint8_t                  Type)
/* returns a pointer to the type-2 sub-block with a given Type.
 *
 * Arguments:

 *   *Type1SubBlock: a pointer to a type-1 sub-block in the
 *        MeasEpoch.  The function will return a pointer to the
 *        type-2 sub-block dependent on this type-1 sub-block, and of
 *        which the Type matches the Type argument.
 *
 *   SB1Size : size in byte of a type-1 sub-block
 *
 *   SB2Size : size in byte of a type-2 sub-block
 *
 *   Type: the type of type-2 sub-block we are looking for.
 *
 * Return : a pointer to the desired type-2 sub-block, or NULL if there is
 *          no type-2 sub-block corresponding to the given Type.
 */
{
  MeasEpochChannelType2_t* ret = NULL;
  uint32_t i;

  for (i=0; i<Type1SubBlock->N_Type2; i++) {
    MeasEpochChannelType2_t* SubChannel = (MeasEpochChannelType2_t*)
      ((uint8_t*)Type1SubBlock + SB1Size + i*SB2Size);

    if (SubChannel->Type == Type) {
      ret = SubChannel;
      break;
    }
  }

  return ret;
}


/*---------------------------------------------------------------------------*/
double GetWavelength(uint8_t Type, int GLOfn)
/* returns the carrier wavelength corresponding to a given Type field
 * in a MeasEpoch sub-block.
 *
 * Arguments:
 *   Type: the Type field as provided in the type-1 or type-2 sub-blocks.
 *
 *   GLOfn: GLONASS frequency number (from -7 to 12).  This argument
 *          is ignored for non-GLONASS signals.
 *
 */
{
  double wavelength;

  switch (Type&0x1f)
  {
    case L1CA:
    case L1P:
    case L1A:
    case L1BC:
    case L1GEO:
    case L1CAQZS :
      wavelength = L1WAVELENGTH;
      break;
    case L2P:
    case L2C:
    case L2CQZS :
      wavelength = L2WAVELENGTH;
      break;
    case E5:
      wavelength = E5WAVELENGTH;
      break;
    case E5a:
      wavelength = E5aWAVELENGTH;
      break;
    case E5b:
    case E5bCMP:
      wavelength = E5bWAVELENGTH;
      break;
    case E6BC:
    case E6A:
      wavelength = E6WAVELENGTH;
      break;
    case L5:
    case L5GEO:
    case L5QZS:
    case L5IRNSS:
      wavelength = L5WAVELENGTH;
      break;
    case E2CMP:
      wavelength = E2WAVELENGTH;
      break;
    case B3CMP:
      wavelength = B3WAVELENGTH;
      break;
    case L1CAGLO:
    case L1PGLO:
      wavelength = c84/(L1GLOFREQ+GLOfn*562500);
      break;
    case L2CAGLO:
    case L2PGLO:
      wavelength = c84/(L2GLOFREQ+GLOfn*437500);
      break;
    case L3GLO:
      wavelength = L3WAVELENGTH;
      break;
    default:
      wavelength = L1WAVELENGTH;
      break;
  }
  return(wavelength);
}

/*---------------------------------------------------------------------------*/
static int32_t ExtendSignBit(uint32_t x, uint32_t N)
/* extend the sign bit of a 2's complement N-bit integer
 *
 * Arguments:
 *   x:  the N-bit integer in two's complement
 *
 *   N:  the size of the integer in bits
*/
{
  if ((x & (1<<(N-1))) == 0) {
    /* the sign bit is 0, clear all the bits that are not part of a
       N-bit integer */
    return x & ((1<<N)-1);
  } else {
    /* the sign bit is 1, set all the bits that are not part of a
       N-bit integer */
    return x | (~((1<<N)-1));
  }
}

/*---------------------------------------------------------------------------*/
bool GetMeasEpochObservables(uint8_t   Type,
                             MeasEpoch_2_t           *MeasEpoch,
                             MeasEpochChannelType1_t *Type1SubBlock,
                             double    *PR,
                             double    *Carrier,
                             double    *Doppler,
                             double    *CN0,
                             double    *LockTime,
                             bool      *HalfCycleAmbiguityFlag)
/* Extract measurements from a MeasEpoch_2 SBF block.
 *
 * Arguments:
 *      Type:  the measurement type that needs to be
 *             extracted. The definition of Type corresponds to the
 *             definition of the Type field in the MeasEpoch_2
 *             structure: it is the OR of one of the observation types
 *             listed in the MeasType_t enumeration in "sbfdef.h",
 *             and the Antenna ID shifted 5 bits to the left.  For
 *             instance, if Type is "L1CA + 1<<5", the
 *             function will decode the GPS CA measurements from the first
 *             auxiliary antenna (Aux1), if any.
 *
 *  *MeasEpoch: a pointer to a MeasEpoch_2 or GenMeasEpoch_1 SBF block
 *
 *  *Type1SubBlock: a pointer to a type-1 sub-block in the
 *        MeasEpoch. The data will be extracted from either this type-1
 *        sub-block, or from one of its type-2 daughters.
 *
 *  *PR:        the extracted pseudorange, in meters, or F64_NOTVALID
 *
 *  *Carrier:   the extracted carrier phase, in cycles, or F64_NOTVALID
 *
 *  *Doppler:   the extracted Doppler, in Hz, or F64_NOTVALID
 *
 *  *CN0:       the extracted C/N0, in dB-Hz, or F64_NOTVALID
 *
 *  *LockTime:  the extracted lock time, in seconds, or F64_NOTVALID
 *
 *  *HalfCycleAmbiguityFlag: true when the half-cycle ambiguity flag is set.
 *
 *  Return: true if at least one of *PR, *Carrier, *Doppler, *CN0 or
 *  *LockTime is not set to its NOTVALID value.  False otherwise.  The
 *  return value can be used as a quick check of data availability: if
 *  the function returns false, the MeasEpoch SBF block does not
 *  contain any data of the requested type.
 */
{
  MeasEpochChannelType2_t    *Type2SubBlock;
  double                      Wavelength1;
  bool                        ret = false;

  /* carrier wavelength for the type-1 block */
  Wavelength1 = GetWavelength(Type1SubBlock->Type, 
                              (int)(Type1SubBlock->ObsInfo>>3)-8);
  
  /* pseudorange from the type-1 block */
  if ( ((Type1SubBlock->Misc&0xf) == 0) && (Type1SubBlock->CodeLSB == 0) ) {
    *PR = F64_NOTVALID;
  } else {
    *PR = (Type1SubBlock->Misc&0xf)*4294967.296+Type1SubBlock->CodeLSB*0.001;
    ret = true;
  }

  /* Doppler from the type-1 block */
  if (Type1SubBlock->Doppler == (int32_t)0x80000000) {
    *Doppler    = F64_NOTVALID;
  } else {
    *Doppler    = Type1SubBlock->Doppler*0.0001;
    ret = true;
  }

  if (SBF_ID_TO_NUMBER(MeasEpoch->Header.ID) == sbfnr_GenMeasEpoch_1)
  {
    Type &= 0xe7;
  }
  
  /* if the measurements are contained in the type-1 sub-block, decode
   * them directly.  */
  if (Type1SubBlock->Type == Type) {

    /* PR and Doppler are already decoded */

    /* carrier phase */
    if ((Type1SubBlock->CarrierLSB == 0)  &&
        (Type1SubBlock->CarrierMSB == (int8_t)0x80)){
      *Carrier = F64_NOTVALID;
    } 
    else 
    {
      *Carrier = *PR/Wavelength1
        +(Type1SubBlock->CarrierMSB*65536+Type1SubBlock->CarrierLSB)/1000.0;
    }

    /* CN0 */
    if (Type1SubBlock->CN0 == (uint8_t)255) {
      *CN0 = F64_NOTVALID;
    } else {
      if ( ((Type1SubBlock->Type&0x1f) != L1P)   &&
           ((Type1SubBlock->Type&0x1f) != L2P)  ){
        *CN0      =  (double)(Type1SubBlock->CN0/4.0+10.0);
      } else {
        *CN0      =  (double)(Type1SubBlock->CN0/4.0);
      }
      ret = true;
    }

    if (Type1SubBlock->LockTime == 65535) {
      *LockTime = F64_NOTVALID;
    } else {
      *LockTime = (double)Type1SubBlock->LockTime;
    }
    
    /* Report the half-cycle ambiguity flag (only available in MeasEpoch v 2.0) */
    *HalfCycleAmbiguityFlag = ((SBF_ID_TO_NUMBER(MeasEpoch->Header.ID) == sbfnr_MeasEpoch_2) && 
                               ((Type1SubBlock->ObsInfo&4)             != 0));
    
  } else {
    /* Search for the type-2 sub-block containing the measurements, if any */
    Type2SubBlock = SearchType2SubBlock(Type1SubBlock,
                                        MeasEpoch->SB1Size,
                                        MeasEpoch->SB2Size,
                                        Type);

    if (Type2SubBlock != NULL) {
      double Wavelength2 = GetWavelength(Type2SubBlock->Type,
                                         (int)(Type1SubBlock->ObsInfo>>3)-8);
      int32_t CodeOffsetMSB
        = ExtendSignBit(Type2SubBlock->OffsetsMSB, 3);
      int32_t  DopplerOffsetMSB
        = ExtendSignBit(Type2SubBlock->OffsetsMSB>>3, 5);

      /* pseudorange.  Note: if this field is not set to its
         Do-Not-Use value, then the pseudorange in the type-1
         sub-block is necessarily valid, so we don't need to check it */
      if ((Type2SubBlock->CodeOffsetLSB == 0 ) &&
          (CodeOffsetMSB                == -4)){
        *PR = F64_NOTVALID;
      } else {
        *PR += (CodeOffsetMSB*65536 + Type2SubBlock->CodeOffsetLSB)*0.001;
      }

      /* carrier phase */
      if ((Type2SubBlock->CarrierLSB == 0)  &&
          (Type2SubBlock->CarrierMSB == (int8_t)0x80)){
        *Carrier = F64_NOTVALID;
      } else {
        *Carrier = *PR/Wavelength2
          +(Type2SubBlock->CarrierMSB*65536+Type2SubBlock->CarrierLSB)*0.001;
      }

      /* L2 Doppler */
      if ((Type2SubBlock->DopplerOffsetLSB == 0   ) &&
          (DopplerOffsetMSB                == -16)) {
        *Doppler = F64_NOTVALID;
      } else {
        *Doppler =
          *Doppler*Wavelength1/Wavelength2
          +(DopplerOffsetMSB*65536+Type2SubBlock->DopplerOffsetLSB)*0.0001;
      }

      /* P2 CN0 */
      if (Type2SubBlock->CN0 == (uint8_t)255) {
        *CN0 = F64_NOTVALID;
      } else {
        if ( ((Type2SubBlock->Type&0x1f) != L1P) &&
             ((Type2SubBlock->Type&0x1f) != L2P) ){
          *CN0      =  (double)(Type2SubBlock->CN0/4.0+10.0);
        } else {
          *CN0      =  (double)(Type2SubBlock->CN0/4.0);
        }
        ret = true;
      }

      if (Type2SubBlock->LockTime == 255) {
        *LockTime = F64_NOTVALID;
      } else {
        *LockTime = (double)Type2SubBlock->LockTime;
      }

      /* Report the half-cycle ambiguity flag (only available in MeasEpoch v 2.0) */
      *HalfCycleAmbiguityFlag = ((SBF_ID_TO_NUMBER(MeasEpoch->Header.ID) == sbfnr_MeasEpoch_2) && 
                                 ((Type2SubBlock->ObsInfo&4)             != 0));
      
    } else {
      /* no sub-block containing the requested data set, set all values to
         their "Do-Not-Use" value */
      *PR       = F64_NOTVALID;
      *Carrier  = F64_NOTVALID;
      *Doppler  = F64_NOTVALID;
      *CN0      = F64_NOTVALID;
      *LockTime = F64_NOTVALID;
      *HalfCycleAmbiguityFlag = false;
      ret        = false;
    }

  }

  return ret;
}


static double  PR_Type1;
static double  Doppler_Type1;
static uint8_t Type2Cnt;
static double  Wavelength1;

/*---------------------------------------------------------------------------*/
void GetObsFromType1(MeasEpoch_2_t           *MeasEpoch,
                     MeasEpochChannelType1_t *Type1SubBlock,
                     uint8_t   *Type,
                     double    *PR,
                     double    *Carrier,
                     double    *Doppler,
                     float     *CN0,
                     uint32_t  *LockTime,
                     bool       OnlyIncludeFullAmbiguityPhase)
/* Extract measurements from a Type-1 sub-block.
 *
 * Arguments:
 *
 *  *MeasEpoch: a pointer to a MeasEpoch_2 or GenMeasEpoch_1 SBF block
 *
 *  *Type1SubBlock: a pointer to a type-1 sub-block in the
 *        MeasEpoch. The data will be extracted from this type-1
 *        sub-block.
 *
 *  *Type:      the Type field of the type-1 sub-block
 *
 *  *PR:        the extracted pseudorange, in meters, or F64_NOTVALID
 *
 *  *Carrier:   the extracted carrier phase, in cycles, or F64_NOTVALID
 *
 *  *Doppler:   the extracted Doppler, in Hz, or F64_NOTVALID
 *
 *  *CN0:       the extracted C/N0, in dB-Hz, or F32_NOTVALID
 *
 *  *LockTime:  the extracted lock time, in seconds, or 0xffffffff
 *
 *   OnlyIncludeFullAmbiguityPhase: if true, carrier phases with unresolved 
 *              pi ambiguity are set to F64_NOTVALID
 *
 *
 *  Note: the data in the subsequent type-2 sub-blocks can be read by
 *  the function GetNextObsFromType2().
 */
{
  /* compute the carrier wavelength */
  Wavelength1 = GetWavelength(Type1SubBlock->Type, 
                              (int)(Type1SubBlock->ObsInfo>>3)-8);
  
  if ((SBF_ID_TO_NUMBER(MeasEpoch->Header.ID) == sbfnr_GenMeasEpoch_1) &&
      (Type1SubBlock->SVID >= 120UL && Type1SubBlock->SVID <= 140UL))
  {
    *Type = L1GEO | (Type1SubBlock->Type&0xe0);
  }
  else
  {
    *Type = Type1SubBlock->Type;
  }

  /* pseudorange */
  if ( ((Type1SubBlock->Misc&0xf) == 0) && (Type1SubBlock->CodeLSB == 0) ) {
    *PR = F64_NOTVALID;
  } else {
    *PR = (Type1SubBlock->Misc&0xf)*4294967.296+Type1SubBlock->CodeLSB*0.001;
  }
  PR_Type1 = *PR;

  /* Doppler */
  if (Type1SubBlock->Doppler == (int32_t)0x80000000) {
    *Doppler    = F64_NOTVALID;
  } else {
    *Doppler    = Type1SubBlock->Doppler*0.0001;
  }
  Doppler_Type1 = *Doppler;

  /* carrier phase */
  if ((Type1SubBlock->CarrierLSB == 0)  &&
      (Type1SubBlock->CarrierMSB == (int8_t)0x80)){
    *Carrier = F64_NOTVALID;
  } else {
    *Carrier = *PR/Wavelength1
      +(Type1SubBlock->CarrierMSB*65536+Type1SubBlock->CarrierLSB)/1000.0;
  }

  /* CN0 */
  if (Type1SubBlock->CN0 == (uint8_t)255) {
    *CN0 = F32_NOTVALID;
  } else {
    if ( ((Type1SubBlock->Type&0x1f) != L1P)   &&
         ((Type1SubBlock->Type&0x1f) != L2P)  ){
      *CN0      =  (float)(Type1SubBlock->CN0/4.0+10.0);
    } else {
      *CN0      =  (float)(Type1SubBlock->CN0/4.0);
    }
  }

  if (Type1SubBlock->LockTime == 65535) {
    *LockTime = 0xffffffff;
  } else {
    *LockTime = Type1SubBlock->LockTime;
  }
  
  /* in SBF 2.0, if the half-cycle ambiguity flag is set, discard
   * the carrier phase measurement */
  if ((SBF_ID_TO_NUMBER(MeasEpoch->Header.ID) == sbfnr_MeasEpoch_2) && 
      ((Type1SubBlock->ObsInfo&4) != 0)                             &&
      OnlyIncludeFullAmbiguityPhase ) 
  {
    *Carrier  = F64_NOTVALID;
    *LockTime = 0xffffffff;
  }
  
  Type2Cnt = 0;
}


/*---------------------------------------------------------------------------*/
void GetNextObsFromType2(MeasEpoch_2_t           *MeasEpoch,
                         MeasEpochChannelType1_t *Type1SubBlock,
                         uint8_t   *Type,
                         double    *PR,
                         double    *Carrier,
                         double    *Doppler,
                         float     *CN0,
                         uint32_t  *LockTime,
                         bool       OnlyIncludeFullAmbiguityPhase)
/* Extract measurements from the next type-2 sub-block (if any).  The
 * function GetObsFromType1() must be called prior to calling this
 * function.
 *
 * Arguments:
 *  *MeasEpoch: a pointer to a MeasEpoch_2 or GenMeasEpoch_1 SBF block
 *
 *  *Type1SubBlock: a pointer to a type-1 sub-block in the
 *        MeasEpoch. The data will be extracted from one of the type-2 
 *        sub-blocks depending on this type-1 sub-block.
 *
 *  *Type:      the Type field of the type-1 sub-block
 *
 *  *PR:        the extracted pseudorange, in meters, or F64_NOTVALID
 *
 *  *Carrier:   the extracted carrier phase, in cycles, or F64_NOTVALID
 *
 *  *Doppler:   the extracted Doppler, in Hz, or F64_NOTVALID
 *
 *  *CN0:       the extracted C/N0, in dB-Hz, or F32_NOTVALID
 *
 *  *LockTime:  the extracted lock time, in seconds, or 0xffffffff
 *
 *   OnlyIncludeFullAmbiguityPhase: if true, carrier phases with unresolved 
 *              pi ambiguity are set to F64_NOTVALID
 *
 */
{
  /* if there are still type-2 sub-blocks to read, proceed*/
  if (Type2Cnt < Type1SubBlock->N_Type2)
  {
    MeasEpochChannelType2_t *Type2SubBlock
      = (MeasEpochChannelType2_t*)
      ((uint8_t*)Type1SubBlock 
       + MeasEpoch->SB1Size + Type2Cnt*MeasEpoch->SB2Size);
  
    double Wavelength2 = GetWavelength(Type2SubBlock->Type,
                                       (int)(Type1SubBlock->ObsInfo>>3)-8);
    int32_t CodeOffsetMSB
      = ExtendSignBit(Type2SubBlock->OffsetsMSB, 3);
    int32_t  DopplerOffsetMSB
      = ExtendSignBit(Type2SubBlock->OffsetsMSB>>3, 5);

    Type2Cnt++;

    *Type = Type2SubBlock->Type;

    /* pseudorange.  Note: if this field is not set to its
       Do-Not-Use value, then the pseudorange in the type-1
       sub-block is necessarily valid, so we don't need to check it */
    if ((Type2SubBlock->CodeOffsetLSB == 0 ) &&
        (CodeOffsetMSB                == -4)){
      *PR = F64_NOTVALID;
    } else {
      *PR = PR_Type1+(CodeOffsetMSB*65536 + Type2SubBlock->CodeOffsetLSB)*1e-3;
    }
    
    /* carrier phase */
    if ((Type2SubBlock->CarrierLSB == 0)  &&
        (Type2SubBlock->CarrierMSB == (int8_t)0x80)){
      *Carrier = F64_NOTVALID;
    } else {
      *Carrier = *PR/Wavelength2
        +(Type2SubBlock->CarrierMSB*65536+Type2SubBlock->CarrierLSB)*0.001;
    }
    
    /* L2 Doppler */
    if ((Type2SubBlock->DopplerOffsetLSB == 0   ) &&
        (DopplerOffsetMSB                == -16)) {
      *Doppler = F64_NOTVALID;
    } else {
      *Doppler =
        Doppler_Type1*Wavelength1/Wavelength2
        +(DopplerOffsetMSB*65536+Type2SubBlock->DopplerOffsetLSB)*0.0001;
    }
    
    /* P2 CN0 */
    if (Type2SubBlock->CN0 == (uint8_t)255) {
      *CN0 = F32_NOTVALID;
    } else {
      if ( ((Type2SubBlock->Type&0x1f) != L1P) &&
           ((Type2SubBlock->Type&0x1f) != L2P) ){
        *CN0      =  (float)(Type2SubBlock->CN0/4.0+10.0);
      } else {
        *CN0      =  (float)(Type2SubBlock->CN0/4.0);
      }
    }

    if (Type2SubBlock->LockTime == 255) {
      *LockTime = 0xffffffff;
    } else {
      *LockTime = Type2SubBlock->LockTime;
    }
    
    /* in SBF 2.0, if the half-cycle ambiguity flag is set, discard
     * the carrier phase measurement */
    if ((SBF_ID_TO_NUMBER(MeasEpoch->Header.ID) == sbfnr_MeasEpoch_2) && 
        ((Type2SubBlock->ObsInfo&4)    != 0)                          &&
        OnlyIncludeFullAmbiguityPhase )
    {
      *Carrier  = F64_NOTVALID;
      *LockTime = 0xffffffff;
    }
    
  } 
  else 
  {
    /* no more sub-blocks to be read.  Set all values to
       their "Do-Not-Use" value */
    *Type     = 0;
    *PR       = F64_NOTVALID;
    *Carrier  = F64_NOTVALID;
    *Doppler  = F64_NOTVALID;
    *CN0      = F32_NOTVALID;
    *LockTime = 0xffffffff;
  }
  
}


/*---------------------------------------------------------------------------*/
uint32_t GetMeasEpochSVID(MeasEpochChannelType1_t *Type1SubBlock)
/* returns the SVID from a type-1 sub-block of a MeasEpoch */
{
  return (uint32_t)Type1SubBlock->SVID;
}

/*---------------------------------------------------------------------------*/
uint32_t GetMeasEpochRXChannel(MeasEpochChannelType1_t *Type1SubBlock)
/* returns the logical receiver channel ID from a type-1 sub-block of a
 * MeasEpoch */
{
  return (uint32_t)Type1SubBlock->RXChannel;
}


/*---------------------------------------------------------------------------*/
uint32_t GetSignalListInType1(MeasEpoch_2_t           *MeasEpoch,
                              MeasEpochChannelType1_t *Type1SubBlock,
                              uint32_t                 AntennaID)
{
/* Returns the list of signal types for which measurements are
 * available in a Type-1 and dependent Type-2 blocks.  The list is
 * given in the form of a bit field, where bit i is set if signal type
 * i is present in the epoch (the index of a given signal is given in
 * the SignalType_t enumeration).
 *
 * Arguments: 
 *   *Type1SubBlock: a pointer to a MeasEpochChannelType1_t
 *                   type-1 sub-block
 */
  uint32_t i;
  uint32_t ret = 0;
  
  /* the Antenna ID is from 0 in the MeasEpoch, and not from 1 */
  AntennaID--;
  
  /* SBF 1.0 had the same type for GPS L1CA and SBAS L1CA.
     Compensate for that here. */
  if ((Type1SubBlock->Type>>5) == AntennaID)
  {
    if ((SBF_ID_TO_NUMBER(MeasEpoch->Header.ID) == sbfnr_GenMeasEpoch_1) &&
        (Type1SubBlock->SVID >= 120UL && Type1SubBlock->SVID <= 140UL))
    {
      ret |= (1<<L1GEO);
    }
    else
    {
      ret |= (1<<(Type1SubBlock->Type&0x1f));
    }
  }
  
  for (i=0; i<Type1SubBlock->N_Type2; i++) {
    MeasEpochChannelType2_t* SubChannel = (MeasEpochChannelType2_t*)
      ((uint8_t*)Type1SubBlock 
       + MeasEpoch->SB1Size + i*MeasEpoch->SB2Size);
    
    if ((SubChannel->Type>>5) == AntennaID)
    {
      ret |= (1<<(SubChannel->Type&0x1f));
    }
  }

  return ret;
}

/*---------------------------------------------------------------------------*/
uint32_t GetSignalListInMeasEpoch(MeasEpoch_2_t *MeasEpoch,
                                  uint32_t       AntennaID)
{
/* Returns the list of signal types for which measurements are
 * available in a given measurement epoch and for a given antenna
 * index (AntennaID being 1,2,3, etc).  The list is given in the form
 * of a bit field, where bit i is set if signal type i is present in
 * the epoch (the index of a given signal is given in the SignalType_t
 * enumeration).
 *
 * Arguments:
 *  *MeasEpoch: a pointer to a MeasEpoch_2 or GenMeasEpoch_1 SBF block
 */
  MeasEpochChannelType1_t *Type1SubBlock;
  uint32_t ret = 0;
  
  Type1SubBlock = GetFirstType1SubBlock(MeasEpoch);
  
  while (Type1SubBlock != NULL) 
  {
    ret |= GetSignalListInType1(MeasEpoch, Type1SubBlock, AntennaID);
    
    Type1SubBlock = GetNextType1SubBlock(MeasEpoch, Type1SubBlock);
  }
  
  return ret;
}

/*---------------------------------------------------------------------------*/
bool IsAntennaPresent(uint32_t                 AntennaID,
                      MeasEpoch_2_t           *MeasEpoch,
                      MeasEpochChannelType1_t *Type1SubBlock)
/* Returns true if there is data from the specified antenna in a given
 * type-1 sub-block or in one of its dependent type-2 sub-blocks.
 *
 * Arguments:
 *   AntennaID: the antenna ID to search for: can be 1, 2 or 3.
 *
 *  *MeasEpoch: a pointer to a MeasEpoch SBF block
 *
 *  *Type1SubBlock: a pointer to a type-1 sub-block in the
 *        MeasEpoch. Data with the specified AntennaID will be searched in
 *        this type-1 sub-block, and in its type-2 daughters.
 */
{
  bool ret = false;

  /* the Antenna ID is from 0 in the MeasEpoch, and not from 1 */
  AntennaID--;

  if ((Type1SubBlock->Type>>5) == AntennaID) 
  {
    ret = true;
  } 
  else 
  {
    uint32_t i;

    for (i=0; i<Type1SubBlock->N_Type2; i++) 
    {
      MeasEpochChannelType2_t* SubChannel = (MeasEpochChannelType2_t*)
        ((uint8_t*)Type1SubBlock + MeasEpoch->SB1Size + i*MeasEpoch->SB2Size);

      if ((SubChannel->Type>>5) == AntennaID) 
      {
        ret = true;
        break;
      }
    }
  }
  
  return ret;
}


/*---------------------------------------------------------------------------*/
bool DecryptMeasEpoch(MeasEpoch_2_t *MeasEpoch, const uint8_t *key)
{
  bool ret;
  MeasEpochChannelType1_t *Type1SubBlock;
  MeasEpochChannelType2_t *Type2SubBlock;
  int Type2Counter;
  ssnchacha_ctx_t ctx;
  const ssnchacha_encryptionInfo_t *info = (const ssnchacha_encryptionInfo_t *)MeasEpoch->Data;

  /* Check encrypted flag */
  if ((MeasEpoch->CommonFlags & (1 << 7)) == 0)
  {
    ret = false;
  }
  else
  {
    ret = true;

    /* Clear the encrypted flag - even if the key is not valid */
    MeasEpoch->CommonFlags &= ~(1 << 7);

    /* Now iterate over the subblocks and decrypt the encrypted fields */
    Type1SubBlock = GetFirstType1SubBlock(MeasEpoch);

    /*@-branchstate@*/
    while (Type1SubBlock != NULL)
    {
      MeasEpochChannelType1_t *NextType1SubBlock = GetNextType1SubBlock(MeasEpoch, Type1SubBlock);
      if (NextType1SubBlock == NULL)
      {
        info = (const ssnchacha_encryptionInfo_t *)((char*)Type1SubBlock
                                                    + Type1SubBlock->N_Type2*MeasEpoch->SB2Size
                                                    + MeasEpoch->SB1Size);
      }
      Type1SubBlock = NextType1SubBlock;
    }
    /*@=branchstate@*/
    if ((char*)info + sizeof(*info) <= (char*)MeasEpoch + MeasEpoch->Header.Length)
    {
      ssnchacha_initDecryptBlock(&ctx, (const char*)key, info,
                                MeasEpoch->TOW, MeasEpoch->WNc, MeasEpoch->Header.ID);

      /* Now iterate over the subblocks and decrypt the encrypted fields */
      Type1SubBlock = GetFirstType1SubBlock(MeasEpoch);

      while (Type1SubBlock != NULL)
      {
        Type1SubBlock->CodeLSB = ssnchacha_uint32(&ctx, Type1SubBlock->CodeLSB);

        for (Type2Counter = 0; Type2Counter < Type1SubBlock->N_Type2; Type2Counter++)
        {
          Type2SubBlock = (MeasEpochChannelType2_t*) ( (char*)Type1SubBlock
                                                      + MeasEpoch->SB1Size
                                                      + Type2Counter*MeasEpoch->SB2Size );
          Type2SubBlock->CodeOffsetLSB = ssnchacha_uint16(&ctx, Type2SubBlock->CodeOffsetLSB);
        }

        Type1SubBlock = GetNextType1SubBlock(MeasEpoch, Type1SubBlock);
      }
    }
  }
  return ret;
}


