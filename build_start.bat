@echo off
:: 2. Initialisation fichiers
echo Step 1 - Init

setlocal enabledelayedexpansion
echo Debut de la recherche...
echo.

echo Dossier de lancement %cd%
echo.

echo Step 2 - Search Files
:: 2. Cherche tout les .c dans le dossier actuel et les sous-dossiers (/R)
for /R %%f in (*.c) do (
    @REM echo Fichier trouve : %%f
	set "SOURCES=!SOURCES! "%%f""
)
echo.
echo Fin de la recherche
echo.
@REM echo Fichier trouves : !SOURCES!
echo Fichier trouves !

:: 3. Compilation fichier .c
echo.
@REM echo Compilation de : !SOURCES!
echo Compilation des fichiers en cours...

gcc !SOURCES! -o app.exe

:: 4. Vérification
if %errorlevel% neq 0 (
	echo ECHEC de la compilation.
	pause
	exit /b
)

echo Lancement du programme...
echo -------------------------
app.exe
echo.
pause