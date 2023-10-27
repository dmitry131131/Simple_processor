; programm to solve factorial of integer
in
pop [1]
push 1
pop [2]
call factorial
push [2]
out
hlt


:factorial
    ; if rax == 0 return
    push 1
    push [1]
    je return

    ; rbx *= rax
    push [2]
    push [1]
    mul
    pop [2]
    
    ; rax -= 1
    push [1]
    push 1
    sub
    pop [1]

    call factorial

    :return
    ret
