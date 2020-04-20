.intel_syntax noprefix
.global main
.data
.LC0:
    .string "[ERROR] test%d: %d expected, but got %d\n"
.LC1:
    .string "hoge"
.LC2:
    .string "abc"
.LC3:
    .string "zyx"
.text
try:
    push rbp
    mov rbp, rsp
    sub rsp, 12
    mov [rbp-4], edi
    mov [rbp-8], esi
    mov [rbp-12], edx
    mov eax, [rbp-8]
    push rax
    mov eax, [rbp-12]
    push rax
    pop rdi
    pop rax
    cmp eax, edi
    setne al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend1
    lea rax, .LC0[rip]
    push rax
    mov eax, [rbp-4]
    push rax
    mov eax, [rbp-8]
    push rax
    mov eax, [rbp-12]
    push rax
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call printf@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
.Lend1:
    mov rsp, rbp
    pop rbp
    ret
test0:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 0
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test1:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 42
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test2:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 5
    push 20
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 4
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test3:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 12
    push 34
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 5
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    push 0
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test4:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 25
    push 2
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 10
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 6
    push 2
    pop rdi
    pop rax
    cltd
    idiv edi
    push rax
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test5:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 33
    push 4
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    push 2
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 45
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 50
    push 38
    push 2
    pop rdi
    pop rax
    cltd
    idiv edi
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test6:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 3
    push 1
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test7:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 0
    push 0
    push 3
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    push 2
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    push 10
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 0
    push 0
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test8:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 1
    push 0
    pop rdi
    pop rax
    cmp eax, edi
    setne al
    movzb eax, al
    push rax
    push 0
    push 3
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 1
    push 1
    pop rdi
    pop rax
    cmp eax, edi
    sete al
    movzb eax, al
    push rax
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    push 14
    push 2
    pop rdi
    pop rax
    cltd
    idiv edi
    push rax
    push 2
    push 3
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test9:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 1
    push 1
    pop rdi
    pop rax
    cmp eax, edi
    sete al
    movzb eax, al
    push rax
    push 2
    push 1
    pop rdi
    pop rax
    cltd
    idiv edi
    push rax
    push 0
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 1
    push 2
    pop rdi
    pop rax
    cmp eax, edi
    setne al
    movzb eax, al
    push rax
    push 0
    push 1
    push 1
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rdi
    pop rax
    cmp eax, edi
    setle al
    movzb eax, al
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 3
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test10:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 1
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 2
    pop rdi
    pop rax
    add rax, rdi
    push rax
    push 1
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test11:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 1
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test12:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    push 5
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 1
    pop rdi
    mov [rbp-8], edi
    push rdi
    pop rax
    push 3
    pop rdi
    mov [rbp-12], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    mov eax, [rbp-12]
    push rax
    mov eax, [rbp-8]
    push rax
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rdi
    mov [rbp-16], edi
    push rdi
    pop rax
    push 2
    mov eax, [rbp-16]
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 3
    pop rdi
    pop rax
    cltd
    idiv edi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test13:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    push 5
    push 3
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rax
    push 10
    push 2
    pop rdi
    pop rax
    cltd
    idiv edi
    push rax
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 2
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-8], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    mov eax, [rbp-8]
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 4
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test14:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 8
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    push 5
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test15:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    push 31415
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 100
    push 314
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rdi
    mov [rbp-8], edi
    push rdi
    pop rax
    push 2
    mov eax, [rbp-4]
    push rax
    mov eax, [rbp-8]
    push rax
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    push 3
    pop rdi
    pop rax
    cltd
    idiv edi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test16:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 0
    pop rax
    cmp rax, 0
    je .Lend2
    push 0
    pop rax
    mov rsp, rbp
    pop rbp
    ret
