; kernel_entry.asm
; This small assembly stub ensures the kernel_main C function is called

[bits 32]           ; We're in 32-bit protected mode
[extern kernel_main] ; Declare that we will be referencing the external symbol 'kernel_main'

call kernel_main    ; Call our kernel's main function
jmp $               ; Infinite loop if kernel_main returns