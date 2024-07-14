CC = gcc
CFLAGS = -g3 -O0 -std=c2x -I./include -I./config $(shell pkg-config sdl2 sdl2_ttf --cflags)
LDFLAGS = -g3 -O0 $(shell pkg-config sdl2 sdl2_ttf --libs)

SRC_DIR = ./src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) 
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))

COMPILED_FILES = 0
ALL_FILES = $(words $(SRC_FILES))

TARGET = mockterm

all: $(TARGET) clean

$(TARGET): $(OBJ_FILES)
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo "+ linking all the objects, created mockterm"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "+ [$(COMPILED_FILES)/$(ALL_FILES)] compiling $<..."
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))

clean:
	rm -f $(SRC_DIR)/*.o $(SRC_DIR)/**/*.o $(SRC_DIR)/**/**/*.o $(SRC_DIR)/**/**/**/*.o