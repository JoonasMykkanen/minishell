/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:13:09 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:39:30 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/init.h"

void	reset_cur(t_data *data)
{
	data->cur.cmd_index = 0;
	data->cur.cmd_count = 0;
}

char	**get_paths(t_data *data)
{
	char	*env_vars;
	char	**paths;
	char	*path_str;

	path_str = ft_strdup("PATH");
	malloc_error_check(path_str, data);
	env_vars = fetch_env_var(path_str, data);
	if (!env_vars)
		return (NULL);
	paths = ft_split(env_vars, ':');
	free(env_vars);
	return (paths);
}

char	*find_env_var(char *str, t_data *data)
{
	int		word_len;
	char	*user;
	int		idx;
	int		len;

	idx = -1;
	len = ft_strlen(str);
	while (data->env.vars[++idx] != NULL)
	{
		if (ft_strncmp(data->env.vars[idx], str, len) == 0)
			break ;
	}
	word_len = ft_strlen(data->env.vars[idx]) - len - 1;
	user = malloc((word_len + 1) * sizeof(char));
	malloc_error_check(user, data);
	ft_memcpy(user, &data->env.vars[idx][len + 1], word_len);
	user[word_len] = '\0';
	return (user);
}
