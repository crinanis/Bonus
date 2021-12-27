.586							; система команд (процессор Pentium)
.model flat, stdcall			; модель памяти, соглашение о вызовах
includelib kernel32.lib			; компановщику: компоновать с kernel32
includelib libucrt.lib			; для UCRT - universal C Run-Time library

ExitProcess PROTO: DWORD		; прототип функции для завершения процесса Windows

;-----------Standart functions-----------
includelib e:\!ПОИТ\2\First\ЯП\КП\LP_KP\Debug\StandartLibrary.lib
cat1 PROTO : DWORD, : DWORD
cat2 PROTO : DWORD, : DWORD, : DWORD
print PROTO : DWORD
printint PROTO : DWORD
isleap PROTO : DWORD
printcurrentdate PROTO
;----------------------------------------

.stack 4096

;---------------Literals---------------
.const

L6	sdword	8	 ; int literal
L8	sdword	12	 ; int literal
L9	sdword	3	 ; int literal
L10	sdword	10	 ; int literal
L11	sdword	6	 ; int literal
L12	sdword	4	 ; int literal
L13	sdword	9	 ; int literal
L14	sdword	15	 ; int literal
L15	sdword	21	 ; int literal
L36	byte	"boo,", 0
L37	sdword	1	 ; int literal
L40	sdword	1	 ; bool literal
L41	sdword	0	 ; bool literal
L42	sdword	1	 ; bool literal
L44	sdword	16	 ; int literal
L45	sdword	13	 ; int literal
L46	sdword	1	 ; int literal
L47	sdword	1	 ; int literal
L48	byte	"ksushabgffdddddddddddddddvsdcvsseves", 0
L49	byte	"grushaesvrsggggggggggggthrthesdefrgs", 0
L50	byte	"the result of concatination", 0
L51	sdword	0	 ; bool literal
L52	byte	"the result of inverting bool variable", 0
L53	byte	"the first element of array", 0
L54	sdword	0	 ; int literal
L55	sdword	0	 ; int literal
L56	sdword	0	 ; int literal
L57	sdword	7	 ; int literal
L58	sdword	1	 ; int literal
L59	byte	"max element of array", 0
L61	sdword	2016	 ; int literal
L63	sdword	2019	 ; int literal
L64	byte	"present date and time", 0
L66	sdword	0	 ; int literal
;--------------------------------------------


;----------------Variables-------------------
.data

x	sdword	0	 ; int variable
y	sdword	0	 ; int variable
z	sdword	0	 ; int variable
k	sdword	0	 ; int variable
m	sdword	0	 ; int variable
l	sdword	0	 ; int variable
sa	byte	255 dup(0)	 ; string variable
sb	byte	255 dup(0)	 ; string variable
sc	byte	255 dup(0)	 ; string variable
bn	byte	255 dup(0)	 ; string variable
bfs	sdword	0	 ; bool variable
bte	sdword	0	 ; bool variable
boo	byte	255 dup(0)	 ; string variable
sadc	sdword	0	 ; int variable
myArray sdword 12, 3, 10, 6, 4, 9, 15, 21
tmp1 byte 255 dup(0)
;--------------------------------------------

;----------------Functions-------------------

.code

f_sum PROC a : sdword, b : sdword

push a
push b
pop eax
pop ebx
add eax, ebx
push eax
pop sadc
mov eax, sadc
	ret
f_sum endp


f_saySomething PROC myname : sdword

push offset L36
mov edi, myname
push edi
push offset tmp1
call cat2
push offset tmp1
push offset boo
call cat1
push offset boo
call print
mov eax, L37
	ret
f_saySomething endp


f_Reverse PROC v : sdword

mov eax, L40
cmp eax, v
jne condition_end
mov eax, L41
	ret
condition_end: 
mov eax, L42
	ret
f_Reverse endp


main PROC

push L44
pop x
push x
call printint
push L45
pop y
push y
call printint
push x
push y
call f_sum
push eax
pop l
push l
call printint
push x
push y
pop eax
pop ebx
mul ebx
push eax
push x
push y
call f_sum
push eax
push l
push L46
pop ebx
pop eax
sub eax, ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
push L47
pop eax
pop ebx
div ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
pop z
push z
call printint
push offset L48
push offset sa
call cat1
push offset L49
push offset sb
call cat1
push offset L50
call print
push offset sa
push offset sb
push offset tmp1
call cat2
push offset tmp1
push offset sc
call cat1
push offset sc
call print
push offset sa
call f_saySomething
push eax
pop x
push L51
pop bfs
push bfs
call f_Reverse
push eax
pop bte
push offset L52
call print
push bte
call printint
push offset L53
call print
push myArray[4*0]
call printint
push L55
pop k
push myArray[4*0]
pop m
while_start: 
mov eax, L57
cmp eax, k
jb while_end
mov esi, k
mov eax, myArray[4*esi]
cmp eax, m
jbe condition_end
mov esi, k
push myArray[4*esi]
pop m
condition_end: 
push k
push L58
pop eax
pop ebx
add eax, ebx
push eax
pop k
jmp while_start
while_end: 
push offset L59
call print
push m
call printint
push L61
call isleap
push eax
pop x
push L63
call isleap
push eax
pop x
push offset L64
call print
call printcurrentdate
push eax
pop x
mov eax, L66
	ret
invoke ExitProcess, 0
main ENDP
end main
;----------------------------------------------
