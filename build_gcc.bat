@echo off
cls

rem Executable name
set ApplicationName="ScratchApp"

set CommonLinkerLibraries= -luser32 -lGdi32 -lWinmm

if not exist _build mkdir _build
pushd _build
del *.* /Q

g++ ..\_source\win32_main.cpp -o %ApplicationName%_x64.exe -std=c++11 -static-libgcc -static-libstdc++ -mwindows -Og %CommonLinkerLibraries%
popd