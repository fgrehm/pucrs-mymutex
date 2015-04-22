.PHONY: clean default

default: spike app1 app2 readers-n-writers

clean:
	rm {spike,app1,app2,readers-n-writers}

spike: mymutex.* spike.*
	gcc -o spike -pthread -g spike.c mymutex.c

app1: mymutex.* app1.*
	gcc -o app1 -pthread -g app1.c mymutex.c

app2: mymutex.* app2.*
	gcc -o app2 -pthread -g app2.c mymutex.c

readers-n-writers: mymutex.* readers-n-writers.*
	gcc -o readers-n-writers -pthread -g readers-n-writers.c mymutex.c
