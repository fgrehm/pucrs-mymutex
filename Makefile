
all: spike app1 app2

clean:
	rm spike
	rm app1
	rm app2

spike: 
	gcc -o spike -pthread spike.c mymutex.c

app1:
	gcc -o app1 -pthread app1.c mymutex.c

app2:
	gcc -o app2 -pthread app2.c mymutex.c

