/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:51:24 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/15 17:21:27 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

static int	choose_builtin(int idx)
{
	int	return_value;

	return_value = 0;
	if (idx == 0)
		return_value = ft_echo(g_data.cur.cmd_index);
	if (idx == 1)
		return_value = ft_cd();
	if (idx == 2)
		return_value = ft_pwd();
	if (idx == 3)
		return_value = ft_export(g_data.cur.cmd_index);
	if (idx == 4)
		return_value = ft_unset(g_data.cur.cmd_index, SHELL);
	if (idx == 5)
		return_value = ft_env();
	if (idx == 6)
		ft_exit();
	return (return_value);
}

void	execute_builtin(t_pipes *p)
{
	int		original_stdout;
	int		return_value;
	char	*cmd;
	int		idx;

	original_stdout = dup(STDOUT);
	handle_output_redirection_for_execution(p);
	cmd = ft_strdup(g_data.cur.cmd_list[g_data.cur.cmd_index]->cmd);
	malloc_error_check(cmd);
	idx = what_builtin(cmd);
	return_value = choose_builtin(idx);
	free(cmd);
	if (g_data.cur.cmd_count == 1)
	{
		close(original_stdout);
		return ;
	}
	if (p->out_redirected == TRUE)
	{
		dup2(original_stdout, STDOUT);
	}
	close(original_stdout);
	if (g_data.cur.cmd_count > 1)
		exit(return_value);
}
