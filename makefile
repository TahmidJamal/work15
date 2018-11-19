all: work15.o
	gcc -o go work15.o

work15.o: work15.c
	gcc -c work15.c

run:
	./go

clean:
	rm *.o
	rm ./go

