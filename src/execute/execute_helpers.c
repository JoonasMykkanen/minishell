/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:24:26 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 17:51:28 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	what_builtin(char *cmd, t_data *data)
{
	int	idx;

	idx = -1;
	while (++idx < 7)
	{
		if (ft_strncmp(cmd, data->dir.builtins[idx],
				ft_strlen(data->dir.builtins[idx])) == 0)
			break ;
	}
	return (idx);
}

void	update_env_paths(t_data *data)
{
	free_arr(data->env.paths);
	data->env.paths = get_paths(data);
}

char	*get_command_path(char *token, t_data *data)
{
	char	*path_with_slash;
	char	*cmd_path;
	int		i;

	if (is_builtin(token, data) == 1)
	{
		cmd_path = (ft_strdup("builtin"));
		return (cmd_path);
	}
	i = 0;
	update_env_paths(data);
	while (data->env.paths != NULL && data->env.paths[i])
	{
		path_with_slash = ft_strjoin(data->env.paths[i], "/");
		cmd_path = ft_strjoin(path_with_slash, token);
		free(path_with_slash);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return ("not found");
}

void	execute_fail(int idx, t_data *data)
{
	ft_putstr_fd("Shell: ", 2);
	if (ft_strchr(data->cur.cmd_list[idx]->cmd, '/'))
	{
		ft_putstr_fd(data->cur.cmd_list[idx]->cmd, 2);
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
	{
		ft_putstr_fd(data->cur.cmd_list[idx]->cmd, 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	clean_exit_shell(data, CHILD);
	exit(127);
}
