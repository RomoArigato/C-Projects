CC = clang
CFLAGS = -g3 -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -fsanitize=undefined,address -fsanitize-trap
LFLAGS = -fsanitize=undefined,address
EXEC = calc
TEST = unit_test
HEADERS = stack.h operators.h mathlib.h
OBJS = stack.o operators.o mathlib.o

all: $(EXEC)

$(EXEC): $(EXEC).o $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(TEST): $(TEST).o $(OBJS)
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