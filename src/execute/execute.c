/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:23:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/21 14:35:54 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_manager.h"
#include "execute.h"

extern int	g_sig_status;

int	do_checks(char *cmd)
{
	struct stat	statbuf;

	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("Shell: .: File name argument requiered\n", 2);
		exit(2);
	}
	stat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode) != 0)
	{
		ft_putstr_fd("Shell: /: is a directory\n", 2);
		exit(126);
	}
	return (0);
}

void	execute_cmd(t_pipes *p, int idx, t_data *data)
{
	char	*path;

	do_checks(data->cur.cmd_list[idx]->cmd);
	if (is_builtin(data->cur.cmd_list[idx]->cmd, data) == 1)
		execute_builtin(p, data);
	path = get_command_path(data->cur.cmd_list[idx]->cmd, data);
	execve(data->cur.cmd_list[idx]->cmd, data->cur.cmd_list[idx]->args,
		data->env.vars);
	execve(path, data->cur.cmd_list[idx]->args, data->env.vars);
	execute_fail(idx, data);
}

void	command_loop(t_pipes *p, t_data *data)
{
	if (p->idx < data->cur.cmd_count - 1)
	{
		pipe(p->pipes[p->idx]);
	}
	g_sig_status = SIG_HAS_CHILD;
	data->sig.exec_pid = fork();
	if (data->sig.exec_pid == 0)
	{
		handle_child(p, data);
	}
	else
	{
		handle_parent(p, data);
		data->cur.cmd_index++;
		p->idx++;
	}
}

static void	handle_errors(t_data *data)
{
	if (data->env.exit_status == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
	else if (data->env.exit_status == SIGSEGV)
		ft_putstr_fd("Segmentation fault: 11\n", 2);
	else if (data->env.exit_status == SIGABRT)
		ft_putstr_fd("Abort: 6\n", 2);
	else if (data->env.exit_status == SIGBUS)
		ft_putstr_fd("Bus error: 10\n", 2);
}

void	execute(t_data *data)
{
	t_pipes	p;

	p.idx = 0;
	if (data->cur.cmd_count == 1
		&& is_builtin(data->cur.cmd_list[0]->cmd, data) == 1)
		execute_builtin(&p, data);
	else
	{
		p.fdin = STDIN_FILENO;
		termios_settings(NO);
		while (p.idx < data->cur.cmd_count)
			command_loop(&p, data);
		while (waitpid(-1, &data->env.exit_status, 0) > 0)
			;
		g_sig_status = SIG_NO_CHILD;
		if (WIFEXITED(data->env.exit_status))
			data->env.exit_status = WEXITSTATUS(data->env.exit_status);
		else
			handle_errors(data);
	}
}
