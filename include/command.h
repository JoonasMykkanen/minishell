/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:43 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/25 14:59:24 by joonasmykka      ###   ########.fr       */
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

int		is_delim(int i, t_data *data);
int		get_cmd_count(t_data *data);
int		parse_commands(t_data *data);
int		is_builtin(char *cmd, t_data *data);
int		parser_allocate(int i, t_data *data);
int		allocate_cmd_list(t_data *data);
t_token	*get_token(int token_idx, t_data *data);
void	parse_single_cmd(int cmd_idx, int *token_idx, t_data *data);
int		check_mode(char *token, int type, int cmd_idx, t_data *data);
void	handle_cmd(int cmd_idx, char *token, int *args_index, t_data *data);
void	handle_args(int cmd_idx, char *token, int *args_index, t_data *data);
int		handle_input_redirection(int cmd_idx, char *token, int *mode, t_data *data);
void	handle_cmd_and_args(int cmd_idx, char *token, int *args_index, t_data *data);
int		handle_output_redirection(int cmd_idx, char *token, int *mode, t_data *data);

#endif
