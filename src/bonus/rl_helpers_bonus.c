/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_helpers_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 12:42:23 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/06 09:22:41 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	refresh_output(t_vec *buf, const char *line)
{
	while (buf->len > 0)
	{
		printf(ERASE);
		vec_pop(NULL, buf);
	}
	fflush(stdout);
	while (*line)
	{
		printf("%c", *line);
		vec_push(buf, (void*)line);
		line++;
	}
	fflush(stdout);
}
