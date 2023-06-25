/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:20:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:09:01 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "../src/libft/libft.h"
# include "types.h"
# include <fcntl.h>

void	free_arr(char **arr);
void	termios_settings(void);
void	reset_cur(t_data *data);
char	**get_paths(t_data *data);
void	set_builtins(t_data *data);
void	clean_cur_struct(t_data *data);
int		init_struct(char **envp, t_data *data);
char	*find_env_var(char *str, t_data *data);
char	**get_env_vars(char **envp, t_data *data);

#endif