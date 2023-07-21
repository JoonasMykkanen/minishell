/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/21 20:50:24 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include "tokenizer.h"

int	evaluate_char(char c, int *mode, int *i, t_data *data)
{
	if (is_terminating_char(c, mode) == true)
		store_token(data);
	if (is_edge_case(&data->cur.raw[*i], mode, i, data) == 1)
		return (0);
	else
	{
		if (is_mode_changing_char(c, mode, data) || is_trigger_char(c, mode))
			return (1);
		if (is_stored_char(c, mode))
			add_char_to_buffer(data->cur.raw[*i], data);
	}
	return (0);
}

int	is_terminating_char(char c, int *mode)
{
	if (*mode == DEFAULT_MODE || *mode == DEFAULT_MODE + 10)
	{
		if (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>'
			|| c == '\n')
			return (true);
	}
	return (false);
}

int	is_stored_char(char c, int *mode)
{
	if (*mode == DEFAULT_MODE)
	{
		if (c == ' ' || c == '>' || c == '<' || c == '\t' || c == '\n'
			|| c == '\'' || c == '\"' || c == '$')
			return (false);
	}
	if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '$')
			return (false);
	}
	return (true);
}

static bool	change_mode_check(int *mode, char c)
{
	if (c == '\'')
	{
		*mode = SINGLE_QUOTES_MODE;
		return (true);
	}
	if (c == '\"')
	{
		*mode = DOUBLE_QUOTES_MODE;
		return (true);
	}
	return (false);
}

int	is_mode_changing_char(char c, int *mode, t_data *data)
{
	if (*mode == DEFAULT_MODE)
	{
		if (change_mode_check(mode, c) == true)
			return (true);
	}
	else if (*mode == DOUBLE_QUOTES_MODE && c == '\"')
	{
		*mode = DEFAULT_MODE;
		if (data->cur.token_buffer.len == 0)
			store_empty_token(data);
		return (true);
	}
	else if (*mode == SINGLE_QUOTES_MODE && c == '\'')
	{
		*mode = DEFAULT_MODE;
		if (data->cur.token_buffer.len == 0)
			store_empty_token(data);
		return (true);
	}
	return (false);
}
