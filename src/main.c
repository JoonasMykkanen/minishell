/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/11 19:08:01 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig_status;

static void	execute_loop(char *input, t_data *data)
{
	if (ft_strlen(input) != 0)
	{
		if ((input && *input) && g_sig_status != SIG_ERROR)
			add_history(input);
		if (g_sig_status != SIG_ERROR)
			handle_input(input, data);
		if (data->cur.err_flag == 0 && g_sig_status != SIG_ERROR)
			tokenize_input(data);
		if (data->cur.err_flag == 0 && g_sig_status != SIG_ERROR)
			parse_commands(data);
		if (data->cur.err_flag == 0 && g_sig_status != SIG_ERROR)
			execute(data);
	}
	else if (input == NULL)
		handle_ctrl_d(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	if (argc != 1 && argv[1] != NULL)
		return (1);
	if (init_struct(envp, &data) == 1)
		perror("init_struct");
	termios_settings(YES);
	signal_manager();
	while (42)
	{
		input = readline(data.env.prompt);
		execute_loop(input, &data);
		clean_cur_struct(&data);
		update_prompt(&data);
	}
	clean_exit_shell(&data, PARENT);
	return (data.env.exit_status);
}
