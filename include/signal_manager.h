/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:08:06 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:10:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER_H
# define SIGNAL_MANAGER_H

# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include "types.h"

# define SIG_ERROR 2
# define SIG_DEFAULT 42
# define INT_HEREDOC 43
# define INT_NO_CHILD 44
# define INT_HAS_CHILD 45

void	signal_manager(void);
void	handle_ctrl_d(t_data *data);

#endif