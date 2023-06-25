/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:51:42 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:24:11 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

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
