; programm to draw circle
; rax -- x
; rbx -- y

push 5
pop rcx

; main function
:main
    push rcx
    out

    push 1
    pop [110]

    push 1
    pop [99]

    push 1
    pop [219]

    ; rcx--
    push rcx
    push -1
    add
    pop rcx

    ; if rcx == 0
    push rcx
    push 0
    je stop

    ; rcx += 10
    push 10
    push 5
    push rcx
    sub
    mul
    push rcx
    add
    pop rbx

    call fill

    jmp main

; fill line
:fill
    push 1
    pop [rbx+99]
    
    ; -rbx
    push rbx
    push -1
    mul
    pop rbx

    push 1
    pop [rbx+99]

    ; -rbx
    push rbx
    push -1
    mul
    pop rbx

    ret

; draw terrain and stop programm
:stop
    draw
    hlt
