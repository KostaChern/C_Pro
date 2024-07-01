all: prog.exe

prog.exe: main.o pumpkins.o field.o drone.o
	gcc -o prog main.o pumpkins.o field.o drone.o

main.o: main.c pumpkins.h
	gcc -c -o main.o main.c

pumpkins.o: pumpkins.c 
	gcc -c -o pumpkins.o pumpkins.c

field.o: field.c 
	gcc -c -o field.o field.c

drone.o: drone.c 
	gcc -c -o drone.o drone.c

clean:
	del *.o
	del prog.exe