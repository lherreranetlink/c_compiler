.386
.model flat, stdcall
option casemap:none
include \masm32\macros\macros.asm
include \masm32\include\masm32.inc
include \masm32\include\kernel32.inc
include \masm32\macros\macros.asm
includelib \masm32\lib\masm32.lib
includelib \masm32\lib\kernel32.lib

.code
begin:
push 7.2
push 3.5
pop ebx
pop eax
add eax, ebx
push eax
push 2.8
pop ebx
pop eax
add eax, ebx
push eax
pop _So3a
push 3
push 4
pop ebx
pop eax
cmp eax, ebx
jg T0
push 0
jmp E0
T0:
push 1
E0:
push _So3a
pop ebx
pop eax
cmp eax, ebx
jl T1
push 0
jmp E1
T1:
push 1
E1:
pop _b
exit
end begin
