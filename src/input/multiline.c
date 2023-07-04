/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:22:42 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 17:53:43 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"
#include "input.h"

extern int	g_sig_status;

int	is_multiline(char *input, t_data *data)
{
	int	mode;
	int	i;

	i = 0;
	mode = DEFAULT_MODE;
	while (input[i] != '\0')
	{
		is_mode_changing_char(input[i], &mode, data);
		if (input[i] == '<' && input[i + 1] == '<' && mode == DEFAULT_MODE)
			return (HEREDOC_MODE);
		i++;
	}
	if (mode != HEREDOC_MODE && mode != DEFAULT_MODE)
		return (mode);
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
	else if (mode == DOUBLE_QUOTES_MODE || mode == SINGLE_QUOTES_MODE)
	{
		printf("Shell: cannot accept input (unclosed quotes)\n");
		g_sig_status = SIG_ERROR;
	}
}
