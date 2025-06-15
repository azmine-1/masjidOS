KERNEL = kernel/kernel.bin
ISO = myos.iso

all: $(ISO)

kernel/kernel.o: kernel/kernel.c
	i686-elf-gcc -ffreestanding -c $< -o $@

$(KERNEL): kernel/kernel.o
	i686-elf-gcc -ffreestanding -nostdlib -T linker.ld $< -o $@

iso/boot/grub/grub.cfg:
	mkdir -p iso/boot/grub
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'menuentry "myos" { multiboot /boot/kernel.bin }' >> iso/boot/grub/grub.cfg

$(ISO): $(KERNEL) iso/boot/grub/grub.cfg
	cp $(KERNEL) iso/boot/kernel.bin
	grub-mkrescue -o $(ISO) iso

run: $(ISO)
	qemu-system-x86_64 -cdrom $(ISO)

clean:
	rm -rf kernel/*.o kernel/*.bin iso myos.iso