/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:54 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/25 12:06:22 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	malloc_error_check(char *string, t_data *data)
{
	if (!string)
	{
		perror("");
		clean_exit_shell(data);
		exit(errno);
	}
}

void	string_array_malloc_error_check(char **string, t_data *data)
{
	if (!string)
	{
		perror("");
		clean_exit_shell(data);
		exit(errno);
	}
}
