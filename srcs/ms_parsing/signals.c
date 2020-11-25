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
	char *tmp;
	int		x;

	(void)sigld;
	x = 1;
	ft_putendl_fd("", 1);
	all.err = 1; //tester le code d'erreur sur linux sur la vm
	while (x != 0)
	{
		ft_putstr_fd("~:", 1);
		tmp = ft_read(&all);
		if (tmp == NULL)
			x = 0;
	}
	signal(SIGINT, c_handler);
	free_all(&all);
	byebye();
	exit(EXIT_SUCCESS);
}