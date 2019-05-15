/*
 * "sbf2asc.c"
 *
 *      Main program for the "sbf2asc" executable that converts an SBF
 *      file (Septentrio Binary Format) to a free plain-text format.
 *
 * (c) 2000-2004 Septentrio nv/sa, Belgium
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "ssngetop.h"
#include "sbfread.h"
#include "sbf2asc_version.h"

static uint32_t OutputPVTcar            = 0;   /* default = no PVTcar            in measasc.dat */
static uint32_t OutputPVTgeo            = 0;   /* default = no PVTgeo            in measasc.dat */
static uint32_t OutputMeas              = 0;   /* default = no Meas              in measasc.dat */
static uint32_t OutputPVTCov            = 0;   /* default = no PVTCov            in measasc.dat */
static uint32_t OutputDOP               = 0;   /* default = no DOP               in measasc.dat */
static uint32_t OutputAttEuler          = 0;   /* default = no AttEuler     in measasc.dat */
static uint32_t OutputAttCovEuler       = 0;   /* default = no AttCovEuler  in measasc.dat */
static uint32_t OutputExtEvent          = 0;   /* default = no ExtEvent          in sbfasc.txt */
static uint32_t OutputReceiverStatus    = 0;   /* default = no ReceiverStatus    in sbfasc.txt */
static uint32_t OutputBaseStation       = 0;   /* default = no BaseStation       in sbfasc.txt */
static uint32_t OutputBaseLine          = 0;   /* default = no BaseLine          in sbfasc.txt */
static uint32_t OutputBaseLink          = 0;   /* default = no BaseLink          in sbfasc.txt */
static uint32_t OutputGPSAlm            = 0;   /* default = no GPSALM            in sbfasc.txt */
static uint32_t OutputAuxPos            = 0;   /* default = no Auspos              in sbfasc.txt */
static uint32_t OutputExtSensorMeas     = 0;   /* default = no ExtSensorMeas              in sbfasc.txt */
static uint32_t VerboseMode             = 0;   /* default = ne VerboseMode       in sbfasc.txt */
static uint32_t TimerCounters[2]        = {0,0}; /* default = no ExtEvent        in sbfasc.txt */
static bool     AcceptInvalidTime       = true; /* default = yes to process blocks without proper time stamp */

static const char usage_msg1[] = "\n"
  "sbf2asc -f input_file [-o output_file]\n"
  "        [-m][-p][-g][-c][-d][-a][-s]\n"
  "        [-b startepoch][-e endepoch][-i Interval][-v][-V]\n"
  "  -f input_file:  (mandatory) Name of the SBF file.\n"
  "  -o output_file: Name of the ascii file\n"
  "                   (if not provided, measasc.dat is used).\n"
  "  -m              Include contents of the (Short)MeasEpoch blocks.\n"
  "  -p              Include contents of the PVTCartesian blocks.\n"
  "  -g              Include contents of the PVTGeodetic blocks.\n"
  "  -c              Include contents of the PVTCov blocks.\n"
  "  -d              Include contents of the DOP blocks.\n"
  "  -a              Include contents of the AttEuler blocks.\n"
  "  -s              Include contents of the AttCovEuler blocks.\n"
  "  -u              Include contents of the AuxPos blocks.\n"
  "  -t              Include contents of the ReceiverStatus blocks.\n"
  "  -x              Include contents of the ExtEvent blocks.\n"
  "  -n              Include contents of the BaseStation blocks.\n"
  "  -l              Include contents of the BaseLine blocks.\n"
  "  -k              Include contents of the BaseLink blocks.\n"
  "  -h              Include contents of the GPSAlm blocks.\n"  
  "  -j              Inlcude contents of the ExtSensorMeasurements blocks.\n"  
  "  -b startepoch   Time of first epoch to insert in the file.\n"
  "                  Format: yyyy-mm-dd_hh:mm:ss.sss or hh:mm:ss.sss.\n"
  "  -e endepoch     Last epoch to insert in the file\n"
  "                  Format: yyyy-mm-dd_hh:mm:ss.sss or hh:mm:ss.sss.\n"
  "  -i Interval:    Decimation interval in seconds.\n"
  "  -E              Exclude blocks where time stamp is invalid.\n"
  "  -v              Verbose mode, progress displayed.\n"
  "  -V              Display the sbf2asc version.\n"
  "\n"
  "The first column identifies the format and contents of each row as follows:\n"
  "1-255: the row contains data from a (Short)MeasEpoch block\n"
  "0    : the row contains data from a PVTCar block\n"
  "-1   : the row contains data from a PVTGeo block\n"
  "-2   : the row contains data from a PVTCov block\n"
  "-3   : the row contains data from a DOP block\n"
  "-4   : the row contains data from a AttEuler block\n"
  "-5   : the row contains data from a AttCovEuler block\n"
  "-6   : the row contains data from a ExtEvent block\n"
  "-7   : the row contains data from a ReceiverStatus block\n"
  "-8   : the row contains data from a BaseStation block\n"
  "-9   : the row contains data from a BaseLine block\n"
  "-10  : the row contains data from a BaseLink block\n"
  "-11  : the row contains data from a GPSAlm block\n"
  "-12  : the row contains data from a AuxPos block\n"
  "\n";
