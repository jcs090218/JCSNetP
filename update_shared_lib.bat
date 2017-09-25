@echo off
:: ========================================================================
:: $File: update_shared_lib.bat $
:: $Date: 2017-04-09 21:59:25 $
:: $Revision: $
:: $Creator: Jen-Chieh Shen $
:: $Notice: See LICENSE.txt for modification and distribution information
::                    Copyright (c) 2017 by Shen, Jen-Chieh $
:: ========================================================================


:: DESCRIPTION(jenchieh): preapre for running the program.

set JCSNetP_DLL_RELEASE=JCSNetP.dll
set JCSNetP_DLL_DEBUG=JCSNetPd.dll

echo ----------------------------
echo -- List of shared file:
echo ----------------------------
echo ** Release shared lib file list: **
echo %JCSNetP_DLL_RELEASE%

echo.

echo ** Debug shared lib file list: **
echo %JCSNetP_DLL_DEBUG%

echo.
echo.

echo Copying shared library files to program directory.
echo -------------------------------

cd "Build/debug/package"

copy "%JCSNetP_DLL_DEBUG%" "../program/"
copy "%JCSNetP_DLL_DEBUG%" "../example/client/"
copy "%JCSNetP_DLL_DEBUG%" "../example/server/"

:: Back to project root directory.
cd "../../../"

cd "Build/release/package"

copy "%JCSNetP_DLL_RELEASE%" "../program/"
copy "%JCSNetP_DLL_RELEASE%" "../example/client/"
copy "%JCSNetP_DLL_RELEASE%" "../example/server/"

:: Back to project root directory.
cd "../../../"

echo -------------------------------
echo Done copying shared library files...
