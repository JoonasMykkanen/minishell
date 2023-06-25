/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 11:45:49 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_manager.h"
#include "../include/minishell.h"

extern t_data	g_data;

static void	handle_int(int sig)
{
	const char	nlc[2] = {10, 0};
	const char	eof[2] = {4, 0};

	if (sig == SIGINT)
	{
		if (g_data.cur.heredoc_mode == 1)
		{
			g_data.cur.heredoc_mode = 0;
			g_data.cur.err_flag = 1;
			ioctl(1, TIOCSTI, eof);
		}
		else if (g_data.sig.exec_pid == NO_CHILDS)
		{
			rl_on_new_line();
			ioctl(1, TIOCSTI, nlc);
		}
		else
		{
			kill(g_data.sig.exec_pid, SIGINT);
			g_data.cur.err_flag = 1;
		}
	}
}

static void	handle_quit(int sig)
{
	if (sig == SIGQUIT || sig == SIGABRT)
	{
		rl_on_new_line();
	}
}

void	handle_ctrl_d(void)
{
	const char	eof[2] = {4, 0};
	
	if (g_data.cur.heredoc_mode == 1)
	{
		g_data.cur.heredoc_mode = 0;
		ioctl(1, TIOCSTI, eof);
	}
	else if (g_data.sig.exec_pid == NO_CHILDS)
	{
		ft_exit();
	}
}

void	signal_manager(void)
{
	struct sigaction	act_int;
	struct sigaction	act_quit;

	act_quit.sa_handler = handle_quit;
	act_int.sa_handler = handle_int;
	act_int.sa_flags = SA_RESTART;
	act_quit.sa_flags = SA_RESTART;
	sigemptyset(&act_quit.sa_mask);
	sigemptyset(&act_int.sa_mask);
	sigaction(SIGINT, &act_int, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
}
