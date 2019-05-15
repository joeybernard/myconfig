/**
 *  \file "sbfsigtypes.h"
 *  \brief Declaration of an enumeration for satellite signals.
 *  \ingroup sbfdata
 *
 *  Declaration and definition of an enumeration for satellite signals.
 *
 *  \par Copyright:
 *    (c) 2000-2015 Copyright Septentrio NV/SA. All rights reserved.
 */

#ifndef SBFSIGTYPES_H
#define SBFSIGTYPES_H 1               /*!< To avoid multiple inclusions */


/** Enumeration of the different signal modulations.
 *  It is important not to mix signal types from different constellations. */

typedef enum {
  L1CA = 0,    /**< GPS L1 C/A (The first item must start at 0.) */
  L1P,         /**< GPS L1 P(Y)       */
  L2P,         /**< GPS L2 P(Y)       */
  L2C,         /**< GPS L2C           */
  L5,          /**< GPS L5 I/Q        */

  L1CAQZS = 6,
  L2CQZS,

  L1CAGLO = 8, /**< GLONASS L1 C/A    */
  L1PGLO,      /**< - Do not use -    */
  L2PGLO,      /**< GLONASS L2 P      */
  L2CAGLO,     /**< GLONASS L2 C/A    */
  L3GLO,       /**< GLONASS L3        */

  L5IRNSS = 15,/**< IRNSS L5          */

  L1A = 16,    /**< Galileo L1 A      */
  L1BC,        /**< Galileo L1 BC     */
  E6A,         /**< Galileo E6 A      */
  E6BC,        /**< Galileo E6 BC     */
  E5a,         /**< Galileo E5a I/Q   */
  E5b,         /**< Galileo E5b I/Q   */
  E5,          /**< Galileo E5 AltBOC */

  MSS_LBAND,   /**< MSS L-Band signal */
  
  L1GEO = 24,  /**< SBAS L1 C/A       */
  L5GEO,       /**< SBAS L5           */
  L5QZS,
  
  E2CMP = 28,  /**< Compass E2/B1     */
  E5bCMP,      /**< Compass E5b/B2    */
  B3CMP,       /**< Compass B3        */

  SIG_LAST = 32,/**< (This must be the last item in the list, never delete it.) */
  SIG_INVALID = 255
} SignalType_t;


#endif
/* End of "ifndef SBFSIGTYPES_H" */
