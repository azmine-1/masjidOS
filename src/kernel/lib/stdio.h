#ifndef STDIO_H
#define STDIO_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_writehex(uint32_t value);
void terminal_writedec(uint32_t value);

#endif