static const char usage_msg2[] = 
  "1-255: (Short)MeasEpoch block\n"
  "Col1:  PRN identifier (from 1 to 255).  For GLONASS, PRN is 45+FreqNumber.\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  CA pseudorange in meters, or -20000000000 if not available\n"
  "Col4:  L1 carrier phase in cycles, or -20000000000 if not available\n"
  "Col5:  CA C/N0 in dB-Hz, or -3276.8 if not available\n"
  "Col6:  P1 pseudorange in meters, or -20000000000 if not available\n"
  "Col7:  P2 pseudorange in meters, or -20000000000 if not available\n"
  "Col8:  L2 carrier phase in cycles, or -20000000000 if not available\n"
  "Col9:  P1 C/N0 in dB-Hz, or -3276.8 if not available\n"
  "Col10: P2 C/N0 in dB-Hz, or -3276.8 if not available\n"
  "Col11: RxChannel\n"
  "Col12: Lock time in seconds\n"
  "Col13: L1 Doppler in Hz, or -214748.365 if not available\n"
  "Col14: L2 Doppler in Hz, or -214748.365 if not available\n"
  "Col15: CA Multipath correction in meters, or 0 if unknown or not applicable\n"
  "Col16: P2 Multipath correction in meters, or 0 if unknown or not applicable\n"
  "\n"
  "0: PVTCartesian block\n"
  "Col1:  0\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  X in meters, or -20000000000 if not available\n"
  "Col4:  Y in meters, or -20000000000 if not available\n"
  "Col5:  Z in meters, or -20000000000 if not available\n"
  "Col6:  Vx in m/s, or -20000000000 if not available\n"
  "Col7:  Vy in m/s, or -20000000000 if not available\n"
  "Col8:  Vz in m/s, or -20000000000 if not available\n"
  "Col9:  RxClkBias in seconds, or -20000000000 if not available\n"
  "Col10: RxClockDrift in seconds/seconds, or -20000000000 if not available\n"
  "Col11: NbrSV\n"
  "Col12: PVT Mode field\n"
  "Col13: MeanCorrAge in 1/100 seconds, or 65535 if not available\n"
  "Col14: PVT Error\n"
  "Col15: COG\n"
  "\n"
  "-1: PVTGeodetic block\n"
  "Col1:  -1\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Latitude in radians, or -20000000000 if not available\n"
  "Col4:  Longitude in radians, or -20000000000 if not available\n"
  "Col5:  Ellipsoidal height in meters, or -20000000000 if not available\n"
  "Col6:  Geodetic Ondulation, or -20000000000 if not available\n"
  "Col7:  Vn in m/s, or -20000000000 if not available\n"
  "Col8:  Ve in m/s, or -20000000000 if not available\n"
  "Col9:  Vu in m/s, or -20000000000 if not available\n"
  "Col10:  Clock bias in seconds, or -20000000000 if not available\n"
  "Col11: Clock drift in seconds/seconds, or -20000000000 if not available\n"
  "Col12: NbrSV\n"  
  "Col13: PVT Mode field\n"
  "Col14: MeanCorrAge in 1/100 seconds, or 65535 if not available\n"
  "Col15: PVT Error\n"
  "Col16: COG\n"
  "\n"
  "-2: PVTCov block\n"
  "Col1:  -2\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Covariance xx\n"
  "Col4:  Covariance yy\n"
  "Col5:  Covariance zz\n"
  "Col6:  Covariance tt\n"
  "\n"
  "-3: PVTDOP block\n"
  "Col1:  -3\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  PDOP value, or NA if PDOP not available\n"
  "Col4:  TDOP value, or NA if TDOP not available\n"
  "Col5:  HDOP value, or NA if HDOP not available\n"
  "Col6:  VDOP value, or NA if VDOP not available\n"
  "Col7:  HPL value in meters, or NA if not available\n"
  "Col8:  VPL value in meters, or NA if not available\n"
  "Col9:  NbrSV\n"
  "\n";
static const char usage_msg3[] = 
  "-4: AttEuler block\n"
  "Col1:  -4\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Heading in degree\n"
  "Col4:  Pitch in degree\n"
  "Col5:  Roll in degree\n"
  "Col6:  Error flag for attitude solution\n"
  "Col7:  Mode used to compute attitude solution\n"
  "Col8:  NbrSV\n"
  "\n"
  "-5: AttCovEuler block\n"
  "Col1:  -5\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Covariance HeadingHeading\n"
  "Col4:  Covariance PitchPitch\n"
  "Col5:  Covariance RollRoll\n"
  "Col6:  Error flag for attitude solution\n"
  "\n"
  "-6: ExtEvent\n"
  "Col1:  -6\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Source (1 = GPIN1, 2 = GPIN2)\n"
  "Col4:  Counter used to indicate the number of events that have occurred from the source (Col3)\n"
  "Col5:  Offset sub-millisecond part of the external event time.\n"
  "\n"
  "-7: ReceiverStatus\n"
  "Col1:  -7\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  CPU-Load in percentage\n"
  "Col4:  Uptime in seconds\n"
  "Col5:  RxStatus field (HEX)\n"
  "\n"
  "-8: BaseStation\n"
  "Col1:  -8\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Base Station ID\n"
  "Col4:  Base type\n"
  "Col5:  Source\n"
  "Col6:  X_L1 Phase center\n"
  "Col7:  Y_L1 Phase center\n"
  "Col8:  Z_L1 Phase center\n"
  "\n"
  "-9: BaseLine\n"
  "Col1:  -9\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Base Station ID\n"
  "Col4:  East\n"
  "Col5:  North\n"
  "Col6:  Up\n"
  "\n"
  "-10: BaseLink\n"
  "Col1:  -10\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Number of Bytes Received\n"
  "Col4:  Number of Bytes Accepted\n"
  "Col5:  Number of Messages Received\n"
  "Col6:  Number of Messages Accepted\n"
  "Col7:  Age of last message\n"
  "\n"
  "-11: GPSAlm\n"
  "Col1:  -11\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  PRN\n"
  "Col4:  Eccentricity\n"
  "Col5:  Almanac reference time of week\n"
  "Col6:  Inclination angle at reference time, relative to i0 = 3 semi-circles\n"
  "Col7:  Rate of right ascension\n"
  "Col8:  Square root of the semi-major axis\n"
  "Col9:  Longitude of ascending node of orbit plane at weekly epoch\n"
  "Col10: Argument of perigee\n"
  "Col11: Mean anomaly at reference time\n"
  "Col12: SV Clock Drift\n" 
  "Col13: SC Clock Bias\n"
  "Col14: Almanac reference week, to which t_oa is referenced\n" 
  "Col15: Health on 8 bits from the almanac page\n"
  "Col16: Health summary on 6 bits\n"
  "\n"
  "-12: AuxPos\n"
  "Col1:  -12\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Antenna ID\n"
  "Col4:  Delta East\n"
  "Col5:  Delta North\n"
  "Col6:  Delta Up\n"
  "Col7:  Number of Satellites\n"
  "Col8:  Error\n"
  "Col9:  Ambiguity Type\n"  
  "\n"
  "-13: ExtSensorMeas\n"
  "Col1:  -13\n"
  "Col2:  time (GPS second since Jan 06, 1980)\n"
  "Col3:  Source\n"
  "Col4:  Type\n"
  "Col5:  X\n"
  "Col6:  Y\n"
  "Col7:  Z\n" 
  "\n";

