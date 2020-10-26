/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:08:31 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/26 12:46:08 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_errors_line(char *line, t_all *all)
{
	if (!check_double(line, ";|"))
		return (ft_syntax_error(line, "double", all));
	else if (!ft_error_ps(line))
		return (ft_syntax_error(line, "ps", all));
	else if (!ft_quote_error(line))
		return (ft_syntax_error(line, "quote", all));
	else if (!check_chevrons(line))
		return (ft_syntax_error(line, "chevrons", all));
	return (1);
}
