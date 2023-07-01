/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:35:33 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/01 13:34:44 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/signal_manager.h"

extern int	g_sig_status;

static void	reset_cmd_struct(int i, t_data *data)
{
	if (data->cur.cmd_list[i]->cmd)
		free(data->cur.cmd_list[i]->cmd);
	if (data->cur.cmd_list[i]->input)
		free(data->cur.cmd_list[i]->input);
	if (data->cur.cmd_list[i]->output)
		free(data->cur.cmd_list[i]->output);
	data->cur.cmd_list[i]->output_mode = 0;
	if (data->cur.cmd_list[i]->args)
		free_arr(data->cur.cmd_list[i]->args);
	free(data->cur.cmd_list[i]);
}

static void	handle_heredoc_flag(t_data *data)
{
	if (data->cur.heredoc_flag == 1)
	{
		if (unlink("heredoc_temp_file") == -1)
		{
			perror("Error deleting the heredoc temp file");
			clean_exit_shell(data);
		}
		data->cur.heredoc_flag = 0;
	}
}

static void	free_vec_pointers(t_data *data)
{
	char	*str;
	size_t	i;

	i = -1;
	if (data->cur.vec_init == NO)
		return ;
	vec_free(&data->cur.token_buffer);
	while (++i < data->cur.tokens.len)
	{
		str = *(char **)vec_get(&data->cur.tokens, i);
		if (str)
		{
			free(str);
		}
	}
	vec_free(&data->cur.tokens);
	vec_free(&data->cur.types);
}

void	clean_cur_struct(t_data *data)
{
	int	i;

	i = -1;
	if (data->cur.raw)
	{
		free(data->cur.raw);
		data->cur.raw = NULL;
	}
	free_vec_pointers(data);
	while (++i < data->cur.cmd_count)
		reset_cmd_struct(i, data);
	if (data->cur.cmd_list)
	{
		free(data->cur.cmd_list);
		data->cur.cmd_list = NULL;
	}
	data->cur.vec_init = 0;
	data->cur.cmd_count = 0;
	data->cur.cmd_index = 0;
	data->cur.err_flag = 0;
	handle_heredoc_flag(data);
	data->sig.exec_pid = NO_CHILDS;
	g_sig_status = SIG_NO_CHILD;
}
