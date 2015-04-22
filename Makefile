.PHONY: clean default

default: producers-n-consumers readers-n-writers

clean:
	rm -f producers-n-consumers
	rm -f readers-n-writers

producers-n-consumers: mymutex.* producers-n-consumers.*
	gcc -o producers-n-consumers -pthread -g producers-n-consumers.c mymutex.c

readers-n-writers: mymutex.* readers-n-writers.*
	gcc -o readers-n-writers -pthread -g readers-n-writers.c mymutex.c
