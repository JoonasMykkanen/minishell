/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:51:42 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 15:07:54 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "command.h"
#include "minishell.h"

// Checks if character triggers expansion
int	is_trigger_char(char c, int *mode)
{
	if (*mode == DEFAULT_MODE || *mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '$')
		{
			*mode += 10;
			return (true);
		}
	}
	return (false);
}
