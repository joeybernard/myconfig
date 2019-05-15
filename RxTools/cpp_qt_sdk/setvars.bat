@echo off

REM Edit the following variables to reflect the actual installation paths 
REM on your system:

set VSDIR=C:\Program Files (x86)\Microsoft Visual Studio 9.0
set WINSDKDIR=C:\Program Files\Microsoft SDKs\Windows\v7.1
set QTDIR=c:\qt\4.8.2

REM Do not edit below

set INCLUDE=%VSDIR%\VC\include;%WINSDKDIR%\Include;%INCLUDE%
set LIB=%VSDIR%\VC\lib;%WINSDKDIR%\LIB;%LIB%
set PATH=%QTDIR%\bin;%VSDIR%\VC\bin;%WINSDKDIR%\bin;%VSDIR%\Common7\IDE;%PATH%