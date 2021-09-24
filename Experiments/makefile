# Usage:
# make	# compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

all: zero_runtime.e

zero_runtime.e: zero_runtime.o zero_runtime_calls.o zero_runtime_main.o
	@echo "Linking..."
	ld $^ -o $@ -static -arch x86_64

zero_runtime_calls.o: zero_runtime_calls.asm
	@echo "Creating zero_runtime_calls object..."
	nasm -f macho64 $<

zero_runtime_main.o: zero_runtime_main.asm
	@echo "Creating zero_runtime_main object..."
	nasm -f macho64 $<

zero_runtime.o: zero_runtime.c
	@echo "Creating zero_runtime object..."
	gcc -Wall -c $<

clean:
	@echo "Cleaning up..."
	rm -rvf *.o *.e


empty:
	nasm -f macho64 empty.asm
	ld empty.o -o empty.e -static -arch x86_64 
	./empty.e
	@echo $?