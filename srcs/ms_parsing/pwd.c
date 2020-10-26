/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:18:43 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/26 11:28:53 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_id(t_all *all)
{
	char	*buf;
	int		catch;

	catch = 0;
	if (!(buf = ft_calloc(sizeof(buf), 1024)))
	{
		ft_malloc_error("pwd");
		all->err = 1;
		return ;
	}
	if (!(getcwd(buf, 1024)))
	{
		error_msg("pwd", strerror(errno));
		errno = 0;
		all->err = 1;
		catch = 1;
	}
	ft_putendl_fd(buf, 1);
	ft_free((void **)&buf);
	if (catch == 0)
		all->err = 0;
}