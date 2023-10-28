; programm to draw circle 
:ret
in
pop rax
push rax
push 1000
je stop

push 1
pop [rax]

draw

jmp ret

:stop
hlt
