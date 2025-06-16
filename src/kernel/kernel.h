#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdint.h>

/* Main kernel function */
void kernel_main(void);

/* GDT functions */
void gdt_init(void);

/* IDT functions */
void idt_init(void);

/* Memory management functions */
void memory_init(void);

/* Driver functions */
void keyboard_init(void);
void timer_init(void);

/* Terminal functions */
void terminal_initialize(void);
void terminal_writestring(const char* data);
void terminal_putchar(char c);

/* Port I/O functions */
static inline void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

static inline void io_wait(void) {
    asm volatile("outb %%al, $0x80" : : "a"(0));
}

#endif