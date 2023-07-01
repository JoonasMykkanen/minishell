/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:19:52 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/01 11:40:57 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/input.h"
#include "../../include/minishell.h"

int	handle_input(char *input, t_data *data)
{
	if (ft_strcmp(input, "quit") == 0)
	{
		free(input);
		exit(0);
	}
	else
	{
		while (is_multiline(input, data) != 0)
			handle_multiline(&input, data);
		data->cur.raw = ft_strdup(input);
		malloc_error_check(data->cur.raw, data);
		free(input);
	}
	return (0);
}
