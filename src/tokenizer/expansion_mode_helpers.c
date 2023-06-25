/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_mode_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:51:57 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/25 15:42:06 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"
#include "../../include/tokenizer.h"

// Fetch environment variable
char	*fetch_env_var(char *str, t_data *data)
{
	int		idx;
	int		len;
	char	*needle;
	int		word_len;
	char	*var;

	idx = -1;
	needle = ft_strjoin(str, "=");
	malloc_error_check(needle, data);
	len = ft_strlen(needle);
	free(str);
	while (data->env.vars[++idx] != NULL)
	{
		if (ft_strncmp(data->env.vars[idx], needle, len) == 0)
			break ;
	}
	if (data->env.vars[idx] == NULL)
		return (NULL);
	word_len = ft_strlen(data->env.vars[idx]) - len;
	var = malloc((word_len + 1) * sizeof(char));
	malloc_error_check(var, data);
	ft_strlcpy(var, &data->env.vars[idx][len], word_len + 1);
	free(needle);
	return (var);
}

// Check if the character is a letter or underscore
int	is_valid_first_character(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
								|| c == '_' || c == '=')
		return (1);
	return (0);
}

// Check if the character is a letter, digit, or underscore
int	is_valid_subsequent_character(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

int	is_exit_status_expansion(int j, t_data *data)
{
	if (data->cur.raw[j] == '?' && (data->cur.raw[j + 1] == ' ' \
								|| data->cur.raw[j + 1] == '\0'))
		return (1);
	else
		return (0);
}
