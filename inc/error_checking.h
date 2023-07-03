/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:46:09 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/25 12:07:11 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CHECKING_H
# define ERROR_CHECKING_H

# include <errno.h>

void	malloc_error_check(char *string, t_data *data);
void	string_array_malloc_error_check(char **string, t_data *data);

#endif