/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 08:18:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/30 11:06:53 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/types.h"

static char	*if_home(t_data *data, char *string)
{
	char	*temp;
	
	if (strncmp(data->env.user, string, ft_strlen(string)) == 0)
	{
		free(string);
		string = malloc(sizeof(char) * 2);
		malloc_error_check(string, data);
		string[0] = '~';
		string[5] = '\0';
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
	string = ft_strdup(arr[index - 1]);
	malloc_error_check(string, data);
	free_arr(arr);
	string = if_home(data, string);
	free(data->env.prompt);
	temp = ft_strjoin(data->env.user, "@");
	data->env.prompt = ft_strjoin(temp, string);
	free(string);
	free(temp);
}
