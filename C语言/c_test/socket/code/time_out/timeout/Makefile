SRC = ${wildcard *.c}
OBJ = ${patsubst %.c, %, $(SRC)}

CPPFLAGS = -I .

LDFLAGS += -L .
LDFLAGS += -lvnet
LDFLAGS += -lpthread
LDFLAGS += -Wl,-rpath=.

CC = $(CROSS)gcc

all:$(OBJ)

$(OBJ):%:%.c
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJ) .*.sw?

.PHONY:all clean
