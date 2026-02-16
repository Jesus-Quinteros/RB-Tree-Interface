all: main.o rbtree.o display.o
	gcc rbtree.o display.o main.o -o main -lfreeglut -lopengl32 -lglu32 -lm
main.o: main.c display.h rbtree.h
	gcc -c main.c
rbtree.o: rbtree.c rbtree.h
	gcc -c rbtree.c
display.o: display.c display.h
	gcc -c display.c
clean:
	rm -f main *.o
