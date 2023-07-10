/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:43:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/10 13:00:07 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	termios_settings(int disable)
{
	t_term	term_settings;

	if (disable == YES)
	{
		tcgetattr(STDIN_FILENO, &term_settings);
		term_settings.c_lflag &= (~ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
	}
	else
	{
		tcgetattr(STDIN_FILENO, &term_settings);
		term_settings.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
	}
}
