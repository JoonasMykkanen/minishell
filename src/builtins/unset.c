/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:55:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 15:24:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_var_to_be_removed(char *to_be_removed, char *cur_env_var)
{
	if (ft_strncmp(cur_env_var, to_be_removed, ft_strlen(to_be_removed)) == 0)
		return (1);
	return (0);
}

char	**remove_env_var(char *arg, t_data *data)
{
	char	**new_env_vars;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env_vars = (char **)malloc(get_env_var_count(data) * sizeof(char *));
	string_array_malloc_error_check(new_env_vars, data);
	while (data->env.vars[i] != NULL)
	{
		if (is_var_to_be_removed(arg, data->env.vars[i]) == 0)
		{
			new_env_vars[j] = ft_strdup(data->env.vars[i]);
			malloc_error_check(new_env_vars[j], data);
			j++;
		}
		i++;
	}
	new_env_vars[j] = NULL;
	free_env_vars(data);
	return (new_env_vars);
}

int	is_valid_unset_identified(char *arg)
{
	int	i;

	i = 1;
	if (ft_strchr(arg, '=') != NULL)
	{
		return (0);
	}
	if (is_valid_first_character(arg[0]) == 0)
	{
		return (0);
	}
	while (arg[i] != '\0')
	{
		if (is_valid_subsequent_character(arg[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	handle_unset_env_var(char *arg, int caller, t_data *data)
{
	char	*arg_without_equal;

	if (is_valid_unset_identified(arg))
	{
		if (is_env_var(arg, data) == 1)
			data->env.vars = remove_env_var(arg, data);
	}
	else if (caller == EXPORT)
	{
		arg_without_equal = extract_until_equal(arg, data);
		if (is_env_var(arg_without_equal, data) == 1)
			data->env.vars = remove_env_var(arg_without_equal, data);
		free(arg_without_equal);
	}
	else
		printf("shell: unset: `%s': not a valid identifier\n", arg);
}

int	ft_unset(int cmd_idx, int caller, t_data *data)
{
	char	*ptr;
	int		i;

	i = 1;
	while (data->cur.cmd_list[cmd_idx]->args[i] != NULL)
	{
		ptr = data->cur.cmd_list[cmd_idx]->args[i];
		handle_unset_env_var(ptr, caller, data);
		i++;
	}
	return (0);
}
