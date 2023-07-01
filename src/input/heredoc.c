/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:08:28 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/01 12:08:07 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/input.h"
#include "../../include/minishell.h"
#include "../../include/signal_manager.h"

extern int	g_sig_status;

void	heredoc_free_delim_and_input(char **delim, char **input)
{
	free(*delim);
	*delim = NULL;
	free(*input);
	*input = NULL;
}

int	open_temp_file(t_data *data)
{
	int	fd;

	fd = open("heredoc_temp_file", O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("");
		clean_exit_shell(data);
		exit(errno);
	}
	return (fd);
}

void	get_input(char *delim, t_data *data)
{
	char	*new_input;
	int		delim_found;
	int		fd;

	fd = open_temp_file(data);
	delim_found = 0;
	while (delim_found == 0 && data->cur.heredoc_mode == 1)
	{
		new_input = readline("> ");
		if (ft_strncmp(new_input, delim, ft_strlen(new_input)) == 0)
			delim_found = 1;
		if (delim_found == 0)
		{
			write(fd, new_input, ft_strlen(new_input));
			write(fd, "\n", 1);
		}
		free(new_input);
	}
	close(fd);
}

char	*get_edited_input(int heredoc_start_idx, char **input, t_data *data)
{
	char	*combined;
	char	*part_a;
	char	*part_b;
	int		delim_end_index;

	part_a = ft_substr(*input, 0, heredoc_start_idx);
	delim_end_index = get_delim_end_index(*input, get_delim_start_index(*input,
				heredoc_start_idx));
	part_b = ft_substr(*input, delim_end_index, ft_strlen(*input)
			- delim_end_index);
	combined = malloc(ft_strlen(part_a) + ft_strlen("heredoc_temp_file")
			+ ft_strlen(part_b) + 3);
	malloc_error_check(combined, data);
	ft_strlcpy(combined, part_a, ft_strlen(part_a) + 1);
	ft_strlcat(combined, "< ", ft_strlen(combined) + 3);
	ft_strlcat(combined, "heredoc_temp_file", ft_strlen(combined)
		+ ft_strlen("heredoc_temp_file") + 1);
	ft_strlcat(combined, part_b, ft_strlen(combined) + ft_strlen(part_b) + 1);
	heredoc_free_part_a_and_b(&part_a, &part_b);
	return (combined);
}

char	*handle_heredoc(char **input, t_data *data)
{
	int		original_status;
	int		heredoc_start_idx;
	char	*delim;
	char	*edited_input;

	original_status = g_sig_status;
	g_sig_status = SIG_HEREDOC;
	data->cur.heredoc_mode = 1;
	heredoc_start_idx = heredoc_start_index(*input, data);
	delim = heredoc_delim(*input, heredoc_start_idx, data);
	get_input(delim, data);
	edited_input = get_edited_input(heredoc_start_idx, input, data);
	data->cur.heredoc_flag = 1;
	heredoc_free_delim_and_input(&delim, input);
	g_sig_status = original_status;
	return (edited_input);
}
