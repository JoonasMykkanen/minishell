/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:17:14 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/02 17:51:11 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# define MAX_LINE 96

# define ESCAPE_SEQUENCE '\033'
# define ARROW_UP 65
# define ARROW_DOWN 66

# define ERASE "\b \b"
# define CTRL_D 4
# define BACKSPACE 0x7F
# define PRINTABLE 1
# define START 0

# include <readline/history.h>
# include <readline/readline.h> 
# include <ctype.h>
# include <signal.h>
# include "../src/libft/libft.h"
# include "ft_types.h"

char	*ft_readline(char *prompt);
void	handle_history(char c, t_vec *buf, char *prompt);

#endif // !BONUS_H
