/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:46:59 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/21 18:32:56 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "minishell.h"

# define NO_CHILDS -1
# define WRITE_END 1
# define READ_END 0
# define STDERR 2

# define TRUE 1
# define FALSE 0

# define CHILD 0
# define PARENT 1

typedef struct s_pipex_data
{
	int			pipes[1000][2];
	int			out_redirected;
	int			fdout;
	int			fdin;
	int			idx;
	pid_t		pid;
}				t_pipes;

void	execute(t_data *data);
void	execute_fail(int idx, t_data *data);
void	redir_out(t_pipes *p, t_data *data);
void	redir_input(t_pipes *p, t_data *data);
int		what_builtin(char *cmd, t_data *data);
void	handle_child(t_pipes *p, t_data *data);
void	handle_parent(t_pipes *p, t_data *data);
void	execute_builtin(t_pipes *p, t_data *data);
char	*get_command_path(char *token, t_data *data);
void	execute_cmd(t_pipes *p, int idx, t_data *data);
void	handle_input_redirection_for_execution(t_pipes *p, t_data *data);
void	handle_output_redirection_for_execution(t_pipes *p, t_data *data);

#endif
