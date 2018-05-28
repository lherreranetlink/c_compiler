.386
.model flat, stdcall
option casemap:none
include \masm32\macros\macros.asm
include \masm32\include\masm32.inc
include \masm32\include\kernel32.inc
include \masm32\macros\macros.asm
includelib \masm32\lib\masm32.lib
includelib \masm32\lib\kernel32.lib

.data
_So3a dword 0
_R dword 0
_e dword 0
_l508 dword 0
_Va dword 0
_xg dword 0

.code
begin:
push 72
push 3.5
pop ebx
pop eax
add eax, ebx
push eax
push 2
pop ebx
pop eax
add eax, ebx
push eax
pop _So3a
push 02
pop _R
push 52
pop _e
push 1
pop _l508
push 5
pop _Va
push 3
pop _xg
push _e
pop eax
print str$(eax), 13, 10
exit
end begin
