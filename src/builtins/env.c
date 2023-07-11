/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:47:13 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/11 21:35:30 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_list(t_data *data)
{
	int	idx;

	idx = -1;
	while (data->env.vars[++idx] != NULL)
	{
		if (ft_strchr(data->env.vars[idx], '=') != NULL)
			printf("%s \n", data->env.vars[idx]);
	}
}

int	ft_env(t_data *data)
{
	int	count;

	count = arr_len(data);
	if (count > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(data->cur.cmd_list[data->cur.cmd_index]->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (data->env.vars)
		print_list(data);
	else
	{
		perror("problem with env");
		clean_exit_shell(data, PARENT);
		return (1);
	}
	return (0);
}
