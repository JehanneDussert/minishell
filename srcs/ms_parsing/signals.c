/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:16:55 by marvin            #+#    #+#             */
/*   Updated: 2020/11/25 14:16:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	c_handler(int sigld)
{
	(void)sigld;
	all.err = 130;
	if (all.prog == 0)
	{
		ft_putendl_fd("", 1);
		ft_putstr_fd("~:", 1);
	}
}

void	d_handler(int sigld)
{
	(void)sigld;
	ft_putendl_fd("xd", 1);
	if (all.prog == 1)
	{
		all.err = 131;
		kill(0, SIGQUIT);
		ft_putendl_fd("Quit (core dumped)", 1);
		exit(0);
	}
}