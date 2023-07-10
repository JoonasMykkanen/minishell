/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:17:14 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/10 13:00:29 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# define MAX_LINE_LEN 100

// Used to manipulate cursor
# define TRACTOR_EMOJI "\U0001F69C\033[1D\033[1D"
# define INPUT_EMOJI "\U0001F448\033[1D\033[1D"
# define ENABLE_CURSOR "\033[?25h"
# define DISABLE_CURSOR "\033[?25l"
# define RIGHT "\033[1C"
# define LEFT "\033[1D"
# define ERASE "\b \b"

# define PROMPT_AT "\U0001F300"

// detecting arrow key presses and identifying if up or down
# define ESCAPE_SEQUENCE '\033'
# define ARROW_RIGHT 67
# define ARROW_LEFT 68
# define ARROW_DOWN 66
# define ARROW_UP 65

// miscellaneous
# define BACKSPACE 0x7F
# define PRINTABLE 1
# define CTRL_D 4
# define START 0
# define YES 1
# define NO 0

# include "../src/libft/inc/libft.h"
# include <readline/readline.h> 
# include <readline/history.h>
# include "ft_types.h"
# include <signal.h>
# include <ctype.h>

void	update_cursor(int mode);
char	*ft_readline(char *prompt);
int		refresh_input(char c, t_vec *buf);
void	refresh_output(t_vec *buf, const char *line);
void	refresh_prompt(t_vec *buf, size_t *cursor_idx);
void	handle_cursor(t_vec *buf, int key, size_t *cursor_idx);
void	handle_history(t_vec *buf, int key, size_t *cursor_idx);

#endif // !BONUS_H
