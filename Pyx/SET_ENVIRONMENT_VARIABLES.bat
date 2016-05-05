@echo off

SET current_directory=%~dp0

echo.
echo +------------------------------------------------------------+
echo +   Setting PYX_SRC_DIR to global variable                   
echo +   Current PYX_SRC_DIR : %PYX_SRC_DIR%               
echo +   New %PYX_SRC_DIR: %current_directory%
echo +   WARNING : This script need to be run as administrator !  
echo +------------------------------------------------------------+
echo.
echo Please wait ...
echo.

SETX -m PYX_SRC_DIR %current_directory%

echo.
echo +------------------------------------------------------------+
echo +   Done, if there is no error, you can compile Pyx projects !
echo +------------------------------------------------------------+
echo.

pause