push 3
in
pop rax
push [rax+3]
add
call hff
hlt


:hff
    out
    ret
