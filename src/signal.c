/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/29 08:54:31 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_manager.h"
#include "../include/minishell.h"

extern t_data	g_data;
extern int		sig_status;

static void	handle_int(int sig)
{
	const char	nlc[2] = {10, 0};
	const char	eof[2] = {4, 0};

	if (sig == SIGINT)
	{
		if (sig_status == SIG_HEREDOC)
		{
			// g_data.cur.heredoc_mode = 0;
			// g_data.cur.err_flag = 1;
			sig_status = SIG_ERROR;
			ioctl(1, TIOCSTI, eof);
		}
		else if (sig_status == SIG_NO_CHILD)
		{
			rl_on_new_line();
			ioctl(1, TIOCSTI, nlc);
		}
		else
		{
			kill(g_data.sig.exec_pid, SIGINT);
			sig_status = SIG_ERROR;
			// g_data.cur.err_flag = 1;
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

void	handle_ctrl_d(t_data *data)
{
	const char	eof[2] = {4, 0};
	
	if (sig_status == SIG_HEREDOC)
	{
		// data->cur.heredoc_mode = 0;
		ioctl(1, TIOCSTI, eof);
	}
	else if (sig_status == SIG_NO_CHILD)
	{
		ft_exit(data);
	}
}

void	signal_manager(void)
{
	struct sigaction	act_int;
	struct sigaction	act_quit;

	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_quit.sa_mask);
	act_int.sa_flags = SA_RESETHAND;
	act_int.sa_handler = handle_int;
	act_quit.sa_flags = SA_RESETHAND;
	act_quit.sa_handler = handle_quit;
	sigaction(SIGINT, &act_int, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
}
