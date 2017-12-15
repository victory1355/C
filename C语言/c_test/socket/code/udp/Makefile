SRC = ${wildcard *.c}
BIN = ${patsubst %.c, %, $(SRC)}

all:$(BIN)

CFLAGS += -I ../lib
CFLAGS += -L ../lib
CFLAGS += -lvnet
CFLAGS += -Wl,-rpath=../lib

$(BIN):%:%.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(BIN) .*.sw?
