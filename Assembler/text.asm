push 3
in
push 1
pop rax
pop [rax+1]
push [rax+1]
add
call hff
hlt

:hff
    out
    ret
