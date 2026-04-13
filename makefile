SRCS = $(wildcard src/*.c) $(wildcard src/compressors/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)

CC = cc

TARGET = myccompressor

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

obj/%.o: src/%.c
	mkdir -p obj/compressors
	$(CC) -c -o $@ $^

clean:
	rm -rf $(TARGET) obj
