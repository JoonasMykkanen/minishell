/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 15:07:37 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"
#include "tokenizer.h"

int	is_greater_than(char c)
{
	return (c == '>');
}

int	is_smaller_than(char c)
{
	return (c == '<');
}

int	is_double_greater_than(char c, char next_c)
{
	return (c == '>' && next_c == '>');
}
