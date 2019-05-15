/*******************************************************************************
**                    Septentrio Satellite Navigation N.V                     **
**  ************************************************************************  **
**  ************************ COPYRIGHT INFORMATION *************************  **
**  This program contains proprietary information which is a trade secret of  **
**  Septentrio N.V. and also is protected as an unpublished work under        **
**  applicable copyright laws. Recipient is to retain this program in         **
**  confidence and is not permitted to use or make copies thereof other than  **
**  as permitted in a written agreement with Septentrio N.V.                  **
**  All rights reserved. Company confidential.                                **
**  ************************************************************************  **
*******************************************************************************/

/**
 *  \file "mscssntypes.h"
 *  \brief Declaration of Septentrio types for Microsoft C/C++ compiler.
 *  \ingroup ssntypes
 *
 *  \par Copyright:
 *    (c) 2007 - Septentrio Satellite Navigation NV/SA, Belgium
 */
#ifndef MSCSSNTYPES_H
#define MSCSSNTYPES_H 1 /**< To avoid multiple inclusions. */

#include "mscstdint.h"
#include "mscinttypes.h"
#include "float.h"
// since MSVC 2013 the stdbool.h is available
#if (_MSC_VER >= 1800)
#include <stdbool.h>
#ifndef __BOOL_DEFINED
#define __BOOL_DEFINED
#endif
#endif

#if !defined(__BOOL_DEFINED)
/* Matlab requires the bool to be 1byte => all MSC builds with bool on 1 byte */
# define  true  1 /**< TRUE */
# define  false 0 /**< FALSE */
# define  bool  uint8_t /**< BOOL */
# define  __bool_true_false_are_defined 1 /**< BOOL is defined */
#endif
#define __func__ __FUNCTION__   /** Microsoft version of C99 keyword */

#if defined(SSN_DLL)
# if defined(FW_MAKE_DLL)
#   define  FW_EXPORT __declspec(dllexport) /**< Exporting for DLL */
# else
#   define  FW_EXPORT __declspec(dllimport) /**< Importing for DLL */
# endif
#else
# define  FW_EXPORT /**< Not defined */
#endif

#define snprintf        slprintf   /**< MS C/C++ definition */
#define strcasecmp      _strcmpi    /**< MS C/C++ definition */
#define strncasecmp     _strnicmp   /**< MS C/C++ definition */
#if (_MSC_VER >= 1700)
# include <math.h>
#else
# define isfinite        _finite     /**< MS C definition */
#endif
#if (!defined (__cplusplus) && (!defined (inline)))
# define inline __inline /**< MS C definition */
#endif

int FW_EXPORT slprintf(char *buffer, size_t count, const char *fmt, ...);

#endif
