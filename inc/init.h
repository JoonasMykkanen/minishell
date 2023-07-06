/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:20:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/05 11:39:15 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "../src/libft/inc/libft.h"
# include "ft_types.h"
# include <fcntl.h>

void	free_arr(char **arr);
char	**get_paths(t_data *data);
void	set_builtins(t_data *data);
void	clean_cur_struct(t_data *data);
int		init_struct(char **envp, t_data *data);
char	*find_env_var(char *str, t_data *data);
char	**get_env_vars(char **envp, t_data *data);

#endif