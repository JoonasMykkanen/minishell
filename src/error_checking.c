/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:54 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/03 17:39:44 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

void	malloc_error_check(char *string, t_data *data)
{
	if (!string)
	{
		perror("");
		clean_exit_shell(data, PARENT);
		exit(errno);
	}
}

void	string_array_malloc_error_check(char **string, t_data *data)
{
	if (!string)
	{
		perror("");
		clean_exit_shell(data, PARENT);
		exit(errno);
	}
}
