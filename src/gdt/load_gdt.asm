global loadGdt, reloadSegment, reloadCS

loadGdt:

    mov rax, [rdi]
    lgdt [rax]
    jmp reloadSegment

reloadSegment:

    push 0x8
    lea rax, [reloadCS]
    push rax
    retf

reloadCS:

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
