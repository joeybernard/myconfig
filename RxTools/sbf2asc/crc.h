/*
 * "crc.h"
 *
 *      Declaration of functions to compute and validate a CRC.
 *
 * (c) 2000-2006 Septentrio nv/sa, Belgium
 */

#ifndef CRC_H
#define CRC_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "ssntypes.h"
//#include "sbfdef.h"

/*---------------------------------------------------------------------------*/
/* This function computes the CRC of a buffer "buf" of "buf_length" bytes. */

uint16_t FW_EXPORT CRC_compute16CCITT(const void * buf, size_t buf_length);
uint16_t FW_EXPORT CRC_compute16_SBG(const void * buf, size_t buf_length);

/*---------------------------------------------------------------------------*/
/* Returns true if the CRC check of the SBFBlock is passed. */

bool FW_EXPORT CRCIsValid(const void *Mess);

#ifdef __cplusplus
}
#endif

#endif
