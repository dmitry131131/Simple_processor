; programm to solve factorial of integer
in
pop rax
push 1
push 0
pop rbx
pop [rbx+1]
call factorial
push [rbx+1]
out
hlt


:factorial
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
    push [rbx+1]
    push rax
    mul
    pop [rbx+1]

    call factorial

    :return
    ret
