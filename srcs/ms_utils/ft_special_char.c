#include "../includes/minishell.h"

void	ft_nb_backslash(char *comd)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (comd[i])
	{
		if (is_charset(comd[i], "\\"))
		{
			nb++;
			if (i > 0 && comd[i - 1] == '\\' && nb % 2 == 0)
				g_all.bs++;
		}
		i++;
	}
}

void	ft_check_hash(char ***commands)
{
	int	i;

	i = 0;
	while ((*commands)[0][i])
	{
		if ((*commands)[0][0] == '#' ||
			(i > 0 && (*commands)[0][i - 1] == ' ' && (*commands)[0][i] == '#'))
		{
			(*commands)[0] = ft_return_new_comd(commands[0],
			&(*commands)[0][i]);
			if ((*commands)[1])
				free_read(NULL, &(*commands)[1]);
			return ;
		}
		if ((*commands)[0][i] == '\\')
			((*commands)[0] = ft_return_new_comd(&(*commands)[0], "\\"));
		i++;
	}
}

int		ft_hash(char **comd, char ***tmp, char *charset, int *i, int *j)
{
	if (charset[0] == '#' && comd[0][*i] == ' ' && comd[0][(*i) + 1] == '#')
		return (0);
	(*tmp)[0][*j] = comd[0][*i];
	(*j)++;
	(*i)++;
	return (1);
}

void	ft_backslash(char **comd, char ***tmp, int *i, int *j)
{
	if (g_all.bs == 0)
		while (comd[0][*i])
		{
			if (comd[0][*i] != '\\')
			{
				(*tmp)[0][*j] = comd[0][*i];
				(*j)++;
			}
			(*i)++;
		}
	else if (comd[0][*i + 1])
		while (comd[0][++(*i)])
		{
			(*tmp)[0][*j] = comd[0][*i];
			(*j)++;
		}
}
