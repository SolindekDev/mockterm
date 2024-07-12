CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -I./include -I./config
LDFLAGS = -g -lSDL2 -lSDL2_ttf

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