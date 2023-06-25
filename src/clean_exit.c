/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:47:02 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 10:32:14 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

static void	free_dir(void)
{
	if (g_data.dir.current)
	{
		free(g_data.dir.current);
		g_data.dir.current = NULL;
	}
}

static void	free_env(void)
{
	free_arr(g_data.env.vars);
	free_arr(g_data.env.paths);
	if (g_data.env.user)
	{
		free(g_data.env.user);
		g_data.env.user = NULL;
	}
	if (g_data.env.prompt)
	{
		free(g_data.env.prompt);
		g_data.env.prompt = NULL;
	}
	if (g_data.env.machine)
	{
		free(g_data.env.machine);
		g_data.env.machine = NULL;
	}
}

void	clean_exit_shell(void)
{
	free_dir();
	free_env();
	if (g_data.cur.raw)
	{
		clean_cur_struct();
	}
}