/*---------------------------------------------------------------------------*/
/* Print basic help about the available command line options: */
static void usage(void)
{
  fprintf(stderr, "%s", usage_msg1);
  fprintf(stderr, "%s", usage_msg2);
  fprintf(stderr, "%s", usage_msg3);
}


/*---------------------------------------------------------------------------*/
/*Displays progress as a percentage of parsed blocks in the SBF file */
static void DisplayProgress(SBFData_t *SBFData) 
{
  static float     SBFFileSize = 0.0F;
  static float     NextProgressReport = 0.0F;
  float            CurrentProgress;

  /* If SBFFileSize not yet initialized, do it now. */
  if (SBFFileSize == 0.0F) 
  {
    SBFFileSize = (float)GetSBFFileLength(SBFData);
  }
  
  /* Get the current progress in % of the SBF file. */
  CurrentProgress = (float)GetSBFFilePos(SBFData)*100.0 / SBFFileSize;

  if (CurrentProgress > NextProgressReport) 
  {
    /* Every time we did one more % of the work, we update the progress
     * indicator. */
    NextProgressReport = floor(CurrentProgress + 1.0);
    fprintf(stdout, "Creating ASCII file:%3.0f%% done\r",
            CurrentProgress);
    (void)fflush(stdout);
  }
}


/*---------------------------------------------------------------------------*/
static void PrintMeasEpoch(FILE          *F, 
                           MeasEpoch_2_t *MeasEpoch,
                           MeasExtra_1_t *MeasExtra)
{
  double  CurrentTime;
  double  PCA, P1Code, P2Code;
  double  CACN0, P1CN0, P2CN0;
  double  LCADoppler, L2Doppler;
  double  LCAPhase, L2Phase;
  double  PhaseDummy, DopplerDummy;
  double  LockTime, LockTimeDummy;
  bool    HalfCycleFlag;
  MeasEpochChannelType1_t *Type1SubBlock;
  int     MeasExtraIdx = 0;
  float   MPCorr_CA = 0.0;
  float   MPCorr_P2 = 0.0;
  
  /* Get the epoch time from the SBF block. */
  CurrentTime 
    = (double)MeasEpoch->WNc * (86400.0 * 7.0)
    + (double)MeasEpoch->TOW / 1000.0;

  /* get the first type-1 sub-block of this MeasEpoch */
  Type1SubBlock = GetFirstType1SubBlock(MeasEpoch);
  
  while (Type1SubBlock != NULL) 
  {
    uint32_t SVID = GetMeasEpochSVID(Type1SubBlock);
    uint32_t CASignalIndex = L1CA;
    uint32_t P1SignalIndex = L1P;
    uint32_t P2SignalIndex = L2P;

    if (SVID >= 120UL && SVID <= 140UL) 
    {
      CASignalIndex = L1GEO;
    }
    else if (SVID >= 38UL && SVID <= 62UL)
    {
      CASignalIndex = L1CAGLO;
      P1SignalIndex = L1PGLO;
      P2SignalIndex = L2PGLO;
    }
    else if (SVID >= 71UL && SVID <= 106UL)
    {
      CASignalIndex = L1BC;
      P2SignalIndex = E5a;
    }

    /* get the CA data */
    (void)GetMeasEpochObservables(CASignalIndex, 
                                  MeasEpoch,
                                  Type1SubBlock,
                                  &PCA,
                                  &LCAPhase,
                                  &LCADoppler,
                                  &CACN0,
                                  &LockTime,
                                  &HalfCycleFlag);
    if (HalfCycleFlag)
    {
      LCAPhase = F64_NOTVALID;
      LockTime = F64_NOTVALID;
    }

    /* get the P1 data */
    (void)GetMeasEpochObservables(P1SignalIndex, 
                                  MeasEpoch,
                                  Type1SubBlock,
                                  &P1Code,
                                  &PhaseDummy,
                                  &DopplerDummy,
                                  &P1CN0,
                                  &LockTimeDummy,
                                  &HalfCycleFlag);
    
    /* get the P2 data */
    (void)GetMeasEpochObservables(P2SignalIndex, 
                                  MeasEpoch,
                                  Type1SubBlock,
                                  &P2Code,
                                  &L2Phase,
                                  &L2Doppler,
                                  &P2CN0,
                                  &LockTimeDummy,
                                  &HalfCycleFlag);
    if (HalfCycleFlag)
    {
      L2Phase = F64_NOTVALID;
    }

    /* get the multipath correction from the MeasExtra SBF block */
    if (MeasExtra != (MeasExtra_1_t*)0)
    {
      uint32_t CurrentChannel = GetMeasEpochRXChannel(Type1SubBlock);
      int i;
      MPCorr_CA =0.0;
      MPCorr_P2 =0.0;

      while ((MeasExtra->MeasExtraChannel[MeasExtraIdx].RXChannel 
              < CurrentChannel)  &&
             (MeasExtraIdx < MeasExtra->N)) 
      {
        MeasExtraIdx++;
      }
      
      for (i=MeasExtraIdx; 
           i<MeasExtra->N && MeasExtra->MeasExtraChannel[i].RXChannel==CurrentChannel;
           i++)
      {
        if (MeasExtra->MeasExtraChannel[i].Type == CASignalIndex)
        {
          MPCorr_CA     = MeasExtra->MeasExtraChannel[i].MPCorr*1e-3;
        } 
        else if (MeasExtra->MeasExtraChannel[i].Type == P2SignalIndex)
        {
          MPCorr_P2     = MeasExtra->MeasExtraChannel[i].MPCorr*1e-3;
        }
      }
    }
    
    fprintf(F,"%-3i %12.2f %12.3f %14.3f %4.1f"
            " %12.3f %12.3f %14.3f %4.1f %4.1f %i %f %10.3f %10.3f %6.3f %6.3f\n",
            (int)((SVID >= 38UL && SVID <= 62UL) ? (Type1SubBlock->ObsInfo>>3)+37 : SVID),
            CurrentTime,
            PCA,
            LCAPhase,
            CACN0,
            P1Code,
            P2Code,
            L2Phase,
            P1CN0 > -1e10 ? P1CN0 : -3276.8,
            P2CN0 > -1e10 ? P2CN0 : -3276.8,
            (int)GetMeasEpochRXChannel(Type1SubBlock),
            (double)LockTime,
            LCADoppler > -1e10 ? LCADoppler : -214748.365,
            L2Doppler  > -1e10 ? L2Doppler  : -214748.365,
            MPCorr_CA,
            MPCorr_P2
            );
    
    /* get the next type-1 sub-block */
    Type1SubBlock = GetNextType1SubBlock(MeasEpoch,
                                         Type1SubBlock);
  }
  
}


