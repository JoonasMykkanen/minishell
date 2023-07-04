/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:02:11 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 17:44:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"

int	is_builtin(char *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(data->dir.builtins[i], cmd, 10) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	get_cmd_count(t_data *data)
{
	int		i;
	int		count;
	char	skip_char;

	i = 0;
	count = 1;
	while (data->cur.raw[i] != '\0')
	{
		if (data->cur.raw[i] == '|')
		{
			count++;
		}
		if (data->cur.raw[i] == '\"' || data->cur.raw[i] == '\'')
		{
			skip_char = data->cur.raw[i];
			i++;
			while (data->cur.raw[i] != skip_char && data->cur.raw[i] != '\0')
				i++;
		}
		i++;
	}
	data->cur.cmd_count = count;
	return (0);
}

int	allocate_cmd_list(t_data *data)
{
	unsigned long	size;
	int				i;

	i = 0;
	size = sizeof(t_cmd *);
	data->cur.cmd_list = (t_cmd **)malloc(data->cur.cmd_count * size);
	if (!data->cur.cmd_list)
	{
		perror("Error allocating command lists, will exit");
		clean_exit_shell(data, PARENT);
		exit(errno);
	}
	while (i < data->cur.cmd_count)
	{
		if (parser_allocate(i, data) != 0)
			exit(errno);
		i++;
	}
	return (0);
}

int	is_delim(int i, t_data *data)
{
	t_token	*t;

	t = get_token(i, data);
	if (t->type == DEFAULT)
	{
		if (ft_strncmp("|", t->token, ft_strlen(t->token)) == 0)
		{
			free(t);
			return (1);
		}
	}
	free(t);
	return (0);
}

int	check_mode(char *token, int type, int cmd_idx, t_data *data)
{
	if (type == DEFAULT)
	{
		if (ft_strncmp("<", token, ft_strlen(token)) == 0)
		{
			return (INPUT_REDIR);
		}
		if (ft_strncmp(">", token, ft_strlen(token)) == 0)
		{
			data->cur.cmd_list[cmd_idx]->output_mode = OVERWRITE_MODE;
			return (OUTPUT_REDIR_OVERWRITE);
		}
		if (ft_strncmp(">>", token, ft_strlen(token)) == 0)
		{
			data->cur.cmd_list[cmd_idx]->output_mode = APPEND_MODE;
			return (OUTPUT_REDIR_APPEND);
		}
	}
	return (DEFAULT_MODE);
}
