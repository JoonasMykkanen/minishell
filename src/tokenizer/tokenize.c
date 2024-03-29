/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/25 12:05:26 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "command.h"
#include "minishell.h"

static void	create_vectors(t_data *data)
{
	data->cur.vec_init = YES;
	vec_new(&data->cur.tokens, 0, sizeof(char *));
	vec_new(&data->cur.types, 0, sizeof(int));
	vec_new(&data->cur.token_buffer, 0, sizeof(char));
}

// Tokenize input
// stores the last token once the input string ends
int	tokenize_input(t_data *data)
{
	int	idx;
	int	mode;

	idx = 0;
	mode = DEFAULT_MODE;
	create_vectors(data);
	while (data->cur.raw[idx] != '\0')
	{
		evaluate_char(data->cur.raw[idx], &mode, &idx, data);
		if (mode > 10)
			handle_expansion_mode(&mode, &idx, data);
		idx++;
	}
	store_token(data);
	if (data->cur.tokens.len == 0)
	{
		data->cur.err_flag = 1;
		return (1);
	}
	return (0);
}
