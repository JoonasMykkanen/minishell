/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:17:14 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/05 21:01:09 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

// Moving cursor left and right
# define RIGHT "\033[1C"
# define LEFT "\033[1D"
# define MOVE_RIGHT 1
# define MOVE_LEFT 2

// detecting arrow key presses and identifying if up or down
# define ESCAPE_SEQUENCE '\033'
# define ARROW_UP 65
# define ARROW_DOWN 66
# define ARROW_LEFT 68
# define ARROW_RIGHT 67

// erase printed character
# define ERASE "\b \b"

# define MAX_LINE_LEN 100
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

char	*ft_readline(char *prompt);
void	refresh_output(t_vec *buf, const char *line);
void	refresh_prompt(t_vec *buf, size_t *cursor_idx);
void    handle_history(t_vec *buf, int key, size_t *cursor_idx);

#endif // !BONUS_H