/*---------------------------------------------------------------------------*/
/* Print a DOP field, 15 characters on "F":
 * either "DOP" divided by 100, right-aligned in a 14 char field,
 * or "            NA " if the DOP is not available (value 0). */
static void PrintPvtDopField(FILE *F, uint16_t DOP)
{
  if (DOP==0) 
  {
    fprintf(F, "            NA ");
  }
  else 
  {
    fprintf(F, "%14.3f ", (float)DOP/100.0);
  }
}

/*---------------------------------------------------------------------------*/
/* Print a HPL or VPL field, 15 characters on "F":
 * either the "XPL", right-aligned in a 14 char field,
 * or "            NA " if the XPL is not available (smaller than -1e10). */
static void PrintPvtXplField(FILE *F, float XPL)
{
  if (XPL <= -1e10) 
  {
    fprintf(F, "            NA ");
  }
  else 
  {
    fprintf(F, "%14.3f ", XPL);
  }
}

/*---------------------------------------------------------------------------*/
static void PrintPvtDopLine(FILE *F, DOP_2_0_t *PVTDOP)
{
  fprintf(F, "-3  ");
  //Print the time
  fprintf(F, "%13.2f ", (float)PVTDOP->WNc*86400.0*7.0+PVTDOP->TOW/1000.0);
    
  PrintPvtDopField(F, PVTDOP->PDOP);
  PrintPvtDopField(F, PVTDOP->TDOP);
  PrintPvtDopField(F, PVTDOP->HDOP);
  PrintPvtDopField(F, PVTDOP->VDOP);
  PrintPvtXplField(F, PVTDOP->HPL);
  PrintPvtXplField(F, PVTDOP->VPL);

  fprintf(F, "%3i \n", (int)(PVTDOP->NrSV));
}


