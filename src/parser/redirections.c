/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/11 21:41:03 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "debug.h"
#include "minishell.h"
#include "signal_manager.h"

extern int	g_sig_status;

int	is_valid_arg_for_redirection(char *token)
{
	if (ft_strncmp("|", token, ft_strlen(token)) == 0)
		return (0);
	if (ft_strncmp("<", token, ft_strlen(token)) == 0)
		return (0);
	if (ft_strncmp(">", token, ft_strlen(token)) == 0)
		return (0);
	return (1);
}

int	input_redirection(int cmd_idx, char *token, int *mode, t_data *data)
{
	if (is_valid_arg_for_redirection(token) == 0)
	{
		data->cur.err_flag = 1;
		g_sig_status = SIG_ERROR;
		printf("syntax error near unexpected token `%s'\n", token);
		return (1);
	}
	data->cur.cmd_list[cmd_idx]->input = ft_strdup(token);
	*mode = DEFAULT_MODE;
	return (0);
}

int	output_redirection(int cmd_idx, char *token, int *mode, t_data *data)
{
	int	fd;

	if (is_valid_arg_for_redirection(token) == 0)
	{
		data->cur.err_flag = 1;
		g_sig_status = SIG_ERROR;
		printf("syntax error near unexpected token `%s'\n", token);
		return (1);
	}
	fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error output file creation");
		clean_exit_shell(data, PARENT);
	}
	else
		close(fd);
	data->cur.cmd_list[cmd_idx]->output = ft_strdup(token);
	if (*mode == OUTPUT_REDIR_APPEND)
		data->cur.cmd_list[cmd_idx]->output_mode = APPEND_MODE;
	else if (*mode == OUTPUT_REDIR_OVERWRITE)
		data->cur.cmd_list[cmd_idx]->output_mode = OVERWRITE_MODE;
	*mode = DEFAULT_MODE;
	return (0);
}

void	redirections(int cmd_idx, t_token *t, int *mode, t_data *data)
{
	if (*mode == INPUT_REDIR)
	{
		input_redirection(cmd_idx, t->token, mode, data);
	}
	else if (*mode == OUTPUT_REDIR_APPEND || *mode == OUTPUT_REDIR_OVERWRITE)
	{
		output_redirection(cmd_idx, t->token, mode, data);
	}
}
