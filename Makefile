.PHONY: test clean

BUILD=build
RESOURCES=resources
OPT=-Wall -Werror -fPIC -std=c99 -O2

all: $(RESOURCES) $(BUILD) $(RESOURCES)/libhash.so

$(RESOURCES)/libhash.so:
	$(CC) $(OPT) -shared -I murmurhash.c \
	murmurhash.c/murmurhash.c \
	libhash.c \
	-o $(RESOURCES)/libhash.so

$(BUILD):
	mkdir -p $(BUILD)

$(RESOURCES):
	mkdir -p $(RESOURCES)

test: all $(BUILD)/hash-node-test $(BUILD)/hash-bucket-test $(BUILD)/hash-test
	./$(BUILD)/hash-node-test
	./$(BUILD)/hash-bucket-test
	./$(BUILD)/hash-test

test-valgrind: all $(BUILD)/hash-node-test $(BUILD)/hash-bucket-test $(BUILD)/hash-test
	valgrind ./$(BUILD)/hash-node-test
	valgrind ./$(BUILD)/hash-bucket-test
	valgrind ./$(BUILD)/hash-test

$(BUILD)/hash-node-test:
	$(CC) $(OPT) hash-node-test.c -o $(BUILD)/hash-node-test

$(BUILD)/hash-bucket-test:
	$(CC) $(OPT) hash-bucket-test.c -o $(BUILD)/hash-bucket-test

$(BUILD)/hash-test:
	$(CC) $(OPT) -I murmurhash.c murmurhash.c/murmurhash.c hash-test.c -o $(BUILD)/hash-test

clean:
	-rm -rf $(BUILD) $(RESOURCES)
