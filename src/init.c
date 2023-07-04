/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/04 10:40:22 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_manager.h"
#include "minishell.h"
#include "ft_types.h"
#include "init.h"

extern int	g_sig_status;

char	**get_env_vars(char **envp, t_data *data)
{
	char	**vars;
	int		idx;

	idx = 0;
	while (envp[idx] != NULL)
		idx++;
	vars = malloc(sizeof(char *) * (idx + 1));
	string_array_malloc_error_check(vars, data);
	idx = 0;
	while (envp[idx] != NULL)
	{
		vars[idx] = ft_strdup(envp[idx]);
		idx++;
	}
	vars[idx] = NULL;
	return (vars);
}

void	set_builtins(t_data *data)
{
	data->dir.builtins[0] = "echo";
	data->dir.builtins[1] = "cd";
	data->dir.builtins[2] = "pwd";
	data->dir.builtins[3] = "export";
	data->dir.builtins[4] = "unset";
	data->dir.builtins[5] = "env";
	data->dir.builtins[6] = "exit";
}

void	init_directories(t_data *data)
{
	data->dir.current = (char *)malloc(1024);
	malloc_error_check(data->dir.current, data);
	data->dir.home = getenv("HOME");
	data->dir.ptr_current = opendir(data->dir.home);
	chdir(data->dir.home);
	getcwd(data->dir.current, 1024);
}

int	init_struct(char **envp, t_data *data)
{
	*data = (t_data){};
	data->cur = (t_cur){};
	data->env = (t_env){};
	data->his = (t_his){};
	data->sig = (t_sig){};
	data->dir = (t_dir){};
	g_sig_status = SIG_NO_CHILD;
	set_builtins(data);
	init_directories(data);
	data->sig.shell_pid = getpid();
	data->env.vars = get_env_vars(envp, data);
	data->env.paths = get_paths(data);
	data->env.user = find_env_var("USER", data);
	update_prompt(data);
	return (0);
}
