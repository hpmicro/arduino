
rem Copyright 2024 hpmicro
rem SPDX-License-Identifier: BSD-3-Clause
set CMD_EXEC=%1%/hpm_manufacturing_cmd.exe
set IMAGE_UTIL_EXEC=%1%\hpm_img_util.exe
set BIN_FILE=%3%
set BUILD_TMP_DIR=%2%
set "BUILD_TMP_DIR2=%BUILD_TMP_DIR:\=/%"
set VID=%4%
set PID=%5%
set BUILD_TYPE=%6%
set IMAGE_JSON_PATH=%BUILD_TMP_DIR%\image.json
set CMD_LINE_RAM=load-image %BUILD_TMP_DIR%\output_%BIN_FILE%
set CMD_LINE_FLASH=config-memory 0x10000 0x200" -r "write-memory 0x10000 0x80000400 %BUILD_TMP_DIR%/%BIN_FILE%

if "%BUILD_TYPE%" == "RAM" (
    echo "Using RAM build type, this build type will lost all program data once the device is reset"
    echo { > %IMAGE_JSON_PATH%
    echo     "boot_image": { >> %IMAGE_JSON_PATH%
    echo         "firmware_info": [ >> %IMAGE_JSON_PATH%
    echo                 { >> %IMAGE_JSON_PATH%
    echo                 "binary_path": "%BUILD_TMP_DIR2%/%BIN_FILE%", >> %IMAGE_JSON_PATH%
    echo                 "entry_point": "0", >> %IMAGE_JSON_PATH%
    echo                 "fw_type": "application", >> %IMAGE_JSON_PATH%
    echo                 "hash_type": "none", >> %IMAGE_JSON_PATH%
    echo                 "is_encrypted": false, >> %IMAGE_JSON_PATH%
    echo                 "load_addr": "0", >> %IMAGE_JSON_PATH%
    echo                 "offset": "auto" >> %IMAGE_JSON_PATH%
    echo             } >> %IMAGE_JSON_PATH%
    echo         ], >> %IMAGE_JSON_PATH%
    echo         "header": { >> %IMAGE_JSON_PATH%
    echo             "fuse_version": 0, >> %IMAGE_JSON_PATH%
    echo             "offset": "0", >> %IMAGE_JSON_PATH%
    echo             "sw_version": 0 >> %IMAGE_JSON_PATH%
    echo         } >> %IMAGE_JSON_PATH%
    echo     }, >> %IMAGE_JSON_PATH%
    echo     "output_path": "%BUILD_TMP_DIR2%/output_%BIN_FILE%" >> %IMAGE_JSON_PATH%
    echo } >> %IMAGE_JSON_PATH%
    %IMAGE_UTIL_EXEC% -- create_image %IMAGE_JSON_PATH%
    %CMD_EXEC% -c -u %VID%,%PID% -r "%CMD_LINE_RAM%"

) else (
    %CMD_EXEC% -c -u %VID%,%PID% -r "write-memory 0x0 0x200 [[0xfcf90002,0x07,0x100e,0x0]]" -r "%CMD_LINE_FLASH%"
)