/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:43:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 16:24:59 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	termios_settings(t_data *data)
{
	t_term	new;
	
	
	tcgetattr(STDIN_FILENO, &data->env.settings);
	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}
