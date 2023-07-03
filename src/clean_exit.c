/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:47:02 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 13:27:42 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_dir(t_data *data)
{
	if (data->dir.current)
	{
		free(data->dir.current);
		data->dir.current = NULL;
	}
}

static void	free_env(t_data *data)
{
	free_arr(data->env.vars);
	free_arr(data->env.paths);
	if (data->env.user)
	{
		free(data->env.user);
		data->env.user = NULL;
	}
	if (data->env.prompt)
	{
		free(data->env.prompt);
		data->env.prompt = NULL;
	}
	if (data->env.machine)
	{
		free(data->env.machine);
		data->env.machine = NULL;
	}
}

// Free's everything that is malloced and reset terminal settings to original state
void	clean_exit_shell(t_data *data)
{
	free_dir(data);
	free_env(data);
	if (data->cur.raw)
	{
		clean_cur_struct(data);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &data->env.settings);
}
