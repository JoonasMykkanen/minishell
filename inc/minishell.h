/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:55 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/25 15:29:15 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_types.h"
# include "builtins.h"
# include "clean_exit.h"
# include "command.h"
# include "error_checking.h"
# include "execute.h"
# include "init.h"
# include "input.h"
# include "signal_manager.h"
# include "termios.h"
# include "tokenizer.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

#endif