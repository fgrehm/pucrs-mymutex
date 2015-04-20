
all: spike app1 app2

clean:
	rm spike
	rm app1
	rm app2

spike: 
	gcc -o spike -pthread -g spike.c mymutex.c

app1:
	gcc -o app1 -pthread -g app1.c mymutex.c

app2:
	gcc -o app2 -pthread -g app2.c mymutex.c

