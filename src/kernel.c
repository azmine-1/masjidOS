/* kernel.c - Simple kernel entry point */

/* Define constants for VGA text mode */
#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_COLOR_BLACK 0
#define VGA_COLOR_LIGHT_GREY 7
#define VGA_COLOR_WHITE 15
#define VGA_COLOR_RED 4


unsigned char vga_color(unsigned char fg, unsigned char bg) {
    return fg | (bg << 4);
}


unsigned short vga_entry(unsigned char ch, unsigned char color) {
    return (unsigned short) ch | ((unsigned short) color << 8);
}


void clear_screen(void) {
    unsigned short* vga_buffer = (unsigned short*) VGA_MEMORY;
    unsigned char color = vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = vga_entry(' ', color);
    }
}


void print_string(const char* str, int row, int col, unsigned char color) {
    unsigned short* vga_buffer = (unsigned short*) VGA_MEMORY;
    int position = row * VGA_WIDTH + col;
    
    for (int i = 0; str[i] != '\0'; i++) {
        vga_buffer[position++] = vga_entry(str[i], color);
    }
}


void kernel_main(void) {
    clear_screen();
    
    
    print_string("Welcome to masjidOS!", 0, 25, vga_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
    print_string("This is a minimal OS built with a simple toolchain", 2, 10, vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    print_string("No complex cross-compiler setup required!", 3, 10, vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    
    /* Stop execution */
    while(1) {
        /* Infinite loop to prevent the CPU from executing random code */
        __asm__("hlt");
    }
}