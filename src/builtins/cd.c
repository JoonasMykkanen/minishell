/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:57:54 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/01 14:26:38 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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
		perror("closedir function failed \n");
		clean_exit_shell(data);
	}
	if (chdir(target) != 0)
	{
		perror("chdir function failed \n");
		clean_exit_shell(data);
	}
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
			return (errno);
		data->dir.ptr_target = opendir(target);
		if (open_and_close(target, data) == 1)
			return (errno);
		getcwd(data->dir.current, 1024);
		data->dir.ptr_current = data->dir.ptr_target;
	}
	return (0);
}
