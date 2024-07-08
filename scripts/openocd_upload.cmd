@echo off
rem Copyright 2024 hpmicro
rem SPDX-License-Identifier: BSD-3-Clause

setlocal enabledelayedexpansion
set OPENOCD_PATH=%1%
set ARG1=%2%
set ARG2=%3%
set ARG3=%4%
set ELF_FILE=%5%
set BUILD_TYPE=%6%
set "NORMALIZED_FILE_NAME=%ELF_FILE:\=/%"
set OCD_CMD=program \"!NORMALIZED_FILE_NAME!\" verify reset exit
set OCD_CFG=-f !ARG1! -f !ARG2! -f !ARG3!
set LOAD_IMAGE_CMD=load_image !NORMALIZED_FILE_NAME!
set OCD_CMD_RAM=-c "init" -c "reset halt" -c "!LOAD_IMAGE_CMD!" -c "set_reg {pc 0}" -c "resume" -c "exit"
if "%BUILD_TYPE%" == "RAM" (
    %OPENOCD_PATH% %OCD_CFG% %OCD_CMD_RAM%
) else (
    %OPENOCD_PATH% %OCD_CFG% -c "%OCD_CMD%"
)