.Lend2:
    push 1
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test17:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 10
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    push 5
    pop rdi
    pop rax
    cltd
    idiv edi
    push rax
    push 2
    pop rdi
    pop rax
    cmp eax, edi
    sete al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend3
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
.Lend3:
    push 0
    push 10
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test18:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    push 10
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 0
    pop rdi
    mov [rbp-8], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    mov eax, [rbp-8]
    push rax
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lelse1
    mov eax, [rbp-4]
    push rax
    pop rdi
    mov [rbp-8], edi
    push rdi
    jmp .Lend4
.Lelse1:
    mov eax, [rbp-8]
    push rax
    pop rdi
    mov [rbp-4], edi
    push rdi
.Lend4:
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test19:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    push 1
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 1
    pop rdi
    mov [rbp-8], edi
    push rdi
.Lbegin1:
    mov eax, [rbp-4]
    push rax
    push 10
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend5
    mov eax, [rbp-4]
    push rax
    mov eax, [rbp-8]
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rdi
    mov [rbp-4], edi
    push rdi
    mov eax, [rbp-8]
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-8], edi
    push rdi
    jmp .Lbegin1
.Lend5:
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test20:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 1
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
.Lbegin2:
    mov eax, [rbp-4]
    push rax
    push 50
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend6
    mov eax, [rbp-4]
    push rax
    push 2
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rdi
    mov [rbp-4], edi
    push rdi
    jmp .Lbegin2
.Lend6:
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test21:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 1
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-4], edi
    push rdi
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test22:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    push 0
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 0
    pop rdi
    mov [rbp-8], edi
    push rdi
    pop rax
.Lbegin3:
    mov eax, [rbp-4]
    push rax
    push 11
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend7
    mov eax, [rbp-8]
    push rax
    mov eax, [rbp-4]
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-8], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-4], edi
    push rdi
    jmp .Lbegin3
.Lend7:
    mov eax, [rbp-8]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test23:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 1
    pop rdi
    mov [rbp-4], edi
    push rdi
.Lbegin4:
    mov eax, [rbp-4]
    push rax
    push 100
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend8
    push 32
    mov eax, [rbp-4]
    push rax
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend9
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
.Lend9:
    mov eax, [rbp-4]
    push rax
    push 2
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rdi
    mov [rbp-4], edi
    push rdi
    jmp .Lbegin4
.Lend8:
    mov rsp, rbp
    pop rbp
    ret
test24:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo1@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo2@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test25:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 2
    push 8
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test26:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 1
    push 2
    push 3
    push 4
    push 5
    push 6
    push 7
    push 8
    push 9
    push 10
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
fibo:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    mov [rbp-4], edi
    mov eax, [rbp-4]
    push rax
    push 0
    pop rdi
    pop rax
    cmp eax, edi
    sete al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lelse2
    push 0
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    jmp .Lend10
.Lelse2:
    mov eax, [rbp-4]
    push rax
    push 1
    pop rdi
    pop rax
    cmp eax, edi
    sete al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lelse3
    push 1
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    jmp .Lend11
.Lelse3:
    mov eax, [rbp-4]
    push rax
    push 1
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call fibo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    mov eax, [rbp-4]
    push rax
    push 2
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call fibo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
.Lend11:
.Lend10:
    mov rsp, rbp
    pop rbp
    ret
