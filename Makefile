# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 11:44:25 by joonasmykka       #+#    #+#              #
#    Updated: 2023/06/30 12:58:37 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
BIN_DIR = bin
TARGET = $(BIN_DIR)/$(NAME)
BONUS_TARGET = $(BIN_DIR)/BONUS_$(NAME)

LIBFT_DIR = ./src/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = -g -Wall -Werror -Wextra -I./include
# LDFLAGS = -L$(LIBFT_DIR) -lft -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
LDFLAGS = -L$(LIBFT_DIR) -lft -L/opt/homebrew/opt/readline/lib -lreadline

SRC_FILES := \
    src/tokenizer/tokenizer_helpers.c src/tokenizer/expansion_mode_helpers.c \
    src/tokenizer/redirection_helpers.c src/tokenizer/edge_cases.c \
    src/parser/handle_cmds_and_args.c src/parser/parser_helpers.c \
    src/parser/parser_allocate_helper.c src/tokenizer/buffer.c \
    src/tokenizer/store_token.c src/tokenizer/evaluate_char.c \
    src/tokenizer/tokenize.c src/tokenizer/expansion_mode.c \
    src/builtins/unset_helper.c src/execute/child_parent.c \
    src/execute/execute.c src/execute/execute_helpers.c \
    src/execute/execute_builtin.c src/execute/redirs.c \
    src/builtins/builtin_helpers.c src/builtins/env.c \
    src/input/heredoc_helpers.c src/input/multiline.c \
    src/parser/parser.c src/parser/redirections.c \
    src/clean_exit_helper.c src/error_checking.c \
    src/builtins/echo.c src/builtins/export.c \
    src/builtins/exit.c src/builtins/unset.c \
    src/input/heredoc.c src/input/input.c \
    src/builtins/pwd.c src/builtins/cd.c \
    src/clean_cur.c src/clean_exit.c \
    src/init_helpers.c src/debug.c \
    src/builtins/export_helper.c \
    src/globals.c src/init.c \
    src/main.c src/signal.c \
	src/input/prompt.c\
	src/termios.c

# BONUS_SRC_FILES = 

OBJ_DIR = obj
OBJ_FILES := $(patsubst src/%,$(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

# BONUS_OBJ_FILES =

.PHONY: all clean fclean re leaks bonus

all: $(TARGET)

$(TARGET): $(LIBFT_LIB) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)/**/*.o
	rm -rf $(OBJ_DIR)/*.o

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(TARGET)

re: fclean all


leaks: $(TARGET)
	leaks --atExit -- ./$(TARGET)

# bonus: $(LIBFT_LIB) $(BONUS_TARGET)

# $(BONUS_TARGET)