/*---------------------------------------------------------------------------*/
static void CreateAsciiFile(char     *SBFFile, 
                            char     *AsciiFile, 
                            int64_t   ForcedFirstEpoch_ms,
                            int64_t   ForcedLastEpoch_ms,
                            int       ForcedInterval_ms)
{
  SBFData_t  SBFData;
  uint8_t    SBFBlock[MAX_SBFSIZE];
  uint32_t   LastMeasTOW = 0xffffffff;
  FILE      *F;
  
  InitializeSBFDecoding(SBFFile, &SBFData);
  
  /* Open the measurements file */
  F = fopen(AsciiFile, "wt");
  if (F==NULL) 
  {
    perror("Opening of output file failed");
    return;
  }
  
    
  while (GetNextBlock(&SBFData, SBFBlock, BLOCKNUMBER_ALL, BLOCKNUMBER_ALL,
                      START_POS_CURRENT | END_POS_AFTER_BLOCK) == 0) 
  {
    /* Get the time of week in milliseconds from the block. */
    uint32_t CurrentTOW = ((HeaderAndTimeBlock_t*)SBFBlock)->TOW;

    /* Only consider the blocks at the requested interval */
    if (IncludeThisEpoch(SBFBlock,
                         ForcedFirstEpoch_ms, ForcedLastEpoch_ms, 
                         ForcedInterval_ms,
                         AcceptInvalidTime)) 
    {
      switch (SBF_ID_TO_NUMBER(((VoidBlock_t*)SBFBlock)->ID)) 
      {
        case sbfnr_MeasEpoch_2:
        case sbfnr_GenMeasEpoch_1:
          if (OutputMeas == 1) {
            uint8_t          SBFBlock_Extra[MAX_SBFSIZE];
            MeasExtra_1_t*   MeasExtra = (MeasExtra_1_t*)0;
            
            /* if a MeasExtra block is available, fetch it */
            if (GetNextBlock(&SBFData, SBFBlock_Extra, 
                             BLOCKNUMBER_ALL, BLOCKNUMBER_ALL,
                             START_POS_CURRENT | END_POS_DONT_CHANGE) == 0)
            {
              if ((SBF_ID_TO_NUMBER(((VoidBlock_t*)SBFBlock_Extra)->ID) 
                   == sbfnr_MeasExtra_1)                                 &&
                  (((HeaderAndTimeBlock_t*)SBFBlock_Extra)->TOW         
                   == CurrentTOW))
              {
                RemoveSubBlockPadding(
                  SBFBlock_Extra,
                  ((MeasExtra_1_t*)SBFBlock_Extra)->N,
                  ((MeasExtra_1_t*)SBFBlock_Extra)->SBSize,
                  sizeof(MeasExtraChannel_1_t));
                MeasExtra = (MeasExtra_1_t*)SBFBlock_Extra;
              }
            }
            
            PrintMeasEpoch(F, (MeasEpoch_2_t*)SBFBlock, MeasExtra);
            
            LastMeasTOW = CurrentTOW;
          }
          break;
        
        case sbfnr_PVTCartesian_1:
          if (OutputPVTcar == 1) 
          {
            PVTCartesian_1_0_t *PVT = (PVTCartesian_1_0_t*)SBFBlock;
            fprintf(F, "%-2i %13.2f %14.3f %14.3f %14.3f %10.3f %10.3f"
                       " %10.3f %15.8e %13.6e %3i %3i %3i %3i %10.3f\n",
                    0,
                    (float)PVT->WNc*86400.0*7.0+PVT->TOW/1000.0,
                    PVT->X,
                    PVT->Y,
                    PVT->Z,
                    PVT->Vx,
                    PVT->Vy,
                    PVT->Vz,
                    PVT->RxClkBias,
                    PVT->RxClkDrift,
                    (int)(PVT->NrSV),
                    (int)PVT->Mode,
                    (int)PVT->MeanCorrAge,
                    (int)PVT->Error,
                    PVT->Cog
                     );
          }
          break;
        
        case sbfnr_PVTCartesian_2:
          if (OutputPVTcar == 1) 
          {
            PVTCartesian_2_0_t *PVT = (PVTCartesian_2_0_t*)SBFBlock;
            fprintf(F, "%-2i %13.2f %14.3f %14.3f %14.3f %10.3f %10.3f"
                       " %10.3f %15.8e %13.6e %3i %3i %3i %3i %10.3f\n",
                    0,
                    (float)PVT->WNc*86400.0*7.0+PVT->TOW/1000.0,
                    PVT->X,
                    PVT->Y,
                    PVT->Z,
                    PVT->Vx,
                    PVT->Vy,
                    PVT->Vz,
                    PVT->RxClkBias  > -1e10 ? PVT->RxClkBias*1e-3  : -2e10,
                    PVT->RxClkDrift > -1e10 ? PVT->RxClkDrift*1e-6 : -2e10,
                    (int)(PVT->NrSV),                    
                    (int)PVT->Mode,
                    (int)PVT->MeanCorrAge,
                    (int)PVT->Error,
                    PVT->COG
                    );
          }
          break;

        case sbfnr_PVTGeodetic_1:
          if (OutputPVTgeo == 1) 
          {
            PVTGeodetic_1_0_t *PVT = (PVTGeodetic_1_0_t*)SBFBlock;
            fprintf(F, "%-2i %13.2f %14.11f %15.11f %14.5f %14.5f %10.5f"
                       " %10.5f %10.5f %15.8e %13.6e %3i %3i %3i %3i %10.3f\n",
                    -1,
                    (float)PVT->WNc*86400.0*7.0+PVT->TOW/1000.0,
                    PVT->Lat,
                    PVT->Lon,
                    PVT->Alt,
                    PVT->GeoidHeight,
                    PVT->Vn,
                    PVT->Ve,
                    PVT->Vu,
                    PVT->RxClkBias,
                    PVT->RxClkDrift,                    
                    (int)(PVT->NrSV),
                    (int)PVT->Mode,
                    (int)PVT->MeanCorrAge,
                    (int)PVT->Error,
                    PVT->Cog
                    );
          }
          break;
        
        case sbfnr_PVTGeodetic_2:
          if (OutputPVTgeo == 1) 
          {
            PVTGeodetic_2_0_t *PVT = (PVTGeodetic_2_0_t*)SBFBlock;
            fprintf(F, "%-2i %13.2f %14.11f %15.11f %14.5f %14.5f %10.5f"
                       " %10.5f %10.5f %15.8e %13.6e %3i %3i %3i %3i %10.3f\n",
                    -1,
                    (float)PVT->WNc*86400.0*7.0+PVT->TOW/1000.0,
                    PVT->Lat,
                    PVT->Lon,
                    PVT->Alt,
                    PVT->Undulation,
                    PVT->Vn,
                    PVT->Ve,
                    PVT->Vu,
                    PVT->RxClkBias  > -1e10 ? PVT->RxClkBias*1e-3  : -2e10,
                    PVT->RxClkDrift > -1e10 ? PVT->RxClkDrift*1e-6 : -2e10,
                    (int)(PVT->NrSV),                    
                    (int)PVT->Mode,
                    (int)PVT->MeanCorrAge,
                    (int)PVT->Error,
                    PVT->COG
                    );
          }
          break;
        
        case sbfnr_PosCovCartesian_1:
          if (OutputPVTCov == 1) 
          {
            PosCovCartesian_1_0_t *PVTCOV = (PosCovCartesian_1_0_t*) SBFBlock;
            fprintf(F, "%-2i %13.2f %14.3f %14.3f %14.3f %14.3f"
                       " 0 0 0 0 0 0 0 0\n",
                    -2,
                    (float)PVTCOV->WNc*86400.0*7.0+PVTCOV->TOW/1000.0,
                    PVTCOV->Cov_xx,
                    PVTCOV->Cov_yy,
                    PVTCOV->Cov_zz,
                    PVTCOV->Cov_tt
                    );
          }
          break;
        
                
        case sbfnr_DOP_1:
          if (OutputDOP == 1) 
          {
            PrintPvtDopLine(F, (DOP_2_0_t*)SBFBlock);
          }
          break;
        
        case sbfnr_DOP_2:
          if (OutputDOP == 1) 
          {
            PrintPvtDopLine(F, (DOP_2_0_t*)SBFBlock);
          }
          break;

        case sbfnr_AttEuler_1:
          if (OutputAttEuler == 1) 
          {
            AttEuler_1_0_t *ATTEULER = (AttEuler_1_0_t*) SBFBlock;
            fprintf(F, "%-2i %13.2f %14.5f %14.5f %14.5f"
                       " %3u %3u %3u 0 0 0 0 0 0\n",
                    -4,
                    (float)ATTEULER->WNc*86400.0*7.0+ATTEULER->TOW/1000.0,
                    ATTEULER->Heading,
                    ATTEULER->Pitch,
                    ATTEULER->Roll,
                    (unsigned int)(ATTEULER->Error),
                    (unsigned int)ATTEULER->Mode,
                    (unsigned int)(ATTEULER->NRSV)
                    );
          }
          break;

        case sbfnr_AttCovEuler_1:
          if (OutputAttCovEuler == 1) 
          {
            AttCovEuler_1_0_t *ATTCOVEULER = (AttCovEuler_1_0_t*) SBFBlock;
            fprintf(F, "%-2i %13.2f %14.5f %14.5f %14.5f"
                       " %3u 0 0 0 0 0 0 0 0\n",
                    -5,
                    (float)ATTCOVEULER->WNc*86400.0*7.0+ATTCOVEULER->TOW/1000.0,
                    ATTCOVEULER->Cov_HeadHead,
                    ATTCOVEULER->Cov_PitchPitch,
                    ATTCOVEULER->Cov_RollRoll,
                    (unsigned int)(ATTCOVEULER->Error)
                    );
          }
          break;
                          
        case sbfnr_ExtEvent_1:
          if (OutputExtEvent == 1) {
            ExtEvent_1_0_t *EXTEVENT = (ExtEvent_1_0_t*) SBFBlock;

            TimerCounters[EXTEVENT->TimerData.Source-1] += 1;
            if (EXTEVENT->TimerData.Offset )
            
            
            fprintf(F, "%-2i %16.6f %4i %4i %16.6f 0 0 0 0 0 0 0 0 0\n",
                    -6,
                    (float)EXTEVENT->TimerData.WNc*86400.0*7.0+EXTEVENT->TimerData.TOW/1000.0+EXTEVENT->TimerData.Offset,
                    (int)EXTEVENT->TimerData.Source,
                    (int)TimerCounters[EXTEVENT->TimerData.Source-1],
                    (float)EXTEVENT->TimerData.Offset
                   );
          }
          break;

        case sbfnr_ReceiverStatus_1:
          if (OutputReceiverStatus == 1) {
              ReceiverStatus_1_0_t *RXSTATUS = (ReceiverStatus_1_0_t*) SBFBlock;
              fprintf(F, "%-2i %13.1f %3u %8u %x "
                      "0 0 0 0 0 0 0 0 0 0 0\n",
                      -7,
                      (double)RXSTATUS->WNc*86400.0*7.0+RXSTATUS->TOW/1000.0,
                      (unsigned int)RXSTATUS->CPULoad,
                      (unsigned int)RXSTATUS->UpTime,
                      (unsigned int)RXSTATUS->RxStatus
                     );
            }
          break;
        
        case sbfnr_ReceiverStatus_2:
          if (OutputReceiverStatus == 1) {
              ReceiverStatus_2_1_t *RXSTATUS = (ReceiverStatus_2_1_t*) SBFBlock;
              fprintf(F, "%-2i %13.1f %3u %8u %x "
                      "0 0 0 0 0 0 0 0 0 0 0\n",
                      -7,
                      (double)RXSTATUS->WNc*86400.0*7.0+RXSTATUS->TOW/1000.0,
                      (unsigned int)RXSTATUS->CPULoad,
                      (unsigned int)RXSTATUS->UpTime,
                      (unsigned int)RXSTATUS->RxStatus
                     );
            }
          break;

        case sbfnr_BaseStation_1:
          if (OutputBaseStation == 1) {
            BaseStation_1_0_t *BASESTATION = (BaseStation_1_0_t*) SBFBlock;
            fprintf(F, "%-2i %13.1f %5u %1u %1u %14.3f %14.3f %14.3f\n",
                    -8,
                    (float)BASESTATION->WNc*86400.0*7.0+BASESTATION->TOW/1000.0,
                    (unsigned int)BASESTATION->BaseStationID,
                    (unsigned int) (BASESTATION->BaseType),
                    (unsigned int) (BASESTATION->Source),
                    BASESTATION->X_L1PhaseCenter,
                    BASESTATION->Y_L1PhaseCenter,
                    BASESTATION->Z_L1PhaseCenter
                   );
          }
          break;

        case sbfnr_BaseLine_1:
          if (OutputBaseLine == 1) {
            BaseLine_1_0_t *BASELINE = (BaseLine_1_0_t*) SBFBlock;
            fprintf(F, "%-2i %13.1f %4u %13.4f %13.4f %13.4f\n",
                    -9,
                    (float)BASELINE->WNc*86400.0*7.0+BASELINE->TOW/1000.0,
                    (unsigned int)BASELINE->BaseStationID,
                    BASELINE->East,
                    BASELINE->North,
                    BASELINE->Up
                   );
          }
          break;

        case sbfnr_BaseLink_1:
          if (OutputBaseLink == 1) {
            BaseLink_1_0_t *BASELINK = (BaseLink_1_0_t*) SBFBlock;
            fprintf(F, "%-2i %13.1f %10u %10u %10u %10u %10.2f\n",
                    -10,
                    (float)BASELINK->WNc*86400.0*7.0+BASELINK->TOW/1000.0,
                    (unsigned int)BASELINK->NrBytesReceived,
                    (unsigned int)BASELINK->NrBytesAccepted,
                    (unsigned int)BASELINK->NrMessagesReceived,
                    (unsigned int)BASELINK->NrMessagesAccepted,
                    BASELINK->AgeOfLastMsg
                   );
          }
          break;
          

        case sbfnr_GPSAlm_1:
          if (OutputGPSAlm == 1) {
            GPSAlm_1_0_t *GPSALM = (GPSAlm_1_0_t*) SBFBlock;
            gpAlm_t *ALM = &(GPSALM->Alm);  
            fprintf(F, "%-2i %13.1f %3u %10.3f %10u %10.3f %10.3f %10.3f"
                    "%10.3f %10.3f %10.3f %10.3f %10.3f %3u %3u %3u %3u\n",
                    -11,
                    (float)ALM->WNc*86400.0*7.0+ALM->TOW/1000.0,
                    (unsigned int)(ALM->PRN),
                    ALM->e, 
                    (unsigned int)ALM->t_oa,
                    ALM->delta_i,
                    ALM->OMEGADOT,
                    ALM->SQRT_A,
                    ALM->OMEGA_0,
                    ALM->omega,
                    ALM->M_0,
                    ALM->a_f1,
                    ALM->a_f0,
                    (unsigned int)(ALM->WN_a),
                    (unsigned int)(ALM->config),
                    (unsigned int)(ALM->health8),
                    (unsigned int)(ALM->health6)
                   );
          }
          break;
          
        case sbfnr_AuxAntPositions_1:
          if (OutputAuxPos == 1) {          
            AuxAntPositions_1_0_t *AUXPOS = (AuxAntPositions_1_0_t*) SBFBlock;
            int i=0;
            for (i=0; i<AUXPOS->NbrAuxAntennas; i++) {
              AuxAntPosData_1_0_t *AUXPOSN = &(AUXPOS->AuxAntPositions[i]);  
              fprintf(F, "%-2i %13.1f %3u %10.3f %10.3f %10.3f"
                      "%3u %3u %3u 0 0 0 0 0\n",
                      -12,
                      (float)AUXPOS->WNc*86400.0*7.0+AUXPOS->TOW/1000.0,
                      (unsigned int)(AUXPOSN->AuxAntID),
                      AUXPOSN->DeltaEast, 
                      AUXPOSN->DeltaNorth,
                      AUXPOSN->DeltaUp,
                      (unsigned int)AUXPOSN->NRSV,
                      (unsigned int)AUXPOSN->Error,
                      (unsigned int)AUXPOSN->AmbiguityType
                     );
            }
          }
          break;
        case sbfnr_ExtSensorMeas_1:
          if (OutputExtSensorMeas == 1) {          
            ExtSensorMeas_1_t *EXTSENSMEAS = (ExtSensorMeas_1_t*) SBFBlock;
            int i=0;
            for (i=0; i<EXTSENSMEAS->N; i++) {
              ExtSensorMeasSB_t *EXTSENSMEASN = &(EXTSENSMEAS->ExtSensorMeas[i]);  
              fprintf(F, "%-2i %13.2f %3u %3u %10.3f %10.3f %10.3f"
                      " 0 0 0 0 0 0\n",
                      -13,
                      (float)EXTSENSMEAS->WNc*86400.0*7.0+EXTSENSMEAS->TOW/1000.0,
                      (unsigned int)EXTSENSMEASN->Source, 
                      (unsigned int)EXTSENSMEASN->Type,
                      EXTSENSMEASN->X,
                      EXTSENSMEASN->Y,
                      EXTSENSMEASN->Z
                     );
            }
          }
          break;
          
        default:
          break;
      }
    }
    /* display the progress report, if enabled */
    if (VerboseMode == 1) 
    {
      DisplayProgress(&SBFData);
    }
  }
  
  if (VerboseMode == 1) 
  {
    fprintf(stdout, "Creating ASCII file:100%% done\n");
    (void)fflush(stdout);
  }
  
  /* Closing the opened files */
  (void)fclose(F);

  CloseSBFFile(&SBFData);

  return;
}

