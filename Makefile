.PHONY: test clean

BUILD=build
RESOURCES=resources
OPT=-Wall -Werror -fPIC -std=c99 -O2

all:
	mkdir -p $(RESOURCES)
	$(CC) $(OPT) -shared -I murmurhash.c \
	murmurhash.c/murmurhash.c \
	libcache.c \
	-o $(RESOURCES)/libcache.so

test: $(BUILD)/cache-node-test $(BUILD)/cache-bucket-test $(BUILD)/cache-hash-test
	./$(BUILD)/cache-node-test
	./$(BUILD)/cache-bucket-test
	./$(BUILD)/cache-hash-test

$(BUILD)/cache-node-test:
	@mkdir -p $(BUILD)
	$(CC) $(OPT) cache-node-test.c -o $(BUILD)/cache-node-test

$(BUILD)/cache-bucket-test:
	@mkdir -p $(BUILD)
	$(CC) $(OPT) cache-bucket-test.c -o $(BUILD)/cache-bucket-test

$(BUILD)/cache-hash-test:
	@mkdir -p $(BUILD)
	$(CC) $(OPT) -I murmurhash.c murmurhash.c/murmurhash.c cache-hash-test.c -o $(BUILD)/cache-hash-test

clean:
	-rm -rf $(BUILD) $(RESOURCES)
