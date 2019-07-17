@echo off
setlocal
for /f "tokens=4-5 delims=[.] " %%i in ('ver') do @(if %%i==Version (set VERSION=%%j) else (set VERSION=%%i))
if %VERSION% GEQ 10 (
  REM uninstall arduino drivers on windows 10 - they just hurt composite USB enumeration 
  if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
    drivers\dpinst-amd64.exe /PATH %cd%\drivers\prewin10 /U %ARGS%
  ) ELSE IF "%PROCESSOR_ARCHITEW6432%" == "AMD64" (
    drivers\dpinst-amd64.exe /PATH %cd%\drivers\prewin10 /U %ARGS%
  ) ELSE (
    drivers\dpinst-x86.exe /PATH %cd%\drivers\prewin10 /U %ARGS%
  )
  exit /b 0
)
endlocal

REM dpinst /PATH has problems with relative paths, so use absolute path.
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  drivers\dpinst-amd64.exe /PATH %cd%\drivers\prewin10 %ARGS%
) ELSE IF "%PROCESSOR_ARCHITEW6432%" == "AMD64" (
  drivers\dpinst-amd64.exe /PATH %cd%\drivers\prewin10 %ARGS%
) ELSE (
  drivers\dpinst-x86.exe /PATH %cd%\drivers\prewin10 %ARGS%
)

exit /b 0
