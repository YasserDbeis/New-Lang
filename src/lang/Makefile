CC=g++
OUT=a.out 
CFLAGS= -g -c -Wall -std=c++11

$(OUT) : lexer.o test.o
	$(CC) -o $@ $^

lexer.o : lexer.cpp
	$(CC) $(CFLAGS) $^

test.o : test.cpp
	$(CC) $(CFLAGS) $^

.PHONY: clean

clean:
	rm -f $(OUT) *.o