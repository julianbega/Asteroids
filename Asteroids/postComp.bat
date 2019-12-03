@echo off
echo Copiando los archivos.
copy %1raylib.dll %2 /y
mkdir "%2res\assets"
xcopy "%1\res\assets" "%2\res\assets" /s /e /y /i
echo Finalizada copia de archivos.
pause