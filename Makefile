all: adduser

adduser: adduser.o client.o
	gcc adduser.o client.o
adduser.o: adduser.c
	gcc -c adduser.c
client.o: client.c
	gcc -c client.c
