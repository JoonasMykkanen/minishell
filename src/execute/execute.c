/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:23:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/25 18:30:03 by jmykkane         ###   ########.fr       */
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

	path = get_command_path(data->cur.cmd_list[idx]->cmd, data);
	do_checks(path);
	if (is_builtin(data->cur.cmd_list[idx]->cmd, data) == 1)
		execute_builtin(p, data);
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
	data->sig.exec_pid[p->idx] = fork();
	g_sig_status = SIG_HAS_CHILD;
	if (data->sig.exec_pid[p->idx] == 0)
		handle_child(p, data);
	else
	{
		handle_parent(p, data);
		data->cur.cmd_index++;
		p->idx++;
	}
}

static void	handle_errors(int status)
{
	if (status == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
	else if (status == SIGSEGV)
		ft_putstr_fd("Segmentation fault: 11\n", 2);
	else if (status == SIGABRT)
		ft_putstr_fd("Abort: 6\n", 2);
	else if (status == SIGBUS)
		ft_putstr_fd("Bus error: 10\n", 2);
}

void	execute(t_data *data)
{
	int		status[1000];
	int		idx;
	t_pipes	p;

	idx = -1;
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
		while (++idx < p.idx)
			waitpid(data->sig.exec_pid[idx], &status[idx], 0);
		g_sig_status = SIG_NO_CHILD;
		if (WIFEXITED(status[p.idx - 1]))
			data->env.exit_status = WEXITSTATUS(status[p.idx - 1]);
		else
			handle_errors(status[p.idx - 1]);
	}
}
