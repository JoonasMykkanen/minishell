/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:04:33 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/10 13:13:41 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	without_option(int cmd_idx, int idx, int printed_idx, t_data *data)
{
	while (data->cur.cmd_list[cmd_idx]->args[idx] != NULL)
	{
		if (printed_idx > 0)
			printf(" ");
		printf("%s", data->cur.cmd_list[cmd_idx]->args[idx]);
		idx++;
		printed_idx++;
	}
	printf("\n");
}

static int	is_option_n(char *arg)
{
	if (ft_strlen(arg) > 2)
	{
		if (arg[2] != 'n')
			return (0);
	}
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		return (1);
	}
	return (0);
}

static int	has_option_n(int *ptr_idx, t_data *data)
{
	int	printable_found;
	int	has_option_n;
	int	i;

	i = 0;
	has_option_n = 0;
	printable_found = 0;
	while (data->cur.cmd_list[data->cur.cmd_index]->args[++i] != NULL)
	{
		if (is_option_n(data->cur.cmd_list[data->cur.cmd_index]->args[i]) == 1)
		{
			if (i > 0 && printable_found == 1)
				continue ;
			if (i > 1 && has_option_n == 0)
				break ;
			(*ptr_idx)++;
			if (i == 1)
				has_option_n = 1;
		}
		else
			printable_found = 1;
	}
	return (has_option_n);
}

static void	with_option(int cmd_idx, int idx, t_data *data)
{
	while (data->cur.cmd_list[cmd_idx]->args[idx] != NULL)
	{
		if (cmd_idx > 0)
			printf(" ");
		printf("%s", data->cur.cmd_list[cmd_idx]->args[idx]);
		idx++;
	}
}

int	ft_echo(int cmd_idx, t_data *data)
{
	int	idx;
	int	printed_idx;

	printed_idx = 0;
	idx = 1;
	if (has_option_n(&idx, data) == 1)
	{
		with_option(cmd_idx, idx, data);
	}
	else
	{
		without_option(cmd_idx, idx, printed_idx, data);
	}
	return (0);
}
