/**
 *  \file "ssntypes.h"
 *  \brief Declaration of Septentrio types.
 *  \ingroup ssntypes
 *
 *  Declarations of Septentrio types and implementation of common C types which
 *  are not implemented by every compiler.
 *
 *  If your compiler does not support the standard C99 types from \p stdint.h
 *  and \p stdbool.h, please define them for your platform. \n
 *  This is already done for the Microsoft C/C++ compiler.
 *
 *  The \p FW_EXPORT macro is foreseen for using the code to build a DLL with
 *  the Microsoft C/C++ compiler.
 *
 *  \par Copyright:
 *    (c) 2000-2015 Copyright Septentrio NV/SA. All rights reserved.
 */

#ifndef SSNTYPES_H
#define SSNTYPES_H 1 /**< To avoid multiple inclusions. */

#ifdef __linux__
# ifndef FW_EXPORT
#  ifdef ENABLE_VISIBILITY
#   define FW_EXPORT __attribute__((visibility("default"))) 
#  else
#   define FW_EXPORT
#  endif
# endif
#endif

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || defined(__GNUC__) || defined(__ARMCC__)
#  include <stdint.h>
#  include <stdbool.h>
#else
#  ifdef _MSC_VER
#    include "mscssntypes.h"
#  endif
#endif

#ifndef FW_EXPORT
#  define FW_EXPORT /**< For making a DLL with the Microsoft C/C++ compiler. */
#endif

#endif
/* End of "ifndef SSNTYPES_H" */
