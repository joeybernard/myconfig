/*
 * "sbfread.h"
 *
 *        Declarations of SBF reading and parsing functions
 *
 * (c) 2000-2002 Septentrio NV, Belgium
 */

#ifndef SBFREAD_H
#define SBFREAD_H 1

#include <stdio.h>

#include "ssntypes.h"

#ifndef S_SPLINT_S
#include <sys/types.h>
#else
  typedef int64_t off_t;
#endif

#include "sbfdef.h"
#include "sbfsigtypes.h"

/* 64 bit versions for fseek and ftell are different for the different compilers */
/* STD C version */
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
  #define ssnfseek fseeko
  #define ssnftell ftello
/* Microsoft compiler MSVC  */
#elif defined (_MSC_VER)
  #define ssnfseek _fseeki64
  #define ssnftell _ftelli64
  #define off_t __int64
/* MinGW-32  */
#elif defined (__MINGW32__) && !defined (__MINGW64__)
/* 32 bit on MinGW-64 already redefines them if _FILE_OFFSET_BITS=64 */
 #define ssnfseek fseeko64
 #define ssnftell ftello64
/* fall back to 32 bit version */
#else
  #define ssnfseek fseek
  #define ssnftell ftell
#endif

#define BLOCKNUMBER_ALL      (0xffff)

#define START_POS_FIELD   0x03LU
#define START_POS_CURRENT 0x00LU
#define START_POS_SET     0x01LU

#define END_POS_FIELD         0x0cLU
#define END_POS_AFTER_BLOCK   0x00LU
#define END_POS_DONT_CHANGE   0x04LU

#define pi    3.14159265358979323846 /* Pi */

#define c84   299792458.             /* WGS-84 value for lightspeed */

#define E5FREQ         1191.795e6
#define E5aFREQ        1176.45e6
#define E5bFREQ        1207.14e6
#define E6FREQ         1278.75e6
#define L1FREQ         1575.42e6
#define L2FREQ         1227.60e6
#define L5FREQ         1176.45e6
#define E2FREQ         1561.098e6
#define L1GLOFREQ      1602.00e6
#define L2GLOFREQ      1246.00e6
#define L3GLOFREQ      1202.025e6
#define B3FREQ         1268.52e6

#define E5WAVELENGTH   (c84/E5FREQ)
#define E5aWAVELENGTH  (c84/E5aFREQ)
#define E5bWAVELENGTH  (c84/E5bFREQ)
#define E6WAVELENGTH   (c84/E6FREQ)
#define L1WAVELENGTH   (c84/L1FREQ)
#define L2WAVELENGTH   (c84/L2FREQ)
#define L5WAVELENGTH   (c84/L5FREQ)
#define E2WAVELENGTH   (c84/E2FREQ)
#define L3WAVELENGTH   (c84/L3GLOFREQ)
#define B3WAVELENGTH   (c84/B3FREQ)

#define FIRSTEPOCHms_DONTCARE  (-1LL)
#define LASTEPOCHms_DONTCARE   (1LL<<62)
#define INTERVALms_DONTCARE    (1)

typedef struct {
  FILE*    F;              /* handle to the file */
  uint8_t  key[32];        /* Key for decrypting encrypted blocks */
  bool     has_key;        /* true if key has been set */
} SBFData_t;

void FW_EXPORT RemoveSubBlockPadding(void*  SBFBlock, 
                                     unsigned int    N,
                                     size_t SourceSBSize,
                                     size_t TargetSBSize);

int32_t FW_EXPORT CheckBlock(SBFData_t* SBFData, uint8_t* Buffer);
                           
int32_t FW_EXPORT GetNextBlock(SBFData_t* SBFData, 
                     /*@out@*/ void*      SBFBlock,
                               uint16_t BlockID1, uint16_t BlockID2,
                               uint32_t FilePos);

off_t FW_EXPORT GetSBFFilePos(SBFData_t* SBFData);

off_t FW_EXPORT GetSBFFileLength(SBFData_t* SBFData);

void FW_EXPORT InitializeSBFDecoding(char *FileName,
                          /*@out@*/  SBFData_t* SBFData);

void FW_EXPORT SetSBFDecryptionKey(SBFData_t* SBFData,
                     /*@unique@*/  const uint8_t* key);

