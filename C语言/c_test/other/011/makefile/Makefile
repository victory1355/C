app:add_func.o sub_func.o main.o
	gcc add_func.o sub_func.o main.o -o app

add_func.o:add_func.c add_func.h
	gcc -c add_func.c add_func.h

sub_func.o:sub_func.c sub_func.h
	gcc -c sub_func.c sub_func.h

main.o:main.c
	gcc -c main.c 

.PHONY:clean
clean:
	rm -rf add_func.o sub_func.o main.o 
