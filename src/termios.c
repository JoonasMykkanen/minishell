/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:43:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 14:43:35 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	termios_settings(int disable)
{
	t_term	new;
	
	if (disable == YES)
	{
		tcgetattr(STDIN_FILENO, &new);
		new.c_lflag &= (~ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
	}
	else
	{
		tcgetattr(STDIN_FILENO, &new);
		new.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
	}
}
