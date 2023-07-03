/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:10:30 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/03 13:29:47 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "input.h"
#include "minishell.h"

int	heredoc_start_index(char *input, t_data *data)
{
	int	idx;
	int	mode;

	idx = 0;
	mode = DEFAULT_MODE;
	while (input[idx] != '\0')
	{
		is_mode_changing_char(input[idx], &mode, data);
		if (input[idx] == '<' && input[idx + 1] == '<' && mode == DEFAULT_MODE)
			return (idx);
		idx++;
	}
	return (-1);
}

int	get_delim_start_index(char *input, int heredoc_start_idx)
{
	int	delim_start_idx;
	int	idx;

	idx = heredoc_start_idx;
	while (input[idx] && input[idx] != '\0' && ft_isalpha(input[idx]) == 0)
		idx++;
	delim_start_idx = idx;
	return (delim_start_idx);
}

int	get_delim_end_index(char *input, int delim_start_idx)
{
	int	delim_end_idx;
	int	idx;

	idx = delim_start_idx;
	while (ft_isalnum(input[idx]) == 1 && input[idx] != '\0')
		idx++;
	delim_end_idx = idx;
	return (delim_end_idx);
}

char	*heredoc_delim(char *input, int heredoc_start_idx, t_data *data)
{
	int		delim_start_idx;
	int		delim_end_idx;
	int		delim_len;
	char	*delim;

	delim_start_idx = get_delim_start_index(input, heredoc_start_idx);
	delim_end_idx = get_delim_end_index(input, delim_start_idx);
	delim_len = delim_end_idx - delim_start_idx;
	delim = ft_substr(input, delim_start_idx, delim_len);
	malloc_error_check(delim, data);
	return (delim);
}

void	heredoc_free_part_a_and_b(char **part_a, char **part_b)
{
	if (*part_a)
	{
		free(*part_a);
		*part_a = NULL;
	}
	if (*part_b)
	{
		free(*part_b);
		*part_b = NULL;
	}
}
