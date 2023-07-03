/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:01:56 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 16:07:46 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_manager.h"
#include "bonus.h"

extern int	g_sig_status;

static void	custom_backspace(t_vec *buf)
{
	if (buf->len > 0)
	{
		printf(ERASE);
		fflush(stdout);
		vec_pop(NULL, buf);
	}
}

static void	handle_output(t_vec *buf, char c)
{
	if (ft_isprint(c) == PRINTABLE)
	{
		vec_push(buf, &c);
		printf("%c", c);
	}
	else if (c == ESCAPE_SEQUENCE)
	{
		handle_history(buf);
	}
}

static void	init(t_vec *buf, char *prompt)
{
	printf("%s", prompt);
	vec_new(buf, 0, sizeof(char));
}

char	*ft_readline(char *prompt)
{
	char	*line;
	t_vec	buf;
	char	c;

	init(&buf, prompt);
	while (buf.len < MAX_LINE)
	{
		c = getchar();
		if (c == '\n')
			break ;
		else if (c == CTRL_D)
		{
			if (buf.len == 0 || g_sig_status == SIG_HEREDOC)
			{
				while (buf.len > 0)
				{
					printf(ERASE);
					vec_pop(NULL, &buf);
				}
				break ;
			}
		}
		else if (c == BACKSPACE)
		{
			custom_backspace(&buf);
			continue ;
		}
		handle_output(&buf, c);
	}
	vec_push(&buf, "\0");
	if (buf.len > 1 || c == '\n')
		line = ft_strdup((char *)vec_get(&buf, START));
	else
		line = NULL;
	vec_free(&buf);
	printf("\n");
	return (line);
}
