/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:16:08 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/01 11:54:55 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

int	handle_within_quotes(char c, char next_c, int *i, t_data *data)
{
	if (c == '<' && (next_c == '\'' || next_c == '\"'))
	{
		add_char_within_quotes(c, data);
		return (1);
	}
	else if (c == '>' && next_c != '>' && (data->cur.raw[*i + 1] == '\''
			|| data->cur.raw[*i + 1] == '\"'))
	{
		add_char_within_quotes(c, data);
		return (1);
	}
	else if (c == '|' && (next_c == '\'' || next_c == '\"'))
	{
		add_char_within_quotes(c, data);
		return (1);
	}
	else if (c == '>' && next_c == '>' && (data->cur.raw[*i + 2] == '\''
			|| data->cur.raw[*i + 2] == '\"'))
	{
		add_double_greater_than_within_quotes(i, data);
		return (1);
	}
	return (0);
}

int	handle_default_mode(char c, char next_c, int *i, t_data *data)
{
	if (c == '>' && next_c == '>')
	{
		handle_double_greater_than(i, data);
		store_token(data);
		return (1);
	}
	else if (c == '>' && next_c != '>')
	{
		add_char_to_buffer(c, data);
		store_token(data);
		return (1);
	}
	else if (c == '<')
	{
		add_char_to_buffer(c, data);
		store_token(data);
		return (1);
	}
	else if (c == '|')
	{
		add_char_to_buffer(c, data);
		store_token(data);
		return (1);
	}
	return (0);
}

int	is_edge_case(char *ptr, int *mode, int *i, t_data *data)
{
	char	next_c;
	char	c;

	c = *ptr;
	next_c = *(ptr + 1);
	if ((*mode == SINGLE_QUOTES_MODE || *mode == DOUBLE_QUOTES_MODE))
	{
		return (handle_within_quotes(c, next_c, i, data));
	}
	else if (*mode == DEFAULT_MODE)
	{
		return (handle_default_mode(c, next_c, i, data));
	}
	return (0);
}
