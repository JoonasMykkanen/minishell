/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:19:02 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/10 12:52:46 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void	handle_up(int *index, t_vec *buf)
{
	HIST_ENTRY	*entry;

	if (*index < history_length - 1)
	{
		*index += 1;
		entry = history_get(history_base + history_length - 1 - *index);
		if (entry)
		{
			refresh_output(buf, entry->line);
			fflush(stdout);
		}
	}
}

static void	handle_down(int *index, t_vec *buf)
{
	HIST_ENTRY	*entry;

	if (*index >= 0)
	{
		*index -= 1;
		if (*index == -1)
		{
			refresh_output(buf, "");
			fflush(stdout);
		}
		else
		{
			entry = history_get(history_base + history_length - 1 - *index);
			if (entry)
			{
				refresh_output(buf, entry->line);
				fflush(stdout);
			}
		}
	}
}

void	handle_history(t_vec *buf, int key, size_t *cursor_idx)
{
	static int	index = -1;

	if (key == ARROW_UP)
	{
		handle_up(&index, buf);
		*cursor_idx = buf->len;
	}
	else if (key == ARROW_DOWN)
	{
		handle_down(&index, buf);
		*cursor_idx = buf->len;
	}
}
