; programm to draw circle
; [1] -- x
; [2] -- y
; [10], [11] -- temp
; set start x and y values

push -25
pop [1]
push 25
pop [2]

push 2601
pop rcx
push 15
pop [4]    ; radius

; main function
:main
    call check
    push 1
    push [3]
    je fil
    :return_1

    call x+1

    ; rcx--
    push rcx
    push 1
    sub
    pop rcx
    ; if rcx == 0
    push rcx
    push 0
    je stop

    jmp main

; draw terrain and stop programm
:stop
    draw
    in
    hlt

; check x and y values for drawing
; ret [3] == 1 if yes and [3] == 0 if no
:check
    ; x^2 + y^2
    push [1]
    push [1]
    mul
    push [2]
    push [2]
    mul
    add
    pop [10]   ; temp

    push [4]
    push [4]
    mul
    pop [11]

    ; if x^2 + y^2 == radius^2
    call if_one
    
    ret

; [3] = 1
:if_one
    push [10]
    push [11]
    sub
    push [10]
    push [11]
    sub
    mul
    push 200
    jb one

    push 0
    pop [3]
    ret

    :one
        push 1
        pop [3]
        ret

; x+1 function
:x+1
    ; if rax == 26
    push 26
    push [1]
    je x=-1

    ; x += 1
        push 1
        push [1]
        add
        pop [1]
        ret

    ; x = -1
    :x=-1
        push -25
        pop [1]

        ; y -= 1
        push -1
        push [2]
        add
        pop [2]

        ; x += 1
        push 1
        push [1]
        add
        pop [1]

        ret

:fil
    call fillpixel
    jmp return_1

; fill pixel by x and y
:fillpixel
    push 25
    push [2]
    sub
    push 51
    mul
    push 25
    push [1]
    sub
    add
    push 100
    add
    pop rdx

    push 1
    pop [rdx]

    ret

