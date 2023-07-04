/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:47:02 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 13:48:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

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

// Free's everything that is malloced and reset terminal settings to original state
void	clean_exit_shell(t_data *data, int	caller)
{
	free_dir(data);
	free_env(data);
	printf("env reset done \n");
	clean_cur_struct(data);
	if (caller == PARENT)
		termios_settings(NO);
}
