alphabet-quiz: main.o
	$(CC) -o alphabet-quiz main.o

clean:
	rm -f alphabet-quiz *.o

.PHONY: clean
