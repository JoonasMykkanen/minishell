/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:55:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:30:25 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	is_var_to_be_removed(char *to_be_removed, char *current_env_var, t_data *data)
{
	char	*needle;

	needle = ft_strjoin(to_be_removed, "=");
	malloc_error_check(needle, data);
	if (ft_strncmp(current_env_var, needle, ft_strlen(needle)) == 0)
		return (1);
	free(needle);
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
		if (is_var_to_be_removed(arg, data->env.vars[i], data) == 0)
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

// Unset identifiers can not contain = and they obey the same rules for first
// and subsequent characters as export variables
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
	{
		printf("shell: unset: `%s': not a valid identifier\n", arg);
	}
}

int	ft_unset(int cmd_idx, int caller, t_data *data)
{
	int	i;

	i = 1;
	while (data->cur.cmd_list[cmd_idx]->args[i] != NULL)
	{
		handle_unset_env_var(data->cur.cmd_list[cmd_idx]->args[i], caller, data);
		i++;
	}
	return (0);
}
