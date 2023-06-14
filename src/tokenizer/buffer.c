/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:17:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/14 09:43:29 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data	g_data;

void	add_char_to_buffer(char c)
{
	vec_push(&g_data.cur.token_buffer, (void *)&c);
}

void	clear_and_init_buffer(void)
{
	vec_free(&g_data.cur.token_buffer);
	vec_new(&g_data.cur.token_buffer, 0, sizeof(char));
}

void	add_char_within_quotes(char c)
{
	add_char_to_buffer(c);
	store_token_within_quotes();
}

void	add_double_greater_than_within_quotes(int *i)
{
	handle_double_greater_than(i);
	store_token_within_quotes();
}

void	handle_double_greater_than(int *i)
{
	add_char_to_buffer('>');
	add_char_to_buffer('>');
	*i = *i + 1;
}
