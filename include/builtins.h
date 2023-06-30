/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:27:09 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/30 12:25:16 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define EXPORT 1
# define SHELL 2

# include "minishell.h"
# include <signal.h>
# include <dirent.h>

// Builtin functions
int		ft_unset(int cmd_idx, int caller, t_data *data);
int		ft_export(int cmd_idx, t_data *data);
int		ft_echo(int cmd_index, t_data *data);
void	ft_exit(t_data *data);
int		ft_env(t_data *data);
int		ft_pwd(t_data *data);
int		ft_cd(t_data *data);

// Helpers for builtins
int		ft_isnum(int c);
int		arr_len(t_data *data);
int		ft_isvalid_int(char *str);
void	free_env_vars(t_data *data);
int		get_env_var_count(t_data *data);
int		is_env_var(char *arg, t_data *data);
int     handle_no_args(t_data *data, int cmd_idx);
char	*extract_until_equal(char *arg, t_data *data);

#endif