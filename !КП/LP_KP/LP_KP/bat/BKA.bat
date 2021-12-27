echo "BKA-2021"
timeout /t 2
start "" e:\LP_KP\Debug\LP_KP.exe -in:file.txt -out:e:\LP_KP\BKA-2021_asm\BKA-2021_asm.asm  m l i
timeout /t 30
echo (get-content -path e:\LP_KP\BKA-2021_asm\BKA-2021_asm.asm)[-1] | powershell -command -
echo "BKA-2021 asm"
start "" e:\LP_KP\BKA-2021_asm\BKA-2021_asm.asm
call C:\Users\budan\Desktop\bat\asm.bat
pause