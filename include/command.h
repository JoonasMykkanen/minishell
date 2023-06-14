/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:43 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/14 12:10:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "../src/libft/libft.h"
# include "minishell.h"
# include "types.h"
# include <fcntl.h>

# define INPUT_REDIR 2
# define OUTPUT_REDIR_OVERWRITE 3
# define OUTPUT_REDIR_APPEND 4
# define APPEND_MODE 1
# define OVERWRITE_MODE 2

int		is_delim(int i);
int		get_cmd_count(void);
int		parse_commands(void);
int		tokenize_input(void);
int		is_builtin(char *cmd);
int		parser_allocate(int i);
int		allocate_cmd_list(void);
t_token	*get_token(int token_idx);
void	parse_single_cmd(int cmd_idx, int *token_idx);
int		check_mode(char *token, int type, int cmd_idx);
void	handle_cmd(int cmd_idx, char *token, int *args_index);
void	handle_args(int cmd_idx, char *token, int *args_index);
int		handle_input_redirection(int cmd_idx, char *token, int *mode);
void	handle_cmd_and_args(int cmd_idx, char *token, int *args_index);
int		handle_output_redirection(int cmd_idx, char *token, int *mode);

#endif
