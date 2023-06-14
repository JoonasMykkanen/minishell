# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 11:44:25 by joonasmykka       #+#    #+#              #
#    Updated: 2023/06/14 12:07:03 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = ./src/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
CC = cc
INCLUDE = -L$(LIBFT) -lft -L/opt/homebrew/opt/readline/lib -lreadline
CFLAGS = -g -Wall -Werror -Wextra -I./include
LDFLAGS = -L$(LIBFT_DIR) -lft -L/opt/homebrew/opt/readline/lib -lreadline

SRC_FILES = $(wildcard src/builtins/*.c) $(wildcard src/parser/*.c) \
             $(wildcard src/input/*.c) $(wildcard src/execute/*.c) \
             $(wildcard src/*.c) $(wildcard src/tokenizer/*.c)

OBJ_FILES = $(patsubst src/%.c, obj/%.o, $(SRC_FILES))

.PHONY: all clean fclean re leaks

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o bin/$@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

run: $(NAME)
	./bin/$(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf obj/*.o obj/*/*.o 

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf bin/*

re: fclean
	make re -C $(LIBFT_DIR)
	make all

leaks: $(NAME)
	leaks --atExit -- ./bin/minishell