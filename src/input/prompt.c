/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 08:18:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/02 14:05:21 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/ft_types.h"

static char	*if_home(t_data *data, char *string)
{
	char	*temp;

	if (strncmp(data->env.user, string, ft_strlen(string)) == 0)
	{
		free(string);
		string = malloc(sizeof(char) * 2);
		malloc_error_check(string, data);
		string[0] = '~';
		string[1] = '\0';
	}
	temp = ft_strjoin(string, " >");
	free(string);
	return (temp);
}

void	update_prompt(t_data *data)
{
	char	*string;
	char	*temp;
	char	**arr;
	int		index;

	index = 0;
	arr = ft_split(data->dir.current, '/');
	string_array_malloc_error_check(arr, data);
	while (arr[index] != NULL)
		index++;
	if (index > 0)
		string = ft_strdup(arr[index - 1]);
	else
		string = ft_strdup("/");
	malloc_error_check(string, data);
	free_arr(arr);
	string = if_home(data, string);
	if (data->env.prompt != NULL)
		free(data->env.prompt);
	temp = ft_strjoin(data->env.user, "@");
	data->env.prompt = ft_strjoin(temp, string);
	free(string);
	free(temp);
}
