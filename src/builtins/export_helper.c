/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:17:13 by jmykkane          #+#    #+#             */
/*   Updated: 2023/07/21 14:46:42 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	need_to_update(char *arg, t_data *data)
{
	char	*needle;
	char	**temp;
	int		idx;

	idx = -1;
	temp = ft_split(arg, '=');
	needle = ft_strdup(temp[0]);
	if (temp[1] == NULL)
	{
		free(needle);
		free_arr(temp);
		return (0);
	}
	free_arr(temp);
	while (data->env.vars[++idx] != NULL)
	{
		if (ft_strncmp(data->env.vars[idx], needle, ft_strlen(needle)) == 0)
		{
			free(needle);
			return (1);
		}
	}
	free(needle);
	return (0);
}

int	handle_no_args(t_data *data)
{
	if (arr_len(data) < 2)
	{
		ft_putstr_fd("Shell: Export: No arguments given\n", 2);
		return (1);
	}
	return (0);
}
