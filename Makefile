NAME = minishell
CC = gcc
CFLAGS = -g -I./include

SRC_FILES = $(wildcard src/builtins/*.c) $(wildcard src/parser/*.c) \
             $(wildcard src/input/*.c) $(wildcard src/execute/*.c) \
             $(wildcard src/*.c) $(wildcard src/tokenizer/*.c)

OBJ_FILES = $(patsubst src/%.c, obj/%.o, $(SRC_FILES))

.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make -C libft
	$(CC) -g $^ -L./libft -lft -L/opt/homebrew/opt/readline/lib -lreadline -o bin/$@


run: $(NAME)
	./bin/$(NAME)

clean:
	make clean -C libft
	rm -rf obj/*.o obj/*/*.o bin/*

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@