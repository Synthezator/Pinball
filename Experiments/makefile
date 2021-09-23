# Usage:
# make	# compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

all: zero_runtime.e

zero_runtime.e: zero_runtime.o zero_runtime_calls.o zero_runtime_main.o
	@echo "Linking..."
	ld $^ -o $@ -no_uuid -no_eh_labels -no_pie -demangle -dynamic -arch x86_64 -platform_version macos 11.0.0 11.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -L/usr/local/lib -lSystem

zero_runtime_calls.o: zero_runtime_calls.asm
	@echo "Creating zero_runtime_calls object..."
	nasm -g -f macho64 $<

zero_runtime_main.o: zero_runtime_main.asm
	@echo "Creating zero_runtime_main object..."
	nasm -g -f macho64 $<

zero_runtime.o: zero_runtime.c
	@echo "Creating zero_runtime object..."
	gcc -Wall -g -c $<

clean:
	@echo "Cleaning up..."
	rm -rvf *.o *.e