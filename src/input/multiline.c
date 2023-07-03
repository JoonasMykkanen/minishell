/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:22:42 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 13:29:17 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"
#include "input.h"

char	*update_multiline_buffer(char *buffer, char *new_input, t_data *data)
{
	char	*temp;

	temp = malloc(ft_strlen(buffer) + ft_strlen(new_input) + 2);
	malloc_error_check(temp, data);
	ft_strlcpy(temp, buffer, ft_strlen(buffer) + 1);
	ft_strlcat(temp, "\n", ft_strlen(buffer) + ft_strlen("\n") + 1);
	ft_strlcat(temp, new_input, ft_strlen(temp) + ft_strlen(new_input) + 1);
	free(buffer);
	free(new_input);
	return (temp);
}

// Combines the original input with the buffer containing multiline input
char	*combine_buffers(char *input, char *buffer, t_data *data)
{
	char	*temp;

	temp = malloc(ft_strlen(input) + ft_strlen(buffer) + 1);
	malloc_error_check(temp, data);
	ft_strlcpy(temp, input, ft_strlen(input) + 1);
	ft_strlcat(temp, buffer, ft_strlen(temp) + ft_strlen(buffer) + 1);
	free(input);
	free(buffer);
	return (temp);
}

char	*handle_unclosed_quote(char *input, int mode, t_data *data)
{
	char	*new_input;
	int		i;
	char	*buffer;

	buffer = malloc(1);
	malloc_error_check(buffer, data);
	buffer[0] = '\0';
	while (mode != DEFAULT_MODE)
	{
		i = 0;
		new_input = readline("> ");
		while (new_input[i] != '\0')
		{
			is_mode_changing_char(new_input[i], &mode, data);
			i++;
		}
		buffer = update_multiline_buffer(buffer, new_input, data);
	}
	return (combine_buffers(input, buffer, data));
}

int	is_multiline(char *input, t_data *data)
{
	int	i;
	int	mode;

	i = 0;
	mode = DEFAULT_MODE;
	while (input[i] != '\0')
	{
		is_mode_changing_char(input[i], &mode, data);
		if (input[i] == '<' && input[i + 1] == '<' && mode == DEFAULT_MODE)
			return (HEREDOC_MODE);
		i++;
	}
	if (mode != DEFAULT_MODE)
	{
		return (mode);
	}
	return (0);
}

void	handle_multiline(char **input, t_data *data)
{
	int	mode;

	mode = is_multiline(*input, data);
	if (mode == HEREDOC_MODE)
	{
		*input = handle_heredoc(input, data);
	}
	else if (mode == SINGLE_QUOTES_MODE || mode == DOUBLE_QUOTES_MODE)
	{
		*input = handle_unclosed_quote(*input, mode, data);
	}
}
