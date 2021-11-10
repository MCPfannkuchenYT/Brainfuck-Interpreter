all: brainc.c
	clang brainc.c -o brainc -O3
debug:
	make all
	gdb brainc
run:
	make all
	./brainc > out.c
	clang out.c -o out -O3
	time ./out
clean:
	rm -rf brainc out.c out
