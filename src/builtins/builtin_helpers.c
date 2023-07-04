/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:11:12 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 15:21:26 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_env_vars(t_data *data)
{
	int	i;

	i = 0;
	while (data->env.vars[i] != NULL)
	{
		free (data->env.vars[i]);
		data->env.vars[i] = NULL;
		i++;
	}
	free (data->env.vars);
}

int	get_env_var_count(t_data *data)
{
	int	i;

	i = 0;
	while (data->env.vars[i] != NULL)
		i++;
	return (i);
}

int	arr_len(t_data *data)
{
	int	idx;

	idx = 0;
	if (data->cur.cmd_list == NULL)
		return (1);
	while (data->cur.cmd_list[data->cur.cmd_index]->args[idx] != NULL)
		idx++;
	return (idx);
}

int	ft_isvalid_int(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	if (str[0] == '-' && str[1] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_env_var(char *arg, t_data *data)
{
	int		idx;

	idx = -1;
	while (data->env.vars[++idx] != NULL)
	{
		if (ft_strncmp(data->env.vars[idx], arg, ft_strlen(arg)) == 0)
		{
			return (1);
		}
	}
	return (0);
}
