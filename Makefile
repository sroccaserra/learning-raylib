.PHONY: run
run: a.out
	./a.out

a.out: main.c
	gcc main.c -lraylib -lm
