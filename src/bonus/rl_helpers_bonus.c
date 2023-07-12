/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_helpers_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 12:42:23 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/12 08:52:02 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_manager.h"
#include "bonus.h"

extern int	g_sig_status;

void	handle_cursor(t_vec *buf, int key, size_t *cursor_idx)
{
	if (key == ARROW_LEFT && *cursor_idx > 0)
	{
		*cursor_idx -= 1;
		printf(LEFT);
	}
	if (key == ARROW_RIGHT && *cursor_idx < buf->len)
	{
		*cursor_idx += 1;
		printf(RIGHT);
	}
}

int	refresh_input(char c, t_vec *buf)
{
	if (c == '\n')
	{
		printf(RIGHT);
		printf(ERASE);
		return (-1);
	}
	if (c != CTRL_D)
		return (0);
	if (buf->len == 0 || g_sig_status == SIG_HEREDOC)
	{
		while (buf->len > 0)
		{
			printf(ERASE);
			vec_pop(NULL, buf);
		}
		return (-1);
	}
	return (0);
}

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
		vec_push(buf, (void *)line);
		line++;
	}
	fflush(stdout);
}