test27:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 13
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call fibo@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test28:
    push rbp
    mov rbp, rsp
    sub rsp, 12
    push 2
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 1
    pop rdi
    mov [rbp-8], edi
    push rdi
    pop rax
    push 0
    pop rdi
    mov [rbp-12], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    mov eax, [rbp-8]
    push rax
    mov eax, [rbp-12]
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call hoge@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
hoge:
    push rbp
    mov rbp, rsp
    sub rsp, 12
    mov [rbp-4], edi
    mov [rbp-8], esi
    mov [rbp-12], edx
    mov eax, [rbp-8]
    push rax
    mov eax, [rbp-4]
    push rax
    mov eax, [rbp-12]
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test29:
    push rbp
    mov rbp, rsp
    sub rsp, 12
    push 3
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    mov rax, rbp
    sub rax, 4
    push rax
    pop rdi
    mov [rbp-12], rdi
    push rdi
    pop rax
    mov rax, [rbp-12]
    push rax
    pop rax
    mov rax, [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test30:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    push 3
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 5
    pop rdi
    mov [rbp-8], edi
    push rdi
    pop rax
    mov rax, rbp
    sub rax, 8
    push rax
    push 1
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-16], rdi
    push rdi
    pop rax
    mov rax, [rbp-16]
    push rax
    pop rax
    mov rax, [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test31:
    push rbp
    mov rbp, rsp
    sub rsp, 12
    mov rax, rbp
    sub rax, 4
    push rax
    pop rdi
    mov [rbp-12], rdi
    push rdi
    pop rax
    push 3
    mov rax, [rbp-12]
    push rax
    pop rax
    pop rdi
    mov [rax], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test32:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, rbp
    sub rax, 8
    push rax
    push 1
    push 2
    push 4
    push 8
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call alloc4@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    mov rax, [rbp-8]
    push rax
    push 3
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-16], rdi
    push rdi
    pop rax
    mov rax, [rbp-16]
    push rax
    pop rax
    mov rax, [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test33:
    push rbp
    mov rbp, rsp
    sub rsp, 12
    mov rax, rbp
    sub rax, 8
    push rax
    push 0
    push 1
    push 2
    push 3
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call alloc4@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 0
    pop rdi
    mov [rbp-12], edi
    push rdi
.Lbegin5:
    mov eax, [rbp-12]
    push rax
    push 4
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend12
    push 4
    mov eax, [rbp-12]
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    mov rax, [rbp-8]
    push rax
    pop rax
    pop rdi
    mov [rax], edi
    push rdi
    pop rax
    mov rax, [rbp-8]
    push rax
    push 1
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-8], rdi
    push rdi
    mov eax, [rbp-12]
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-12], edi
    push rdi
    jmp .Lbegin5
