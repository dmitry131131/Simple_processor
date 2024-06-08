; Compile global variables
push 0
pop rpx
;=======================================
push rpx          ; save old rpx value
call main         ; Jump to start point
hlt               ; End of program

; Function declaration with name: "главная"
:main
; Defined variable with name: "ф"
push 0
pop [rpx+0]  ; Variable with name: "ф"
; Defined variable with name: "фф"
push 0
pop [rpx+1]  ; Variable with name: "фф"
; Defined variable with name: "ффф"
push 0
pop [rpx+2]  ; Variable with name: "ффф"
; While 0 section
:While_next_0
push [rpx+0]     ; Variable with name: "(null)"
push 0
ja Skip_scope_0
push 0
pop [rpx+1]  ; Variable with name: "фф"
; While 1 section
:While_next_1
push [rpx+1]     ; Variable with name: "(null)"
push 1000
ja Skip_scope_1
push 0
pop [rpx+2]  ; Variable with name: "ффф"
; While 2 section
:While_next_2
push [rpx+2]     ; Variable with name: "(null)"
push 1000
ja Skip_scope_2
; Print function
push 1
out
push [rpx+2]     ; Variable with name: "(null)"
push 1
add
pop [rpx+2]  ; Variable with name: "ффф"
jmp While_next_2
:Skip_scope_2        ; End of if 2 section

push [rpx+1]     ; Variable with name: "(null)"
push 1
add
pop [rpx+1]  ; Variable with name: "фф"
jmp While_next_1
:Skip_scope_1        ; End of if 1 section

push [rpx+0]     ; Variable with name: "(null)"
push 1
add
pop [rpx+0]  ; Variable with name: "ф"
jmp While_next_0
:Skip_scope_0        ; End of if 0 section

pop rpx
ret
