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
	all.err = 1; //tester sur le bash de la vm
	ft_putendl_fd("", 1);
	ft_putstr_fd("~:", 1);
}

void	c_prgm(int sigld)
{
	(void)sigld;
	kill(0, SIGINT);
}