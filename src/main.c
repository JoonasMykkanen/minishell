/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/25 15:38:03 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int		sig_status;

static void	execute_loop(char *input, t_data *data)
{
	if (input && *input)
		add_history(input);
	handle_input(input, data);
	if (data->cur.err_flag == 0 || sig_status != SIG_ERROR)
		tokenize_input(data);
	if (data->cur.err_flag == 0 || sig_status != SIG_ERROR)
		parse_commands(data);
	if (data->cur.err_flag == 0 || sig_status != SIG_ERROR)
		execute(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	if (argc != 1 && argv[1] != NULL)
		return (1);

	signal_manager();
	termios_settings();
	if (init_struct(envp, &data) == 1)
		perror("init_struct");
	while (42)
	{
		input = readline(data.env.prompt);
		if (ft_strlen(input) != 0)
		{
			execute_loop(input, &data);
			clean_cur_struct(&data);
		}
		else if (input == NULL)
		{
			handle_ctrl_d(&data);
		}
	}
	clean_exit_shell(&data);
	return (data.env.exit_status);
}
