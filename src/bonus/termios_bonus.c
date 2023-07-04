/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:43:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 14:43:26 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_manager.h"
#include "minishell.h"
#include "termios.h"
#include "bonus.h"

// For bonus ICANON flag will disable canonical mode (buffered i/o)
void	termios_settings(int disable)
{
	t_term			new;
	
	if (disable == YES)
	{
		tcgetattr(STDIN_FILENO, &new);
		new.c_lflag &= ~(ECHOCTL);
		new.c_lflag &= (~ICANON & ~ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
	}
	else
	{
		tcgetattr(STDIN_FILENO, &new);
        new.c_lflag |= ECHOCTL;
        new.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);
	}
}
