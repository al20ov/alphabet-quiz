CC = cc
CFLAGS = -Iinclude
SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

alphabet-quiz: $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f alphabet-quiz $(OBJS)

.PHONY: clean
