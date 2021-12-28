CC=g++
OUT=a.out 
CFLAGS= -g -c -Wall -std=c++17

$(OUT) : lexer.o test.o error_handler.o
	$(CC) -o $@ $^

lexer.o : lexer.cpp
	$(CC) $(CFLAGS) $^

test.o : test.cpp
	$(CC) $(CFLAGS) $^

error_handler.o: error_handler.cpp	
	$(CC) $(CFLAGS) $^

.PHONY: clean

clean:
	rm -f $(OUT) *.o