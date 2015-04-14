default: all

all: spike

clean:
	ls | grep -E -v '(.*\.c|Makefile)' | xargs rm

spike: spike.c
	gcc -o spike -pthread spike.c
