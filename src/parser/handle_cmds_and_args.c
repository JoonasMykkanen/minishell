/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_and_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:21:26 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 13:28:45 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include "ft_types.h"

void	handle_cmd(int cmd_idx, char *token, int *args_index, t_data *data)
{
	data->cur.cmd_list[cmd_idx]->cmd = ft_strdup(token);
	malloc_error_check(data->cur.cmd_list[cmd_idx]->cmd, data);
	data->cur.cmd_list[cmd_idx]->args = (char **)malloc(100 * sizeof(char *));
	string_array_malloc_error_check(data->cur.cmd_list[cmd_idx]->args, data);
	data->cur.cmd_list[cmd_idx]->args[(*args_index)++] = ft_strdup(token);
}

void	handle_args(int cmd_idx, char *token, int *args_index, t_data *data)
{
	data->cur.cmd_list[cmd_idx]->args[*args_index] = ft_strdup(token);
	malloc_error_check(data->cur.cmd_list[cmd_idx]->args[*args_index], data);
	(*args_index)++;
}

void	cmd_and_args(int cmd_idx, char *token, int *args_index,
		t_data *data)
{
	if (data->cur.cmd_list[cmd_idx]->cmd == NULL)
	{
		handle_cmd(cmd_idx, token, args_index, data);
	}
	else
	{
		handle_args(cmd_idx, token, args_index, data);
	}
}
