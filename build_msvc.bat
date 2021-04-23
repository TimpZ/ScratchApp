@echo off
cls

rem Executable name
set ApplicationName="ScratchApp"

rem Set this to 1 if this build is not to be released publically
set InternalBuild=1

rem Set this to 1 if we're enabling debugging code and error checking that draws performance
set SlowBuild=1

rem Get The current time and put in TimeStamp
set Hour=%time:~0,2%
if "%Hour:~0,1%" == " " SET Hour=0%Hour:~1,1%
set TimeStamp=%date:~6,4%-%date:~3,2%-%date:~0,2%_%Hour%-%time:~3,2%-%time:~6,2%

set CustomFlags= -DBUILD_INTERNAL=%InternalBuild% -DBUILD_SLOW=%SlowBuild%
set CommonCompilerFlags= -MT -nologo -GR- -EHsc -EHa- -Od -Oi -fp:fast -WX -W4 -wd4201 -wd4100 -wd4189 -wd4333 -wd4505 %CustomFlags% -FC -Zi
set SharedLinkerFlags= -incremental:no -DEBUG:FULL -opt:ref
set CommonLinkerLibraries= user32.lib Gdi32.lib Winmm.lib
 
rem 64-bit build
pushd _build
del *.* /Q
cl %CommonCompilerFlags% -Fm%ApplicationName%_x64.map ..\_source\win32_main.cpp /link %SharedLinkerFlags% %CommonLinkerLibraries% /out:%ApplicationName%_x64.exe
popd