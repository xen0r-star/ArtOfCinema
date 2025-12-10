@echo off
:: Step 1 - Initialisation fichiers
echo Step 1 - Init

setlocal enabledelayedexpansion
echo Debut de la recherche...
echo.

echo Dossier de lancement %cd%
echo.

:: Step 2 - Cherche tout les .c dans le dossier actuel et les sous-dossiers (/R)
echo Step 2 - Search Files
for /R %%f in (*.c) do (
    @REM echo Fichier trouve : %%f
	set "SOURCES=!SOURCES! "%%f""
)
echo.
echo Fin de la recherche
echo.
@REM echo Fichier trouves : !SOURCES!
echo Fichier trouves !

:: Step 3 - Compilation fichier .c
echo.
@REM echo Compilation de : !SOURCES!
echo Step 3 - Compilation of the files in progress...
windres src\resources\resource.rc -O coff -o resource.o
gcc !SOURCES! resource.o -o src\ArtOfCinema.exe -Wall -Wextra -O2

del resource.o

:: Step 4 - Vérification
if %errorlevel% neq 0 (
	echo ECHEC de la compilation.
	pause
	exit /b
)

echo Step 4 - No errors of compilation

:: Step 5 - Lancement du programme
echo Step 5 - Lancement du programme...
:: Attente du lancement (affichage erreur)
TIMEOUT /T 3 /NOBREAK
echo -------------------------
cd src
ArtOfCinema.exe
echo.
pause