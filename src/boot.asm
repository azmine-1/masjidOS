; boot.asm - A simple bootloader
[bits 16]                   ; We're working in 16-bit mode
[org 0x7C00]                ; BIOS loads us at this memory address

start:
    cli                     ; Disable interrupts
    xor ax, ax              ; Zero AX register
    mov ds, ax              ; Set Data Segment to 0
    mov es, ax              ; Set Extra Segment to 0
    mov ss, ax              ; Set Stack Segment to 0
    mov sp, 0x7C00          ; Set Stack Pointer to where we are loaded
    sti                     ; Enable interrupts
    
    ; Print welcome message
    mov si, welcome_msg
    call print_string
    
    ; Load kernel from disk
    mov ah, 0x02            ; BIOS read sector function
    mov al, 1               ; Read one sector
    mov ch, 0               ; Cylinder 0
    mov cl, 2               ; Sector 2 (sectors start from 1, boot sector is 1)
    mov dh, 0               ; Head 0
    mov bx, 0x1000          ; Load to memory address 0x1000
    int 0x13                ; Call BIOS disk function
    jc disk_error           ; Jump if carry flag set (error)
    
    ; Jump to kernel
    jmp 0:0x1000            ; Jump to kernel
    
    ; Halt system if we get here
    cli
    hlt

; Print a null-terminated string
print_string:
    pusha                   ; Save all registers
    mov ah, 0x0E            ; BIOS teletype function

print_char:
    lodsb                   ; Load next character from SI into AL
    or al, al               ; Check if AL is 0 (null terminator)
    jz print_done           ; If AL is 0, we're done
    int 0x10                ; Otherwise print the character
    jmp print_char          ; And continue with next character

print_done:
    popa                    ; Restore all registers
    ret

disk_error:
    mov si, disk_error_msg
    call print_string
    jmp $                   ; Infinite loop

; Data section
welcome_msg db 'Simple OS booting...', 13, 10, 0
disk_error_msg db 'Disk read error!', 13, 10, 0

; Boot sector padding and signature
times 510-($-$$) db 0       ; Pad with zeros to make 512 bytes
dw 0xAA55                   ; Boot signature at the end of the sector