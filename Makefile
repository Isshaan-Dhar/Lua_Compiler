CC = gcc
CFLAGS = -I./include -Os -Wall -s
SRC = src/lexer.c src/parser.c src/main.c
OBJ = $(SRC:.c=.o)
TARGET = luacomp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

benchmark: $(TARGET)
	@echo "--- BINARY SIZE ---"
	@ls -lh $(TARGET) | awk '{print "Size:", $$5}'
	@echo "--- RUNNING PERFORMANCE TEST ---"
	@./$(TARGET) tests/test_bench.lua

clean:
	rm -f src/*.o $(TARGET)