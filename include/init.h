/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:20:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/10 13:48:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "../src/libft/libft.h"
# include <fcntl.h>

void	reset_cur(void);
char	**get_paths(void);
void	set_builtins(void);
void	free_arr(char **arr);
void	clean_cur_struct(void);
void	termios_settings(void);
int		init_struct(char **envp);
char	*find_env_var(char *str);
char	**get_env_vars(char **envp);

#endif