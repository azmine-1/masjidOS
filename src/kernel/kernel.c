#include "kernel/kernel.h"
#include "lib/stdio.h"
#include "lib/string.h"

void kernel_main(void) {
    /* Initialize terminal */
    terminal_initialize();
    
    /* Print welcome message */
    terminal_writestring("Welcome to MyOS!\n");
    terminal_writestring("Kernel initialized successfully.\n\n");
    
    /* Initialize kernel subsystems */
    terminal_writestring("Initializing GDT...\n");
    gdt_init();
    
    terminal_writestring("Initializing IDT...\n");
    idt_init();
    
    terminal_writestring("Initializing memory management...\n");
    memory_init();
    
    terminal_writestring("Initializing keyboard driver...\n");
    keyboard_init();
    
    terminal_writestring("Initializing timer...\n");
    timer_init();
    
    terminal_writestring("\nAll systems initialized successfully!\n");
    terminal_writestring("MyOS is ready.\n");
    
    /* Enable interrupts */
    asm volatile("sti");
    
    /* Kernel main loop */
    while (1) {
        /* Halt until next interrupt */
        asm volatile("hlt");
    }
}