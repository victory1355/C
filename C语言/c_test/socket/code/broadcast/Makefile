SRC = ${wildcard *.c}
BIN = ${patsubst %.c, %, $(SRC)}

CFLAGS = -g -Wall

all:$(BIN)

$(BIN):%:%.c
	$(CC) $(CFLAGS) -o $@ $^ -I../lib -L../lib -lvnet -Wl,-rpath=../lib

clean:
	$(RM) $(BIN) .*.sw?

.PHONY:all clean
