all: main.o rbtree.o display.o
	gcc rbtree.o display.o main.o -o main -lGL -lGLU -lglut -lm
main.o: main.c
	gcc -c main.c
rbtree.o: rbtree.c
	gcc -c rbtree.c
display.o: display.c
	gcc -c display.c
clean:
	rm -f
