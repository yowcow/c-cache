.PHONY: test clean

BUILD=build
OPT=-Wall -Werror -fPIC -std=c99 -O2

test: $(BUILD)/cache-node-test $(BUILD)/cache-bucket-test $(BUILD)/cache-hash-test
	./$(BUILD)/cache-node-test
	./$(BUILD)/cache-bucket-test
	./$(BUILD)/cache-hash-test

$(BUILD)/cache-node-test:
	@mkdir -p $(BUILD)
	gcc $(OPT) cache-node-test.c -o $(BUILD)/cache-node-test

$(BUILD)/cache-bucket-test:
	@mkdir -p $(BUILD)
	gcc $(OPT) cache-bucket-test.c -o $(BUILD)/cache-bucket-test

$(BUILD)/cache-hash-test:
	@mkdir -p $(BUILD)
	gcc $(OPT) -I murmurhash.c murmurhash.c/murmurhash.c cache-hash-test.c -o $(BUILD)/cache-hash-test

clean:
	-rm -rf $(BUILD)
