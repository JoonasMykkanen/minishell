/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:54 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/03 13:27:33 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
