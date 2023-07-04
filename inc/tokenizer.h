/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:25:58 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 22:06:37 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../src/libft/libft.h"
# include "ft_types.h"

# define YES 1
# define NO 0

# define DEFAULT 0
# define WITHIN_QUOTES 1
# define DEFAULT_MODE 1
# define DOUBLE_QUOTES_MODE 2
# define SINGLE_QUOTES_MODE 3
# define HEREDOC_MODE 4
# define EXPANSION_MODE_DEFAULT 11
# define EXPANSION_MODE_DOUBLE_Q 12

// Expansion mode
void	handle_expansion_mode(int *mode, int *i, t_data *data);
int		is_exit_status_expansion(int j, t_data *data);
int		is_valid_subsequent_character(char c);
int		is_valid_first_character(char c);
char	*fetch_env_var(char *str, t_data *data);

// Edge cases
int		is_edge_case(char *ptr, int *mode, int *i, t_data *data);
int		handle_within_quotes(char c, char next_c, int *i, t_data *data);
int		handle_default_mode(char c, char next_c, int *i, t_data *data);
int		is_double_greater_than(char c, char next_c);
int		is_smaller_than(char c);
int		is_greater_than(char c);

// Buffer handling
void	clear_and_init_buffer(t_data *data);
void	add_char_to_buffer(char c, t_data *data);
void	handle_double_greater_than(int *i, t_data *data);

// Store token
void	add_double_greater_than_within_quotes(int *i, t_data *data);
void	store_current_token_within_quotes(t_data *data);
void	add_char_within_quotes(char c, t_data *data);
void	store_token_within_quotes(t_data *data);
void	store_current_token(t_data *data);
void	store_empty_token(t_data *data);
void	store_token(t_data *data);

// Char evaluation
int		evaluate_char(char c, int *mode, int *i, t_data *data);
int		is_mode_changing_char(char c, int *mode, t_data *data);
int		is_trigger_char(char c, int	*mode);
int		is_stored_char(char c, int *mode);

int		is_terminating_char(char c, int *mode);
int		needs_blanc(char c, int *mode);
int		tokenize_input(t_data *data);

#endif