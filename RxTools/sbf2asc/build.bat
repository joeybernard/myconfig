Rem Batch script to compile "sbf2asc" with the
Rem Microsoft Visual C++ Toolkit 2003
Rem (c) 2000-2015 Copyright Septentrio NV/SA. All rights reserved.


cl -Ox -Zp4 sbf2asc.c sbfread.c ssngetop.c crc.c
