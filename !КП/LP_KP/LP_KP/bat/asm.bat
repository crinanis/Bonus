call "e:\SOFT\Visual Studio\VC\Auxiliary\Build\vcvarsall.bat" x86
ml /c /coff  e:\LP_KP\BKA-2021_asm\BKA-2021_asm.asm
link /OPT:NOREF /DEBUG BKA-2021_asm.obj  /SUBSYSTEM:CONSOLE /NODEFAULTLIB:library
call C:\Users\budan\Desktop\bat\BKA-2021_asm.exe
pause