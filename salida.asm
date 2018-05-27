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
_Rq dword 0
_Jj dword 0
_B70K dword 0
_Y8 dword 0
_x dword 0
_wg7 dword 0

.code
begin:
push 72
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
push 6
push _xg
pop eax
imul -1
push eax
pop ebx
pop eax
mul ebx
push eax
push 6
push 88
pop ebx
pop eax
mul ebx
push eax
pop ebx
pop eax
cmp eax, ebx
jg T0
push 0
jmp E0
T0:
push 1
E0:
pop eax
cmp eax, 1
jne L0
push 9
pop _Rq
push 3
pop _Jj
push _Rq
push _Jj
pop ebx
pop eax
cmp eax, ebx
jl T1
push 0
jmp E1
T1:
push 1
E1:
pop eax
cmp eax, 1
jne L2
push _Jj
push _Rq
pop ebx
pop eax
sub eax, ebx
push eax
push 10
pop ebx
pop eax
div ebx
push eax
push 1
pop ebx
pop eax
add eax, ebx
push eax
pop _B70K
push _Rq
push 2
pop ebx
pop eax
add eax, ebx
push eax
pop eax
print str$(eax), 13, 10
push _Rq
push _B70K
pop ebx
pop eax
add eax, ebx
push eax
push 4
pop ebx
pop eax
sub eax, ebx
push eax
pop _Rq
push 12
pop _Y8
jmp E3
L2:
E3:
push _R
pop eax
cmp eax, 1
jne L4
B6:
push _R
pop eax 
cmp eax, 1
jne E7
push _Va
pop eax
cmp eax, 1
jne L8
B10:
push _Rq
push _Jj
pop ebx
pop eax
cmp eax, ebx
jl T2
push 0
jmp E2
T2:
push 1
E2:
pop eax 
cmp eax, 1
jne E11
push _Jj
push _Rq
pop ebx
pop eax
sub eax, ebx
push eax
push 10
pop ebx
pop eax
div ebx
push eax
push 1
pop ebx
pop eax
add eax, ebx
push eax
pop _B70K
push _Rq
push 2
pop ebx
pop eax
add eax, ebx
push eax
pop eax
print str$(eax), 13, 10
push _Rq
push _B70K
pop ebx
pop eax
add eax, ebx
push eax
push 4
pop ebx
pop eax
sub eax, ebx
push eax
pop _Rq
push 12
pop _Y8
jmp B10
E11:
jmp E9
L8:
push 23
pop eax
cmp eax, 1
jne L12
push _R
pop eax
cmp eax, 1
jne L14
B16:
push 1
pop eax 
cmp eax, 1
jne E17
push _R
pop eax
print str$(eax), 13, 10
jmp B16
E17:
jmp E15
L14:
E15:
jmp E13
L12:
E13:
E9:
jmp B6
E7:
jmp E5
L4:
E5:
push 43
push 10
push _R
push _l508
pop ebx
pop eax
add eax, ebx
push eax
pop ebx
pop eax
mul ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
pop _x
push 38
push _Y8
pop ebx
pop eax
add eax, ebx
push eax
pop eax
print str$(eax), 13, 10
jmp E1
L0:
push 98
pop _wg7
E1:
push _e
pop eax
print str$(eax), 13, 10
exit
end begin
