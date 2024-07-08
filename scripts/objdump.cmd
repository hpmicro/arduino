@echo off
rem Copyright 2024 hpmicro
rem SPDX-License-Identifier: BSD-3-Clause

setlocal enabledelayedexpansion
set TOOL_PATH=%1%
set ELF_FILE=%2%
set ASM_FILE_NAME=%3%

echo "Generating ASM file:"
!TOOL_PATH! -s -d !ELF_FILE! > !ASM_FILE_NAME!
