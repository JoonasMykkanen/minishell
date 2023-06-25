/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:28:46 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"
#include "../../include/debug.h"

/*
	Redirections can only accept certain tokens as arguments 
	and an invalid is a syntax error.
*/
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

int	handle_input_redirection(int cmd_idx, char *token, int *mode, t_data *data)
{
	if (is_valid_arg_for_redirection(token) == 0)
	{
		data->cur.err_flag = 1;
		printf("syntax error near unexpected token `%s'\n", token);
		return (1);
	}
	data->cur.cmd_list[cmd_idx]->input = ft_strdup(token);
	*mode = DEFAULT_MODE;
	return (0);
}

int	handle_output_redirection(int cmd_idx, char *token, int *mode, t_data *data)
{
	if (is_valid_arg_for_redirection(token) == 0)
	{
		data->cur.err_flag = 1;
		printf("syntax error near unexpected token `%s'\n", token);
		return (1);
	}
	data->cur.cmd_list[cmd_idx]->output = ft_strdup(token);
	if (*mode == OUTPUT_REDIR_APPEND)
		data->cur.cmd_list[cmd_idx]->output_mode = APPEND_MODE;
	else if (*mode == OUTPUT_REDIR_OVERWRITE)
		data->cur.cmd_list[cmd_idx]->output_mode = OVERWRITE_MODE;
	*mode = DEFAULT_MODE;
	return (0);
}
