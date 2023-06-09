/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_allocate_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:21:26 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 17:44:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"

int	parser_allocate(int i, t_data *data)
{
	data->cur.cmd_list[i] = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data->cur.cmd_list[i])
	{
		perror("");
		clean_exit_shell(data, PARENT);
		return (1);
	}
	data->cur.cmd_list[i]->args = NULL;
	data->cur.cmd_list[i]->cmd = NULL;
	data->cur.cmd_list[i]->input = NULL;
	data->cur.cmd_list[i]->output = NULL;
	data->cur.cmd_list[i]->output_mode = 0;
	return (0);
}

void	initialize_cmd_if_needed(int cmd_idx, t_data *data)
{
	if (data->cur.cmd_list[cmd_idx] == NULL)
	{
		data->cur.cmd_list[cmd_idx] = (t_cmd *)malloc(sizeof(t_cmd));
		if (data->cur.cmd_list[cmd_idx] == NULL)
		{
			clean_exit_shell(data, PARENT);
			perror("Error creating cmd_list");
			exit(errno);
		}
		data->cur.cmd_list[cmd_idx]->cmd = NULL;
		data->cur.cmd_list[cmd_idx]->args = ft_calloc(100, sizeof(char *));
		data->cur.cmd_list[cmd_idx]->input = NULL;
		data->cur.cmd_list[cmd_idx]->output = NULL;
	}
}
