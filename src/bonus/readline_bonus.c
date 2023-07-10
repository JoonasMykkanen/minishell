/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:01:56 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/10 12:58:39 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_manager.h"
#include "bonus.h"

extern int	g_sig_status;

static int	custom_backspace(char c, t_vec *buf, size_t *cursor_idx)
{
	if (c != BACKSPACE)
		return (0);
	if (buf->len > 0 && *cursor_idx >= 0)
	{
		*cursor_idx -= 1;
		vec_remove(buf, *cursor_idx);
		refresh_prompt(buf, cursor_idx);
		update_cursor(BACKSPACE);
	}
	else
		update_cursor(PRINTABLE);
	return (1);
}

static void	handle_output(t_vec *buf, char c, size_t *cursor_idx)
{
	int	key;

	if (ft_isprint(c) == PRINTABLE)
	{
		*cursor_idx += 1;
		vec_push(buf, &c);
		printf("%c", c);
		update_cursor(PRINTABLE);
	}
	else if (c == ESCAPE_SEQUENCE)
	{
		getchar();
		key = getchar();
		if (key == ARROW_UP || key == ARROW_DOWN)
			handle_history(buf, key, cursor_idx);
		else if (key == ARROW_LEFT || key == ARROW_RIGHT)
			handle_cursor(buf, key, cursor_idx);
	}
}

static void	init(t_vec *buf, char *prompt)
{
	printf(DISABLE_CURSOR);
	printf("%s", prompt);
	printf(INPUT_EMOJI);
	vec_new(buf, 0, sizeof(char));
}

char	*ft_readline(char *prompt)
{
	static size_t	cursor_idx = 0;
	char			*line;
	t_vec			buf;
	char			c;

	init(&buf, prompt);
	while (buf.len < MAX_LINE_LEN)
	{
		c = getchar();
		if (refresh_input(c, &buf) < 0)
			break ;
		if (custom_backspace(c, &buf, &cursor_idx) == 1)
			continue ;
		handle_output(&buf, c, &cursor_idx);
	}
	vec_push(&buf, "\0");
	if (buf.len > 1 || c == '\n')
		line = ft_strdup((char *)vec_get(&buf, START));
	else
		line = NULL;
	vec_free(&buf);
	printf("\n");
	cursor_idx = 0;
	return (line);
}