void FW_EXPORT SetSBFDecryptionKeyFromFile(SBFData_t* SBFData,
                             /*@unique@*/  const char* RxSerialNbr);

void FW_EXPORT CloseSBFFile(SBFData_t* SBFData);

bool FW_EXPORT IsTimeValid(void* SBFBlock);

int FW_EXPORT GetCRCErrors();

double FW_EXPORT GetWavelength(uint8_t Type, int GLOfn);

uint32_t FW_EXPORT GetSignalListInType1(MeasEpoch_2_t           *MeasEpoch,
                                        MeasEpochChannelType1_t *Type1SubBlock,
                                        uint32_t                 AntennaID);

uint32_t FW_EXPORT GetSignalListInMeasEpoch(MeasEpoch_2_t *MeasEpoch,
                                            uint32_t       AntennaID);

MeasEpochChannelType1_t
FW_EXPORT *GetFirstType1SubBlock(MeasEpoch_2_t *MeasEpoch);

MeasEpochChannelType1_t
FW_EXPORT *GetNextType1SubBlock(MeasEpoch_2_t           *MeasEpoch,
                                MeasEpochChannelType1_t *CurrentType1SubBlock);

bool FW_EXPORT GetMeasEpochObservables(uint8_t   Type,
                                       MeasEpoch_2_t           *MeasEpoch,
                                       MeasEpochChannelType1_t *Type1SubBlock,
                             /*@out@*/ double    *PR,
                             /*@out@*/ double    *Carrier,
                             /*@out@*/ double    *Doppler,
                             /*@out@*/ double    *CN0,
                             /*@out@*/ double    *LockTime,
                             /*@out@*/ bool      *HalfCycleAmbiguityFlag);

void FW_EXPORT GetObsFromType1(MeasEpoch_2_t           *MeasEpoch,
                               MeasEpochChannelType1_t *Type1SubBlock,
                     /*@out@*/ uint8_t   *Type,
                     /*@out@*/ double    *PR,
                     /*@out@*/ double    *Carrier,
                     /*@out@*/ double    *Doppler,
                     /*@out@*/ float     *CN0,
                     /*@out@*/ uint32_t  *LockTime,
                               bool       OnlyIncludeFullAmbiguityPhase);

void FW_EXPORT GetNextObsFromType2(MeasEpoch_2_t           *MeasEpoch,
                                   MeasEpochChannelType1_t *Type1SubBlock,
                       /*@out@*/   uint8_t   *Type,
                       /*@out@*/   double    *PR,
                       /*@out@*/   double    *Carrier,
                       /*@out@*/   double    *Doppler,
                       /*@out@*/   float     *CN0,
                       /*@out@*/   uint32_t  *LockTime,
                                   bool       OnlyIncludeFullAmbiguityPhase);

uint32_t FW_EXPORT GetMeasEpochSVID(MeasEpochChannelType1_t *Type1SubBlock);

uint32_t FW_EXPORT GetMeasEpochRXChannel(MeasEpochChannelType1_t *Type1SubBlock);

uint32_t FW_EXPORT GetGenMeasAntennaID(MeasEpochChannelType1_t *Type1SubBlock);

bool FW_EXPORT IncludeThisEpoch(void*   SBFBlock,
                                int64_t ForcedFirstEpoch_ms,
                                int64_t ForcedLastEpoch_ms,
                                int     ForcedInterval_ms,
                                bool    AcceptInvalidTimeStamp);

bool FW_EXPORT IsAntennaPresent(uint32_t                 AntennaID,
                                MeasEpoch_2_t           *MeasEpoch,
                                MeasEpochChannelType1_t *Type1SubBlock);

bool FW_EXPORT IncludeThisEpoch(void*   SBFBlock,
                                int64_t ForcedFirstEpoch_ms,
                                int64_t ForcedLastEpoch_ms,
                                int     ForcedInterval_ms,
                                bool    AcceptInvalidTimeStamp);

bool FW_EXPORT DecryptMeasEpoch(MeasEpoch_2_t *MeasEpoch, const uint8_t *key);

#define Terminate {char S[255];   \
  (void)snprintf(S, sizeof(S), "Abnormal program termination (%s,%i)", \
             __FILE__, __LINE__); \
  S[254] = '\0'; \
  perror(S); \
  exit(EXIT_FAILURE); \
  }


#endif
/* End of "ifndef SBFREAD_H" */
