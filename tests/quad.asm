; programm to solve quadratic equation  
; enter section
in      ; A
in      ; B
in      ; C
pop rcx
pop rbx
pop rax

; if rax == 0
push rax
push 0
je lineral

; solve Descriminant
call descr

; if rdx < 0
push 0
push rdx
jb noteq

; solve first root
push -1
push rbx
mul
push rdx
sqrt
sub
push 2
push rax
mul
div
out

; solve second root
push -1
push rbx
mul
push rdx
sqrt
add
push 2
push rax
mul
div
out

hlt

; function if equation is lineral
:lineral
    ; if rbx == 0
    push 0
    push rbx
    je noteq

    ; -rcx
    push -1
    push rcx
    mul

    push rbx
    div
    out

    hlt

; function outs -99 if equation hasn't got roots
:noteq
    push -99
    out 
    hlt

; sunction solving descriminant of quadratic equation
:descr
    push rbx
    push rbx
    mul
    push 4
    push rax
    push rcx
    mul
    mul
    sub
    pop rdx
    ret
