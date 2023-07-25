/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/25 12:09:48 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "command.h"
#include "minishell.h"

// Store token if buffer is not empty
void	store_token(t_data *data)
{
	if (data->cur.token_buffer.len != 0)
	{
		store_current_token(data);
		clear_and_init_buffer(data);
	}
}

// Store the current token
void	store_current_token(t_data *data)
{
	char	*token;
	int		type;

	type = DEFAULT;
	add_char_to_buffer('\0', data);
	token = ft_strdup((char *)vec_get(&data->cur.token_buffer, 0));
	malloc_error_check(token, data);
	vec_push(&data->cur.tokens, &token);
	vec_push(&data->cur.types, &type);
}

// Store token if buffer is not empty
void	store_token_within_quotes(t_data *data)
{
	if (data->cur.token_buffer.len != 0)
	{
		store_current_token_within_quotes(data);
		clear_and_init_buffer(data);
	}
}

// Store the current token
void	store_current_token_within_quotes(t_data *data)
{
	char	*token;
	int		type;

	type = WITHIN_QUOTES;
	add_char_to_buffer('\0', data);
	token = ft_strdup((char *)vec_get(&data->cur.token_buffer, 0));
	malloc_error_check(token, data);
	vec_push(&data->cur.tokens, &token);
	vec_push(&data->cur.types, &type);
}

void	store_empty_token(t_data *data)
{
	char	*token;
	int		type;

	if (data->cur.vec_init != YES)
		return ;
	type = WITHIN_QUOTES;
	token = ft_strdup("");
	malloc_error_check(token, data);
	vec_push(&data->cur.tokens, &token);
	vec_push(&data->cur.types, &type);
	clear_and_init_buffer(data);
}
