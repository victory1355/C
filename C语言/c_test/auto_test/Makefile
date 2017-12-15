CC = gcc


TARGET = main


SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))


$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lcurses -lpthread

$(OBJS):%.o:%.c
	$(CC) -c $^ -o $@ -lcurses -lpthread


clean:
	rm *.o 

