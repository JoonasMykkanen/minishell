/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:57:54 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 16:00:51 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	home_not_set(t_data *data)
{
	ft_putstr_fd("Shell: cd: HOME not set\n", 2);
	data->env.exit_status = 1;
	return (1);
}

static void	update_env(t_data *data, char *var)
{
	char	*temp;
	char	*str;

	temp = malloc(1024 * sizeof(char));
	malloc_error_check(temp, data);
	getcwd(temp, 1024);
	str = ft_strjoin(var, temp);
	free(temp);
	data->env.vars = remove_env_var(var, data);
	data->env.vars = add_arg_to_env_vars(str, data);
	free(str);
}

static int	open_and_close(char *target, t_data *data)
{
	if (!data->dir.ptr_target)
	{
		perror("shell: cd: ");
		free(target);
		return (1);
	}
	if (closedir(data->dir.ptr_current) != 0)
	{
		free(target);
		clean_exit_shell(data, PARENT);
	}
	update_env(data, "OLDPWD=");
	if (chdir(target) != 0)
	{
		free(target);
		clean_exit_shell(data, PARENT);
	}
	update_env(data, "PWD=");
	free(target);
	return (0);
}

int	ft_cd(t_data *data)
{
	char	*target;
	int		len;

	len = arr_len(data);
	if (len > 1)
	{
		target = ft_strdup(data->cur.cmd_list[data->cur.cmd_index]->args[1]);
		data->dir.ptr_target = opendir(target);
		if (open_and_close(target, data) == 1)
			return (errno);
		getcwd(data->dir.current, 1024);
		data->dir.ptr_current = data->dir.ptr_target;
	}
	else
	{
		target = fetch_env_var(ft_strdup("HOME"), data);
		if (target == NULL)
			return (home_not_set(data));
		data->dir.ptr_target = opendir(target);
		if (open_and_close(target, data) == 1)
			return (errno);
		getcwd(data->dir.current, 1024);
		data->dir.ptr_current = data->dir.ptr_target;
	}
	return (0);
}