.Lend12:
    mov rax, [rbp-8]
    push rax
    push 2
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    sub rax, rdi
    push rax
    pop rax
    mov rax, [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test34:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 0
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test35:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 4
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test36:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    push 4
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test37:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 4
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 8
    push 4
    pop rdi
    pop rax
    imul eax, edi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test38:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    push 0
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 10
    pop rdi
    mov [rbp-4], edi
    push rdi
    pop rax
    push 100
    pop rdi
    mov [rbp-8], edi
    push rdi
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test39:
    push rbp
    mov rbp, rsp
    sub rsp, 40
    push 4
    mov rax, rbp
    sub rax, 40
    push rax
    push 5
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    pop rdi
    mov [rax], edi
    push rdi
    pop rax
    mov rax, rbp
    sub rax, 40
    push rax
    push 5
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rax, [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test40:
    push rbp
    mov rbp, rsp
    sub rsp, 44
    push 0
    pop rdi
    mov [rbp-44], edi
    push rdi
.Lbegin6:
    mov eax, [rbp-44]
    push rax
    push 10
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend13
    mov eax, [rbp-44]
    push rax
    mov rax, rbp
    sub rax, 40
    push rax
    mov eax, [rbp-44]
    push rax
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    pop rdi
    mov [rax], edi
    push rdi
    mov eax, [rbp-44]
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-44], edi
    push rdi
    jmp .Lbegin6
.Lend13:
    mov rax, rbp
    sub rax, 40
    push rax
    push 5
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rax, [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test41:
    push rbp
    mov rbp, rsp
    sub rsp, 404
    push 0
    pop rdi
    mov [rbp-404], edi
    push rdi
.Lbegin7:
    mov eax, [rbp-404]
    push rax
    push 100
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend14
    mov eax, [rbp-404]
    push rax
    push 0
    pop rdi
    pop rax
    cmp eax, edi
    sete al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lelse4
    mov eax, [rbp-404]
    push rax
    mov rax, rbp
    sub rax, 400
    push rax
    mov eax, [rbp-404]
    push rax
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    pop rdi
    mov [rax], edi
    push rdi
    jmp .Lend15
.Lelse4:
    mov rax, rbp
    sub rax, 400
    push rax
    mov eax, [rbp-404]
    push rax
    push 1
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rax, [rax]
    push rax
    mov eax, [rbp-404]
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    mov rax, rbp
    sub rax, 400
    push rax
    mov eax, [rbp-404]
    push rax
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    pop rdi
    mov [rax], edi
    push rdi
.Lend15:
    mov eax, [rbp-404]
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-404], edi
    push rdi
    jmp .Lbegin7
.Lend14:
    mov rax, rbp
    sub rax, 400
    push rax
    push 10
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rax, [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
.data
a42:
    .zero 4
.text
test42:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    mov eax, a42[rip]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
.data
a43:
    .zero 4
.text
test43:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 5
    pop rdi
    mov a43[rip], edi
    push rdi
    pop rax
    mov eax, a43[rip]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
.data
a44:
    .zero 4
.text
foo44:
    push rbp
    mov rbp, rsp
    sub rsp, 12
    mov [rbp-8], rdi
    push 100
    mov rax, [rbp-8]
    push rax
    pop rax
    pop rdi
    mov [rax], edi
    push rdi
    pop rax
    push 10
    pop rdi
    mov [rbp-12], edi
    push rdi
    pop rax
    mov eax, [rbp-12]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test44:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    lea rax, a44[rip]
    push rax
    pop rdi
    mov [rbp-8], rdi
    push rdi
    pop rax
    mov rax, [rbp-8]
    push rax
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call foo44@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    mov eax, a44[rip]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
.data
a45:
    .zero 40
.text
init45:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 1
    pop rdi
    mov [rbp-4], edi
    push rdi
.Lbegin8:
    mov eax, [rbp-4]
    push rax
    push 10
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lend16
    lea rax, a45[rip]
    push rax
    mov eax, [rbp-4]
    push rax
    push 1
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rax, [rax]
    push rax
    mov eax, [rbp-4]
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    lea rax, a45[rip]
    push rax
    mov eax, [rbp-4]
    push rax
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    pop rdi
    mov [rax], edi
    push rdi
    mov eax, [rbp-4]
    push rax
    push 1
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rdi
    mov [rbp-4], edi
    push rdi
    jmp .Lbegin8
.Lend16:
    push 0
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test45:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call init45@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    lea rax, a45[rip]
    push rax
    push 9
    pop rdi
    push 4
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rax, [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test46:
    push rbp
    mov rbp, rsp
    sub rsp, 7
    push 0
    push 1
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    mov rax, rbp
    sub rax, 3
    push rax
    push 0
    pop rdi
    push 1
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    pop rdi
    mov [rax], dil
    push rdi
    pop rax
    push 2
    mov rax, rbp
    sub rax, 3
    push rax
    push 1
    pop rdi
    push 1
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    pop rdi
    mov [rax], dil
    push rdi
    pop rax
    push 0
    push 5
    pop rdi
    pop rax
    sub rax, rdi
    push rax
    mov rax, rbp
    sub rax, 3
    push rax
    push 2
    pop rdi
    push 1
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    pop rdi
    mov [rax], dil
    push rdi
    pop rax
    push 1
    pop rdi
    mov [rbp-7], edi
    push rdi
    pop rax
    mov rax, rbp
    sub rax, 3
    push rax
    push 1
    pop rdi
    push 1
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    movsx rax, BYTE PTR [rax]
    push rax
    mov eax, [rbp-7]
    push rax
    pop rdi
    pop rax
    add rax, rdi
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test47:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    lea rax, .LC1[rip]
    push rax
    pop rdi
    mov [rbp-8], rdi
    push rdi
    pop rax
    mov rax, [rbp-8]
    push rax
    push 0
    pop rdi
    push 1
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    movsx rax, BYTE PTR [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test48:
    push rbp
    mov rbp, rsp
    sub rsp, 4
    push 0
    push 1
    pop rdi
    pop rax
    cmp eax, edi
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lelse5
    push 1
    pop rdi
    mov [rbp-4], edi
    push rdi
    jmp .Lend17
.Lelse5:
    push 0
    pop rdi
    mov [rbp-4], edi
    push rdi
.Lend17:
    mov eax, [rbp-4]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test49:
    push rbp
    mov rbp, rsp
    sub rsp, 24
    lea rax, .LC2[rip]
    push rax
    pop rdi
    mov [rbp-8], rdi
    push rdi
    pop rax
    lea rax, .LC3[rip]
    push rax
    pop rdi
    mov [rbp-16], rdi
    push rdi
    pop rax
    mov rax, [rbp-8]
    push rax
    push 0
    pop rdi
    push 1
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    movsx rax, BYTE PTR [rax]
    push rax
    mov rax, [rbp-16]
    push rax
    push 0
    pop rdi
    push 1
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    movsx rax, BYTE PTR [rax]
    push rax
    pop rdi
    pop rax
    cmp al, dil
    setl al
    movzb eax, al
    push rax
    pop rax
    cmp rax, 0
    je .Lelse6
    mov rax, [rbp-8]
    push rax
    pop rdi
    mov [rbp-24], rdi
    push rdi
    jmp .Lend18
.Lelse6:
    mov rax, [rbp-16]
    push rax
    pop rdi
    mov [rbp-24], rdi
    push rdi
.Lend18:
    mov rax, [rbp-24]
    push rax
    push 2
    pop rdi
    push 1
    pop rax
    cltq
    imul rdi, rax
    pop rax
    add rax, rdi
    push rax
    pop rax
    movsx rax, BYTE PTR [rax]
    push rax
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test50:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 2
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
test51:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 0
    pop rax
    mov rsp, rbp
    pop rbp
    ret
    mov rsp, rbp
    pop rbp
    ret
main:
    push rbp
    mov rbp, rsp
    sub rsp, 0
    push 0
    push 0
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test0@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 1
    push 42
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test1@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 2
    push 21
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test2@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 3
    push 41
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test3@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 4
    push 57
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test4@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 5
    push 34
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test5@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 6
    push 2
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test6@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 7
    push 10
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test7@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 8
    push 0
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test8@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 9
    push 3
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test9@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 10
    push 51
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test10@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 11
    push 1
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test11@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 12
    push 6
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test12@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 13
    push 11
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test13@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 14
    push 8
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test14@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 15
    push 10
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test15@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 16
    push 1
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test16@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 17
    push 10
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test17@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 18
    push 0
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test18@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 19
    push 24
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test19@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 20
    push 64
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test20@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 21
    push 2
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test21@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 22
    push 55
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test22@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 23
    push 64
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test23@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 24
    push 3
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test24@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 25
    push 10
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test25@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 26
    push 55
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test26@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 27
    push 233
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test27@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 28
    push 2
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test28@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 29
    push 3
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test29@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 30
    push 3
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test30@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 31
    push 3
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test31@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 32
    push 8
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test32@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 33
    push 6
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test33@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 34
    push 0
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test34@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 35
    push 4
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test35@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 36
    push 4
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test36@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 37
    push 32
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test37@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 38
    push 10
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test38@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 39
    push 4
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test39@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 40
    push 5
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test40@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 41
    push 55
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test41@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 42
    push 0
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test42@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 43
    push 5
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test43@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 44
    push 100
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test44@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 45
    push 45
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test45@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 46
    push 3
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test46@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 47
    push 104
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test47@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 48
    push 1
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test48@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 49
    push 99
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test49@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 50
    push 2
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test50@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    push 51
    push 0
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call test51@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    pop rdx
    pop rsi
    pop rdi
    push 0
    pop rax
    mov r10, rsp
    and rsp, -16
    push r10
    push r11
    call try@plt
    pop r11
    pop r10
    mov rsp, r10
    push rax
    mov rsp, rbp
    pop rbp
    ret
