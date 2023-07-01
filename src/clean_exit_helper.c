/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:11:46 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/01 13:30:32 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_arr(char **arr)
{
	int	idx;

	idx = -1;
	if (arr != NULL)
	{
		while (arr[++idx] != NULL)
			free(arr[idx]);
		free(arr);
		arr = NULL;
	}
}
