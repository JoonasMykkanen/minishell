/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:49:15 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/30 08:35:33 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	handle_with_argument(int idx, t_data *data)
{
	if (ft_isvalid_int(data->cur.cmd_list[idx]->args[1]))
	{
		data->env.exit_status = ft_atoi(data->cur.cmd_list[idx]->args[1]);
		clean_exit_shell(data);
		exit(data->env.exit_status);
	}
	else
	{
		ft_putstr_fd("Shell: Exit: Numeric argument required\n", 2);
		data->env.exit_status = 255;
		clean_exit_shell(data);
		exit(data->env.exit_status);
	}
}

static void	handle_too_many_arguments(int idx, t_data *data)
{
	if (ft_isvalid_int(data->cur.cmd_list[idx]->args[1]))
	{
		if (data->cur.cmd_count == 1)
		{
			ft_putstr_fd("Shell: Exit: too many arguments\n", 2);
			return ;
		}
		else
		{
			clean_exit_shell(data);
			ft_putstr_fd("Shell: Exit: too many arguments\n", 2);
			exit(255);
		}
	}
	clean_exit_shell(data);
	ft_putstr_fd("Shell: Exit: Numeric argument required\n", 2);
	data->env.exit_status = 255;
}

void	ft_exit(t_data *data)
{
	int	idx;
	int	len;

	idx = data->cur.cmd_index;
	len = arr_len(data);
	printf("exit\n");
	if (len == 1)
	{
		clean_exit_shell(data);
		exit(data->env.exit_status);
	}
	else if (len == 2)
		handle_with_argument(idx, data);
	else
		handle_too_many_arguments(idx, data);
}
