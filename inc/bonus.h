/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:17:14 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 16:00:08 by jmykkane         ###   ########.fr       */
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
void	handle_history(t_vec *buf);

#endif // !BONUS_H
