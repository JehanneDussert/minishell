/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehannedussert <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:06:21 by jehannedu         #+#    #+#             */
/*   Updated: 2020/12/29 17:06:30 by jehannedu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	c_handler(int sigld)
{
	(void)sigld;
	g_all.err = 130;
	if (g_all.prog == 0)
	{
		ft_putendl_fd("", 1);
		ft_putstr_fd("~:", 1);
	}
}

void	d_handler(int sigld)
{
	(void)sigld;
	if (g_all.prog == 1)
	{
		g_all.err = 131;
		kill(g_pid, SIGQUIT);
		ft_putendl_fd("Quit (core dumped)", 1);
	}
	else
		ft_putstr_fd("\b \b\b \b", 1);
}
