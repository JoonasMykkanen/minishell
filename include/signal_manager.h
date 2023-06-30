/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:08:06 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/30 09:51:44 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER_H
# define SIGNAL_MANAGER_H

# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include "types.h"

# define CHILDS 0

# define SIG_ERROR 2
# define SIG_HEREDOC 43
# define SIG_NO_CHILD 44
# define SIG_HAS_CHILD 45

void	signal_manager(void);
void	termios_settings(void);
void	handle_ctrl_d(t_data *data);

#endif