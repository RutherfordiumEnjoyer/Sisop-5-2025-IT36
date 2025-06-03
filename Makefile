IDIR = include
BDIR = bin
SDIR = src
NASK = nasm
BCC = bcc
LD = ld86

IMG  = $(BDIR)/floppy.img
OBJS = $(BDIR)/kernel.o $(BDIR)/kernel-asm.o $(BDIR)/std_lib.o $(BDIR)/shell.o

CFLAGS = -ansi -I$(IDIR)

.PHONY: all clean build run

all: build

build: $(IMG)

run: build
	bochs -f bochsrc.txt

clean:
	rm -f $(BDIR)/*

$(IMG): $(BDIR)/bootloader.bin $(BDIR)/kernel.bin
	@echo "==> Creating new floppy image..."
	dd if=/dev/zero of=$(IMG) bs=512 count=2880 >/dev/null 2>&1
	@echo "==> Writing bootloader to image..."
	dd if=$(BDIR)/bootloader.bin of=$(IMG) bs=512 count=1 conv=notrunc >/dev/null 2>&1
	@echo "==> Writing kernel to image..."
	dd if=$(BDIR)/kernel.bin of=$(IMG) bs=512 seek=1 conv=notrunc >/dev/null 2>&1
	@echo "==> Build finished: $(IMG)"


$(BDIR)/kernel.bin: $(OBJS)
	@echo "==> Linking object files to create kernel.bin..."
	$(LD) -o $@ -d $^

$(BDIR)/bootloader.bin: $(SDIR)/bootloader.asm
	@echo "==> Assembling bootloader..."
	$(NASK) -f bin $< -o $@

$(BDIR)/kernel-asm.o: $(SDIR)/kernel.asm
	@echo "==> Assembling kernel ASM ($<)..."
	$(NASK) -f as86 $< -o $@

$(BDIR)/%.o: $(SDIR)/%.c
	@echo "==> Compiling C source ($<)..."
	$(BCC) $(CFLAGS) -c $< -o $@
