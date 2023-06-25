/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:17:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:28:42 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

void	add_char_to_buffer(char c, t_data *data)
{
	vec_push(&data->cur.token_buffer, (void *)&c);
}

void	clear_and_init_buffer(t_data *data)
{
	vec_free(&data->cur.token_buffer);
	vec_new(&data->cur.token_buffer, 0, sizeof(char));
}

void	add_char_within_quotes(char c, t_data *data)
{
	add_char_to_buffer(c, data);
	store_token_within_quotes(data);
}

void	add_double_greater_than_within_quotes(int *i, t_data *data)
{
	handle_double_greater_than(i, data);
	store_token_within_quotes(data);
}

void	handle_double_greater_than(int *i, t_data *data)
{
	add_char_to_buffer('>', data);
	add_char_to_buffer('>', data);
	*i = *i + 1;
}
