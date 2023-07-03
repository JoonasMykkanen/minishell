/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:43:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 13:31:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// For bonus ICANON flag will disable canonical mode (buffered i/o)
void	termios_settings(t_data *data)
{
	t_term	new;
	t_term	old;
	
	tcgetattr(STDIN_FILENO, &old);
	data->env.settings = old;
	new = old;
	new.c_lflag &= ~ECHOCTL;
	new.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}
