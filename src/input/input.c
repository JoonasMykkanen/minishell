/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:19:52 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/25 15:10:23 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "input.h"
#include "minishell.h"

extern int	g_sig_status;

int	handle_input(char *input, t_data *data)
{
	if (ft_strcmp(input, "quit") == 0)
	{
		free(input);
		clean_exit_shell(data, PARENT);
		exit(0);
	}
	else
	{
		while (is_multiline(input, data) != 0)
		{
			handle_multiline(&input, data);
			if (g_sig_status == SIG_ERROR)
			{
				free(input);
				return (1);
			}
		}
		data->cur.raw = ft_strdup(input);
		malloc_error_check(data->cur.raw, data);
		free(input);
		input = NULL;
	}
	return (0);
}
