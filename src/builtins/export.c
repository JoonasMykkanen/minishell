/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/30 12:56:55 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	is_valid_env_variable_value(char *arg)
{
	if (arg[0] == '\0')
		return (0);
	return (1);
}

int	is_valid_env_variable_name(char *arg)
{
	int	i;

	i = 0;
	if (is_valid_first_character(arg[i]) != 1)
		return (0);
	i++;
	while (arg[i] != '=')
	{
		if (is_valid_subsequent_character(arg[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier(char *arg)
{
	char	*equal_sign_ptr;
	int		is_valid;

	is_valid = 1;
	equal_sign_ptr = ft_strchr(arg, '=');
	if (equal_sign_ptr == NULL)
	{
		is_valid = 0;
	}
	if (is_valid == 1 && is_valid_env_variable_name(arg) != 1)
	{
		is_valid = 0;
	}
	if (is_valid == 1 && is_valid_env_variable_value(equal_sign_ptr + 1) != 1)
	{
		is_valid = 0;
	}
	return (is_valid);
}

char	**add_arg_to_env_vars(char *arg, t_data *data)
{
	char	**new_env_vars;
	int		i;

	i = 0;
	new_env_vars = (char **)malloc((get_env_var_count(data) + 2) * sizeof(char *));
	string_array_malloc_error_check(new_env_vars, data);
	while (data->env.vars[i] != NULL)
	{
		new_env_vars[i] = ft_strdup(data->env.vars[i]);
		malloc_error_check(new_env_vars[i], data);
		i++;
	}
	new_env_vars[i] = ft_strdup(arg);
	new_env_vars[i + 1] = NULL;
	free_env_vars(data);
	return (new_env_vars);
}

int	ft_export(int cmd_idx, t_data *data)
{
	int		env_var_idx;
	char	*arg;
	int		i;

	i = 1;
	env_var_idx = 0;
	arg = ft_strdup(data->cur.cmd_list[cmd_idx]->args[i]);
	malloc_error_check(arg, data);
	if (data->cur.cmd_list[cmd_idx]->args[1] == NULL)
	{
		while (data->env.vars[env_var_idx] != NULL)
			env_var_idx++;
	}
	while (data->cur.cmd_list[cmd_idx]->args[i] != NULL)
	{
		if (is_valid_identifier(arg) == 1)
		{
			ft_unset(cmd_idx, EXPORT, data);
			data->env.vars = add_arg_to_env_vars(arg, data);
		}
		else
			ft_printf("export: `%s': not a valid identifier\n", arg);
		i++;
	}
	return (0);
}
