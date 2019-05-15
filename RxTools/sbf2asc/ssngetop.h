/*
 * "ssngetop.h"
 *
 *   A declaration of "ssngetopt()", Septentrio's own implementation
 *   of the Posix "getopt()" function. Should conform to IEEE Std
 *   1003.1-2001, but not all functionalities are implemented.
 *
 *   The implementation has the following limitations:
 *     1. It is a pure 8-bit character implementation, it doesn't
 *        support locales, multibytes or wide characters at all.
 *     2. "opterr" is supposed set to 0 by the application, i.e. no
 *        message is output to "stderr" in case of error.
 *     3. No extention is supported. (No GNU extention, no '-W'
 *        option...)
 *
 * (c) 2003 Septentrio nv/sa, Belgium
 */

#ifndef SSNGETOP_H
#define SSNGETOP_H 1

#include "ssntypes.h"

extern FW_EXPORT char *ssn_optarg;

extern FW_EXPORT int ssn_optind;
extern FW_EXPORT int ssn_opterr;
extern FW_EXPORT int ssn_optopt;

int FW_EXPORT ssn_getopt(int argc, char * const argv[], const char *optstring);

#endif
/* End of "ssngetop.h" */

