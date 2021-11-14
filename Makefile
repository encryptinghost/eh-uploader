CC ?= gcc
CFLAGS := -Ideps
CLIBS := curl ssl
TARGET := eh-uploader
PREFIX ?= /usr/local

SRC := $(shell find src/ -name '*.c')
OBJ := $(patsubst %.c,%.o,$(subst src/,build/,$(SRC)))

# gcc -o eh-uploader -Ideps -lcurl -lssl

.PHONY: clean

all: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(patsubst %,-l%,$(CLIBS))

$(OBJ): build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)
	@echo ""

install: all
	install -d $(PREFIX)/bin
	install -m 755 eh-uploader $(PREFIX)/bin

clean:
	rm -r build/