/*---------------------------------------------------------------------------*/
static int yearOffset[4] = {0, 366, 366+365, 366+365+365};
static int dayCount[12]  = {0,31,59,90,120,151,181,212,243,273,304,334};

static int ConvertDateToGPSDay(int         year,
                               int         month,
                               int         day)
{
  int  fouryear_interval = year%4;
  int  GPSDay;

  /* # days from beginning of 1980 till beginning of the current
       4-year period (NB: 1461=365.25*4)*/
  GPSDay = 1461*((year-1980)/4);

  /* add the number of days from the beginning of the current 4-year
     period to the beginning of the current year */
  GPSDay += yearOffset[fouryear_interval];
  
  /* add number of full days elapsed since the beginning of the
     current year */
  GPSDay += dayCount[month-1] + day - 1;

  /* compensate for leap year */
  if ((fouryear_interval==0) && (month>=3))
  {
    GPSDay++;
  }

  /* GPS time starts January 6th, 1980, so remove 5 days */
  GPSDay -= 5;

  return GPSDay;
}


/*---------------------------------------------------------------------------*/
double ConvertDateTimeToGPSsec(int         year,
                               int         month,
                               int         day,
                               int         hour,
                               int         min,
                               double      sec)
{
  uint32_t GPSday = ConvertDateToGPSDay(year, month, day);
  
  return (GPSday*86400.0 + (double)(hour*3600 + min*60) + sec);
}


