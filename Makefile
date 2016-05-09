.PHONY: test test-valgrind clean

BUILD=build
RESOURCES=resources
OPT=-Wall -Werror -fPIC -std=c99 -O2

all: $(RESOURCES) $(BUILD) $(RESOURCES)/libhash.so

$(RESOURCES):
	mkdir -p $(RESOURCES)

$(BUILD):
	mkdir -p $(BUILD)

$(RESOURCES)/libhash.so: $(BUILD)/hash-node.o $(BUILD)/hash-bucket.o $(BUILD)/hash.o
	$(CC) $(OPT) -shared -I murmurhash.c murmurhash.c/murmurhash.c \
		$(BUILD)/hash-node.o $(BUILD)/hash-bucket.o $(BUILD)/hash.o \
		-o $(RESOURCES)/libhash.so

$(BUILD)/hash-node.o:
	$(CC) $(OPT) -c hash-node.c \
		-o $(BUILD)/hash-node.o

$(BUILD)/hash-bucket.o:
	$(CC) $(OPT) -c hash-bucket.c \
		-o $(BUILD)/hash-bucket.o

$(BUILD)/hash.o:
	$(CC) $(OPT) -c -I murmurhash.c hash.c \
		-o $(BUILD)/hash.o

test: all $(BUILD)/hash-node-test $(BUILD)/hash-bucket-test $(BUILD)/hash-test
	./$(BUILD)/hash-node-test
	./$(BUILD)/hash-bucket-test
	./$(BUILD)/hash-test

test-valgrind: all $(BUILD)/hash-node-test $(BUILD)/hash-bucket-test $(BUILD)/hash-test
	valgrind ./$(BUILD)/hash-node-test
	valgrind ./$(BUILD)/hash-bucket-test
	valgrind ./$(BUILD)/hash-test

$(BUILD)/hash-node-test: $(BUILD)/hash-node.o
	$(CC) $(OPT) \
		$(BUILD)/hash-node.o \
		hash-node-test.c -o $(BUILD)/hash-node-test

$(BUILD)/hash-bucket-test: $(BUILD)/hash-bucket.o
	$(CC) $(OPT) \
		$(BUILD)/hash-node.o $(BUILD)/hash-bucket.o \
		hash-bucket-test.c -o $(BUILD)/hash-bucket-test

$(BUILD)/hash-test: $(BUILD)/hash.o
	$(CC) $(OPT) -I murmurhash.c murmurhash.c/murmurhash.c \
		$(BUILD)/hash-node.o $(BUILD)/hash-bucket.o $(BUILD)/hash.o \
		hash-test.c -o $(BUILD)/hash-test

clean:
	-rm -rf $(BUILD) $(RESOURCES)
