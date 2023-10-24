push 3
in
pop rax
push rax
add
call hff
hlt


:hff
    out
    ret
