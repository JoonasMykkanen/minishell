/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:47:13 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/11 14:49:05 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_data *data)
{
	int	count;
	int	idx;

	idx = -1;
	count = arr_len(data);
	if (count > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(data->cur.cmd_list[data->cur.cmd_index]->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (data->env.vars)
	{
		while (data->env.vars[++idx] != NULL)
			printf("%s \n", data->env.vars[idx]);
	}
	else
	{
		perror("problem with env");
		clean_exit_shell(data, PARENT);
		return (1);
	}
	return (0);
}
