@echo off
REM Go to the Talon root directory
cd /d "%~dp0"

REM Define paths
set "TALON_DIR=%CD%"
set "BUILD_DIR=%TALON_DIR%\build"

REM Create build directory if it doesn't exist
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

REM Run CMake to generate build files for Ninja
cmake -B "%BUILD_DIR%" -G Ninja "%TALON_DIR%"

REM Check if CMake ran successfully
if errorlevel 1 (
    echo Error: Failed to run CMake.
    exit /b 1
)

REM Run the build system (Ninja) to compile the project
cmake --build "%BUILD_DIR%"

REM Check if the build succeeded
if errorlevel 1 (
    echo Error: Failed to build Talon package manager.
    exit /b 1
)

REM Move Talon executable and compile_commands.json to the root directory
move "%BUILD_DIR%\Talon.exe" "%TALON_DIR%\"
move "%BUILD_DIR%\compile_commands.json" "%TALON_DIR%\"

echo Talon package manager built successfully.
exit /b 0

