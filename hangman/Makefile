CC = clang
CFLAGS = -g3 -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -fsanitize=undefined,address -fsanitize-trap
LFLAGS = -fsanitize=undefined,address
EXEC = hangman
TEST = unit_test
HEADERS = hangman_helpers.h

all: $(EXEC)

$(EXEC): $(EXEC).o hangman_helpers.o
	$(CC) $^ $(LFLAGS) -o $@

$(TEST): $(TEST).o hangman_helpers.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

test: $(TEST)
	./$(TEST)

clean:
	rm -rf $(EXEC) $(TEST) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format test