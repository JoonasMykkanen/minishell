/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:22:00 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/10 12:59:14 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	update_cursor(int mode)
{
	if (mode == BACKSPACE)
	{
		printf(TRACTOR_EMOJI);
		fflush(stdout);
	}
	if (mode == PRINTABLE)
	{
		printf(INPUT_EMOJI);
		fflush(stdout);
	}
}

static void	remove_old_prompt(size_t *idx, size_t len)
{
	while (*idx <= len && len >= 0)
	{
		printf(RIGHT);
		*idx += 1;
	}
	*idx += 1;
	while (*idx > 0 && len >= 0)
	{
		printf(ERASE);
		*idx -= 1;
	}
	fflush(stdout);
}

static void	print_new_prompt(size_t *cursor, t_vec *buf, size_t origina_pos)
{
	while (*cursor < buf->len && buf->len > 0)
	{
		printf("%c", *(char *)vec_get(buf, *cursor));
		*cursor += 1;
	}
	while (*cursor > origina_pos)
	{
		printf(LEFT);
		*cursor -= 1;
	}
	fflush(stdout);
}

void	refresh_prompt(t_vec *buf, size_t *cursor_idx)
{
	size_t	original_pos;

	original_pos = *cursor_idx;
	remove_old_prompt(cursor_idx, buf->len);
	print_new_prompt(cursor_idx, buf, original_pos);
}
