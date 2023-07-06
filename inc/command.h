/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:43 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/05 11:39:15 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "../src/libft/inc/libft.h"
# include "minishell.h"
# include "ft_types.h"
# include <fcntl.h>

# define INPUT_REDIR 2
# define OUTPUT_REDIR_OVERWRITE 3
# define OUTPUT_REDIR_APPEND 4
# define APPEND_MODE 1
# define OVERWRITE_MODE 2

int		get_cmd_count(t_data *data);
int		parse_commands(t_data *data);
int		is_delim(int i, t_data *data);
int		allocate_cmd_list(t_data *data);
int		is_builtin(char *cmd, t_data *data);
int		parser_allocate(int i, t_data *data);
t_token	*get_token(int token_idx, t_data *data);
void	initialize_cmd_if_needed(int cmd_idx, t_data *data);
void	parse_single_cmd(int cmd_idx, int *token_idx, t_data *data);
int		check_mode(char *token, int type, int cmd_idx, t_data *data);
void	redirections(int cmd_idx, t_token *t, int *mode, t_data *data);
void	handle_cmd(int cmd_idx, char *token, int *args_index, t_data *data);
void	handle_args(int cmd_idx, char *token, int *args_index, t_data *data);
int		input_redirection(int cmd_idx, char *token, int *mode, t_data *data);
void	cmd_and_args(int cmd_idx, char *token, int *args_index, t_data *data);
int		output_redirection(int cmd_idx, char *token, int *mode, t_data *data);

#endif
