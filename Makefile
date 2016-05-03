.PHONY: test clean

BUILD=build
OPT=-Wall -Werror -fPIC -std=c99 -O2

test: $(BUILD)/cache-node-test
	./$(BUILD)/cache-node-test

$(BUILD)/cache-node-test:
	@mkdir -p $(BUILD)
	gcc $(OPT) cache-node-test.c -o $(BUILD)/cache-node-test

clean:
	-rm -rf $(BUILD)
