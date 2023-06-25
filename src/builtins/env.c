/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:47:13 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:29:51 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_env(t_data *data)
{
	int	idx;

	idx = -1;
	if (data->env.vars)
	{
		while (data->env.vars[++idx] != NULL)
			printf("%s \n", data->env.vars[idx]);
	}
	else
	{
		perror("problem with env");
		clean_exit_shell(data);
		return (1);
	}
	return (0);
}
