@echo off
rem Copyright 2024 hpmicro
rem SPDX-License-Identifier: BSD-3-Clause

setlocal enabledelayedexpansion
set BUILD_TYPE=%1%
set SOC_NAME=%2%
set ELF_FILE=%3%
set BUILD_TMP_DIR=%4%
set "NORMALIZED_FILE_NAME=%ELF_FILE:\=/%"

if "%BUILD_TYPE%" == "RAM" (
    echo "Using RAM build type, this build type will lost all program data once the device is reset"
    echo !BUILD_TMP_DIR!/download.jlink
    echo loadfile !ELF_FILE!
    echo loadfile !ELF_FILE! > !BUILD_TMP_DIR!/download.jlink
    echo SetPC 0 >> !BUILD_TMP_DIR!/download.jlink
    echo Go >> !BUILD_TMP_DIR!/download.jlink
    echo q >> !BUILD_TMP_DIR!/download.jlink
) else (
    echo !BUILD_TMP_DIR!/download.jlink
    echo erase > !BUILD_TMP_DIR!/download.jlink
    echo loadfile !ELF_FILE!
    echo loadfile !ELF_FILE! >> !BUILD_TMP_DIR!/download.jlink
    echo r >> !BUILD_TMP_DIR!/download.jlink
    echo Go >> !BUILD_TMP_DIR!/download.jlink
    echo q >> !BUILD_TMP_DIR!/download.jlink
)
JLink.exe -device !SOC_NAME! -if jtag -JTAGConf -1,-1 -autoconnect 1 -speed 4000 !BUILD_TMP_DIR!/download.jlink
