; programm to solve factorial of integer
in
pop rax
push 1
pop rbx
call factorial
push rbx
out
hlt


:factorial

    ; rbx = rax
    push rax
    pop rbx

    ; rax -= 1
    push rax
    push 1
    sub
    pop rax

    ; if rax == 0 return
    push 1
    push rax
    je return

    ; rbx *= rax
    push rbx
    push rax
    mul
    pop rbx

    call factorial

    :return
    ret
