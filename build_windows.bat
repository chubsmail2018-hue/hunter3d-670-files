@echo off
setlocal

set GODOT_EXE=%GODOT_EXE%
if "%GODOT_EXE%"=="" set GODOT_EXE="C:\Program Files\Godot\Godot_v4.2.2-stable_win64.exe"

if not exist %GODOT_EXE% (
    echo Godot export executable was not found at %GODOT_EXE%
    echo Install Godot 4.2.x and export templates, then set GODOT_EXE or update this script.
    exit /b 1
)

mkdir build\Windows 2>nul

%GODOT_EXE% --headless --export-release "Windows Desktop" build\Windows\Hunter3D.exe

if exist build\Windows\Hunter3D.exe (
    echo Export succeeded: build\Windows\Hunter3D.exe
) else (
    echo Export failed. Make sure the project has export presets and the export templates are installed.
    exit /b 1
)
