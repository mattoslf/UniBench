# Example
# target: dependencies
	# command 1
	# command 2
          # .
          # .
          # .
	# command n

# link objects(binaries) together
a.out:	main.o
	clang	main.o \
			-omptargets=spir64-unknown-unknown -fno-verbose-asm -lm -fopenmp -o srad

# compile main function file into object (binary)
main.o: 	main.c \
				define.c \
				graphics.c
	clang	main.c \
			-omptargets=spir64-unknown-unknown -fno-verbose-asm -c -O3 -fopenmp

# delete all object files
clean:
	rm *.o srad _kernel*
