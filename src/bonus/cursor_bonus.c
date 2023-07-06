/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:22:00 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/06 12:49:56 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void reset_cursor_position(size_t *idx, size_t len)
{
	while (*idx < len && len > 0)
	{
		printf(RIGHT);
		*idx += 1;
	}
}

static void	erase_old_prompt(size_t *idx, size_t len)
{
	*idx += 1;

	while (*idx > 0 && len >= 0)
	{
		printf(ERASE);
		*idx -= 1;
	}
}

static void	print_new_prompt(size_t *idx, t_vec *buf)
{
	while (*idx < buf->len && buf->len > 0)
	{
		printf("%c", *(char *)vec_get(buf, *idx));
		*idx += 1;
	}
}

static void restore_cursor_position(size_t *cursor, size_t og)
{
	while (*cursor > og)
	{
		printf(LEFT);
		*cursor -= 1;
	}
}

void	refresh_prompt(t_vec *buf, size_t *cursor_idx)
{
	size_t	original_pos;

	original_pos = *cursor_idx;
	reset_cursor_position(cursor_idx, buf->len);
	erase_old_prompt(cursor_idx, buf->len);
	print_new_prompt(cursor_idx, buf);
	restore_cursor_position(cursor_idx, original_pos);
}
