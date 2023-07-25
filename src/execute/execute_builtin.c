/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:51:24 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/25 09:42:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	choose_builtin(int idx, t_data *data)
{
	int	return_value;

	return_value = 0;
	if (idx == 0)
		return_value = ft_echo(data->cur.cmd_index, data);
	if (idx == 1)
		return_value = ft_cd(data);
	if (idx == 2)
		return_value = ft_pwd(data);
	if (idx == 3)
		return_value = ft_export(data->cur.cmd_index, data);
	if (idx == 4)
		return_value = ft_unset(data->cur.cmd_index, SHELL, data);
	if (idx == 5)
		return_value = ft_env(data);
	if (idx == 6)
		ft_exit(data);
	return (return_value);
}

void	execute_builtin(t_pipes *p, t_data *data)
{
	int		original_stdout;
	int		return_value;
	char	*cmd;
	int		idx;

	original_stdout = dup(STDOUT_FILENO);
	handle_output_redirection_for_execution(p, data);
	cmd = ft_strdup(data->cur.cmd_list[data->cur.cmd_index]->cmd);
	malloc_error_check(cmd, data);
	idx = what_builtin(cmd, data);
	free(cmd);
	return_value = choose_builtin(idx, data);
	if (p->out_redirected == TRUE)
		dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	if (data->cur.cmd_count > 1)
		exit(return_value);
}
