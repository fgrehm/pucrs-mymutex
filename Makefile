.PHONY: clean default

default: spike producers-n-consumers readers-n-writers

clean:
	rm -f spike
	rm -f producers-n-consumers
	rm -f readers-n-writers

spike: mymutex.* spike.*
	gcc -o spike -pthread -g spike.c mymutex.c

producers-n-consumers: mymutex.* producers-n-consumers.*
	gcc -o producers-n-consumers -pthread -g producers-n-consumers.c mymutex.c

readers-n-writers: mymutex.* readers-n-writers.*
	gcc -o readers-n-writers -pthread -g readers-n-writers.c mymutex.c
