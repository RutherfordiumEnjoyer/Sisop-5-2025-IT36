bits 16

KERNEL_SEGMENT equ 0x1000
KERNEL_SECTORS equ 15
KERNEL_START equ 1

bootloader:
    mov ax, KERNEL_SEGMENT
    mov es, ax
    mov bx, 0x0000

    mov ah, 0x02
    mov al, KERNEL_SECTORS

    mov ch, 0x00
    mov cl, KERNEL_START + 1
    mov dh, 0x00
    mov dl, 0x00

    int 0x13

    jc kernel_load_failed

    mov ax, KERNEL_SEGMENT
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov ax, 0xFFF0
    mov sp, ax
    mov bp, ax

    jmp KERNEL_SEGMENT:0x0000

kernel_load_failed:
    mov si, err_msg
print_loop:
    lodsb
    cmp al, 0
    je halt
    mov ah, 0x0E
    int 0x10
    jmp print_loop
halt:
    jmp $

err_msg: db 'X - Kernel Load Failed!', 0

times 510-($-$$) db 0
dw 0xAA55
