; Compile global variables
push 0
pop rpx
;=======================================
push rpx          ; save old rpx value
call main         ; Jump to start point
hlt               ; End of program

; Function declaration with name: "главная"
:main
; Defined variable with name: "a"
; Print in()
in
pop [rpx+0]  ; Variable with name: "a"
; Defined variable with name: "b"
; Print in()
in
pop [rpx+1]  ; Variable with name: "b"
; Defined variable with name: "c"
; Print in()
in
pop [rpx+2]  ; Variable with name: "c"
; Compile parameter
push [rpx+2]     ; Variable with name: "(null)"
; Compile parameter
push [rpx+1]     ; Variable with name: "(null)"
; Compile parameter
push [rpx+0]     ; Variable with name: "(null)"
; Saving memory stack pointer
push rpx       ; Save old stack pointer
push rpx       ; Calculate new stack pointer
push 3
add
pop rpx
; call function with name: "решить"
call Function_39
pop rpx
ret

; Function declaration with name: "решить"
:Function_39
; Save old rpx value in rbx
pop rbx
; Accepting parameters
; Parameter declaration with name: "a"
pop [rpx+0]
; Parameter declaration with name: "b"
pop [rpx+1]
; Parameter declaration with name: "c"
pop [rpx+2]
; Repair old rpx value to stack
push rbx
; If 0 section
push [rpx+0]     ; Variable with name: "(null)"
push 0
jne Skip_scope_0
; Compile parameter
push [rpx+2]     ; Variable with name: "(null)"
; Compile parameter
push [rpx+1]     ; Variable with name: "(null)"
; Saving memory stack pointer
push rpx       ; Save old stack pointer
push rpx       ; Calculate new stack pointer
push 3
add
pop rpx
; call function with name: "не_квадратное"
call Function_196
; Return
push 0
pop rax
pop rpx
ret
:Skip_scope_0        ; End of if 0 section

; Defined variable with name: "d"
push [rpx+1]     ; Variable with name: "(null)"
push [rpx+1]     ; Variable with name: "(null)"
mul
push 4
push [rpx+0]     ; Variable with name: "(null)"
mul
push [rpx+2]     ; Variable with name: "(null)"
mul
sub
pop [rpx+3]  ; Variable with name: "d"
; If 1 section
push [rpx+3]     ; Variable with name: "(null)"
push 0
jae Skip_scope_1
; Print function
push 0
push 2
sub
out
; Return
push 0
pop rax
pop rpx
ret
:Skip_scope_1        ; End of if 1 section

; If 2 section
push [rpx+3]     ; Variable with name: "(null)"
push 0
jne Skip_scope_2
; Print function
push 1
out
; Print function
push 0
push [rpx+1]     ; Variable with name: "(null)"
sub
push 2
push [rpx+0]     ; Variable with name: "(null)"
mul
div
out
; Return
push 0
pop rax
pop rpx
ret
:Skip_scope_2        ; End of if 2 section

; If 3 section
push [rpx+3]     ; Variable with name: "(null)"
push 0
jbe Skip_scope_3
; Print function
push 2
out
; Print function
; Print sqrt
push [rpx+3]     ; Variable with name: "(null)"
sqrt
push [rpx+1]     ; Variable with name: "(null)"
sub
push 2
push [rpx+0]     ; Variable with name: "(null)"
mul
div
out
; Print function
push 0
push [rpx+1]     ; Variable with name: "(null)"
sub
; Print sqrt
push [rpx+3]     ; Variable with name: "(null)"
sqrt
sub
push 2
push [rpx+0]     ; Variable with name: "(null)"
mul
div
out
; Return
push 0
pop rax
pop rpx
ret
:Skip_scope_3        ; End of if 3 section

pop rpx
ret

; Function declaration with name: "не_квадратное"
:Function_196
; Save old rpx value in rbx
pop rbx
; Accepting parameters
; Parameter declaration with name: "b"
pop [rpx+0]
; Parameter declaration with name: "c"
pop [rpx+1]
; Repair old rpx value to stack
push rbx
; If 4 section
push [rpx+0]     ; Variable with name: "(null)"
push 0
jne Skip_scope_4
; If 5 section
push [rpx+1]     ; Variable with name: "(null)"
push 0
jne Skip_scope_5
; Print function
push 1000
out
; Print function
push 0
out
; Print function
push 0
out
; Return
push 0
pop rax
pop rpx
ret
:Skip_scope_5        ; End of if 5 section

; Print function
push 0
out
; Print function
push 0
out
; Print function
push 0
out
; Return
push 0
pop rax
pop rpx
ret
:Skip_scope_4        ; End of if 4 section

; Print function
push 1
out
; Print function
push 0
push [rpx+1]     ; Variable with name: "(null)"
sub
push [rpx+0]     ; Variable with name: "(null)"
div
out
; Return
push 0
pop rax
pop rpx
ret
pop rpx
ret