/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  char       SBFFileName[256];
  char       AsciiFileName[256];
  int        optionchar;
  double     Interval;
  
  int        year, month, day, hour, min;
  double     sec;
  char       dummy;
  int64_t    ForcedFirstEpoch_ms, ForcedLastEpoch_ms;
  int        ForcedInterval_ms;

  /* Set the file names to an empty string. */
  SBFFileName[0]   = '\0';
  AsciiFileName[0] = '\0';

  /* No specs on the first and last epoch to put on the file */
  ForcedFirstEpoch_ms  = FIRSTEPOCHms_DONTCARE;
  ForcedLastEpoch_ms   = LASTEPOCHms_DONTCARE;
  ForcedInterval_ms    = INTERVALms_DONTCARE;
  
  /* Parse the command line options: */
  ssn_opterr = 0;    /* Warn the user if an invalid option was entered. */

  while ( (optionchar = ssn_getopt(argc, argv, "f:o:b:e:mgcpsadjvVEi:xtnlkhu") ) != -1 )
  {
    switch (optionchar)
      {
      case 'b':
        /* First time to include in the file */
        /* If there is a '-' in the argument, we assume that a date
                          * is provided */
        if (strchr(ssn_optarg, '-') != NULL) {
          (void)sscanf(ssn_optarg, "%d%c%d%c%d%c%d%c%d%c%lf",
                       &year, &dummy, &month, &dummy, &day, &dummy,
                       &hour, &dummy, &min, &dummy, &sec);
          ForcedFirstEpoch_ms 
            = (int64_t)(ConvertDateTimeToGPSsec(year, month, day, hour, min, sec)
                        *1000.0 + 0.5);
        }
        else
        {
          (void)sscanf(ssn_optarg, "%d%c%d%c%lf",
                       &hour, &dummy, &min, &dummy, &sec);
          ForcedFirstEpoch_ms = hour*3600000 + min*60000 + (int64_t)(sec*1000+0.5);
        }
        break;
        
      case 'e':
        /* Last time to include in the file */
        if (strchr(ssn_optarg, '-') != NULL) {
          (void)sscanf(ssn_optarg, "%d%c%d%c%d%c%d%c%d%c%lf",
                       &year, &dummy, &month, &dummy, &day, &dummy,
                       &hour, &dummy, &min, &dummy, &sec);
          ForcedLastEpoch_ms 
            = (int64_t)(ConvertDateTimeToGPSsec(year, month, day, hour, min, sec)
                        *1000.0 + 0.5);
        }
        else
        {
          (void)sscanf(ssn_optarg, "%d%c%d%c%lf",
                       &hour, &dummy, &min, &dummy, &sec);
          ForcedLastEpoch_ms = hour*3600000 + min*60000 + (int64_t)(sec*1000+0.5);
        }
        break;
      case 'i':
        if (sscanf(ssn_optarg, "%lf", &Interval) != 1){
          fprintf(stderr, "Unparsable argument '%s'.\n", ssn_optarg);
          usage();
          return 3;
        }
        ForcedInterval_ms = (uint32_t)(Interval*1000.0+0.5);
        break;
      case 'f':
        strncpy(SBFFileName, ssn_optarg, sizeof(SBFFileName));
        SBFFileName[sizeof(SBFFileName)-1] = '\0';
        break;
      case 'o':
        strncpy(AsciiFileName, ssn_optarg, sizeof(AsciiFileName));
        AsciiFileName[sizeof(AsciiFileName)-1] = '\0';
        break;
      case 'm':
        OutputMeas = 1;
        break;
      case 'p':
        OutputPVTcar = 1;
        break;
      case 'g':
        OutputPVTgeo = 1;
        break;
      case 'c':
        OutputPVTCov = 1;
        break;
      case 'd':
        OutputDOP = 1;
        break;
      case 'a':
        OutputAttEuler = 1;
        break;
      case 's':
        OutputAttCovEuler = 1;
        break;
      case 'x':
        OutputExtEvent = 1;
        break;
      case 't':
        OutputReceiverStatus = 1;
        break;
      case 'n':
        OutputBaseStation = 1;
        break;
      case 'l':
        OutputBaseLine = 1;
        break;
      case 'k':
        OutputBaseLink = 1;
        break;
      case 'j':
        OutputExtSensorMeas = 1;
        break;
      case 'h':
        OutputGPSAlm = 1;
        break;
      case 'u':
        OutputAuxPos = 1;
        break;
      case 'v':
        VerboseMode = 1;
        break;
      case 'E':
        AcceptInvalidTime = false;
        break;
      case 'V':
        fprintf(stdout, "%s\n", VERSION_STRING);
        return 0;
        
      case '?': /* Returned if an unknown option given. */
        if ( isprint(ssn_optopt) )
          fprintf(stderr, "Unknown option -%c.\n", ssn_optopt);
        else
          fprintf(stderr, "Unknown option character \\x%x.\n",
                          (unsigned int)ssn_optopt);
        usage();
        return 3;
      default:
        usage();
        return 3;
      } /* EOF switch optionchar */
                      
  } /* EOF while ssn_getopt */
    
    
  /* If no SBFFileName has been given, then the program can not continue: */
  if ( strlen(SBFFileName) == 0 ) 
  {
    usage();
    return 3;
  }

  /* If no AsciiFileName has been given, then use "measasc.dat" as
   * default: */
  if ( strlen(AsciiFileName) == 0 ) 
  {
    strcpy(AsciiFileName, "measasc.dat");
  }

  CreateAsciiFile(SBFFileName, AsciiFileName, 
                  ForcedFirstEpoch_ms, ForcedLastEpoch_ms, ForcedInterval_ms);

  return 0;
}

