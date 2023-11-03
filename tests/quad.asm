; programm to solve quadratic equation  
; [1] - count of roots
; [2] - first root
; [3] - second root
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
ja complex

; if rdx == 0
push 0
push rdx
je one_root

push 2
out

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

; if one root 
:one_root
    push 1
    out 1

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
    hlt

; function if equation is lineral
:lineral
    ; if rbx == 0
    push 0
    push rbx
    je check_c

    ; -rcx
    push -1
    push rcx
    mul

    push rbx
    div
    push 1
    out
    out
    hlt

    :check_c
        ; if rcx == 0
        push rcx
        push 0
        jne noroots
        push 10000
        out
        hlt

    :noroots
        push -99
        out 
        hlt

    hlt

; function outs -99 if equation hasn't got roots
:noteq
    push -99
    out 
    hlt

; outs -2 if roots are complex
:complex
    push -2
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
