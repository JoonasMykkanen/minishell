/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 08:58:41 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal_manager.h"
#include "../../include/minishell.h"
#include "../../include/bonus.h"

extern int		g_sig_status;

static void	handle_int(int sig)
{
	const char	nlc[2] = {10, 0};
	const char	eof[2] = {4, 0};

	if (sig == SIGINT)
	{
		if (g_sig_status == SIG_HEREDOC)
		{
			g_sig_status = SIG_ERROR;
			ioctl(1, TIOCSTI, eof);
		}
		else if (g_sig_status == SIG_NO_CHILD)
		{
			g_sig_status = SIG_ERROR;
			ioctl(1, TIOCSTI, nlc);
		}
		else if (g_sig_status == SIG_HAS_CHILD)
		{
			kill(CHILDS, SIGINT);
			g_sig_status = SIG_ERROR;
		}
	}
}

static void	handle_quit(int sig)
{
	const char	nlc[2] = {10, 0};
	
	if (sig == SIGQUIT || sig == SIGABRT)
	{
		g_sig_status = SIG_ERROR;
		ioctl(1, TIOCSTI, nlc);
	}
}

void	handle_ctrl_d(t_data *data)
{
	const char	eof[2] = {4, 0};

	if (g_sig_status == SIG_HEREDOC)
	{
		ioctl(1, TIOCSTI, eof);
	}
	else if (g_sig_status == SIG_NO_CHILD)
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
	act_int.sa_flags = SA_RESTART;
	act_int.sa_handler = handle_int;
	act_quit.sa_flags = SA_RESTART;
	act_quit.sa_handler = handle_quit;
	sigaction(SIGINT, &act_int, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
}
