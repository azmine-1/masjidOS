# Compiler and tools
CC = i686-elf-gcc
AS = i686-elf-as
LD = i686-elf-gcc

# Directories
SRCDIR = src
BUILDDIR = build
ISODIR = iso
INCLUDEDIR = include

# Compiler flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDEDIR)
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

# Find all source files
C_SOURCES = $(shell find $(SRCDIR) -name "*.c")
ASM_SOURCES = $(shell find $(SRCDIR) -name "*.s")

# Object files
C_OBJECTS = $(C_SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
ASM_OBJECTS = $(ASM_SOURCES:$(SRCDIR)/%.s=$(BUILDDIR)/%.o)
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# Kernel binary
KERNEL = myos.bin

# Default target
all: $(KERNEL)

# Create build directories
$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/boot
	mkdir -p $(BUILDDIR)/kernel/gdt
	mkdir -p $(BUILDDIR)/kernel/idt
	mkdir -p $(BUILDDIR)/kernel/memory
	mkdir -p $(BUILDDIR)/kernel/drivers
	mkdir -p $(BUILDDIR)/kernel/lib

# Compile C sources
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile assembly sources
$(BUILDDIR)/%.o: $(SRCDIR)/%.s | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(AS) $< -o $@

# Link kernel
$(KERNEL): $(OBJECTS)
	$(LD) -T linker.ld -o $@ $(LDFLAGS) $(OBJECTS)

# Verify multiboot
verify: $(KERNEL)
	grub-file --is-x86-multiboot $(KERNEL) && echo "Multiboot confirmed" || echo "Not multiboot compatible"

# Create ISO
iso: $(KERNEL) verify
	cp $(KERNEL) $(ISODIR)/boot/$(KERNEL)
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso $(ISODIR)

# Run in QEMU
run: iso
	qemu-system-i386 -cdrom myos.iso

# Debug with QEMU and GDB
debug: iso
	qemu-system-i386 -cdrom myos.iso -s -S &
	gdb $(KERNEL) -ex "target remote localhost:1234"

# Clean build files
clean:
	rm -rf $(BUILDDIR)
	rm -f $(KERNEL)
	rm -f myos.iso

# Create necessary directories
setup:
	mkdir -p $(ISODIR)/boot/grub

.PHONY: all clean iso run debug verify setup
