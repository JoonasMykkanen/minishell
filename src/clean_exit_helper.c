/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:11:46 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/10 13:13:14 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

void	free_arr(char **arr)
{
	int	idx;

	idx = -1;
	if (arr)
	{
		while (arr[++idx] != NULL)
			free(arr[idx]);
		free(arr);
	}
}
