.PHONY: test clean

BUILD=build
RESOURCES=resources
OPT=-Wall -Werror -fPIC -std=c99 -O2

all: $(RESOURCES) $(BUILD)
	$(CC) $(OPT) -shared -I murmurhash.c \
	murmurhash.c/murmurhash.c \
	libcache.c \
	-o $(RESOURCES)/libcache.so

$(BUILD):
	mkdir -p $(BUILD)

$(RESOURCES):
	mkdir -p $(RESOURCES)

test: $(BUILD)/cache-node-test $(BUILD)/cache-bucket-test $(BUILD)/cache-hash-test
	./$(BUILD)/cache-node-test
	./$(BUILD)/cache-bucket-test
	./$(BUILD)/cache-hash-test

$(BUILD)/cache-node-test:
	$(CC) $(OPT) cache-node-test.c -o $(BUILD)/cache-node-test

$(BUILD)/cache-bucket-test:
	$(CC) $(OPT) cache-bucket-test.c -o $(BUILD)/cache-bucket-test

$(BUILD)/cache-hash-test:
	$(CC) $(OPT) -I murmurhash.c murmurhash.c/murmurhash.c cache-hash-test.c -o $(BUILD)/cache-hash-test

clean:
	-rm -rf $(BUILD) $(RESOURCES)
