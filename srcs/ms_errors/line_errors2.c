/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:08:31 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/22 17:09:04 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_errors_line(char *line)
{
	if (!check_double(line, ";|"))
		return(ft_syntax_error(line, "double"));
	else if (!ft_error_ps(line))
		return(ft_syntax_error(line, "ps"));
	else if (!ft_quote_error(line))
		return(ft_syntax_error(line, "quote"));
	else if (!check_chevrons(line)) // segfault here
		return(ft_syntax_error(line, "chevrons"));
	return(1);
}
