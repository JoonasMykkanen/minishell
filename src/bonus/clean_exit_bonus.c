/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:47:02 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/10 12:53:30 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"
#include "bonus.h"

static void	free_dir(t_data *data)
{
	free(data->dir.current);
	data->dir.current = NULL;
}

static void	free_env(t_data *data)
{
	free_arr(data->env.vars);
	free_arr(data->env.paths);
	free(data->env.user);
	data->env.user = NULL;
	free(data->env.prompt);
	data->env.prompt = NULL;
	free(data->env.machine);
	data->env.machine = NULL;
}

void	clean_exit_shell(t_data *data, int caller)
{
	free_dir(data);
	free_env(data);
	clean_cur_struct(data);
	if (caller == PARENT)
		termios_settings(NO);
	printf(ENABLE_CURSOR);
}
