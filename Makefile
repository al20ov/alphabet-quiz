CC			=	cc
CFLAGS		=	-Iinclude
SRCS		=	src/main.c \
				src/gauge.c
OBJS		=	$(SRCS:.c=.o)
TARGET		=	alphabet-quiz

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: clean
