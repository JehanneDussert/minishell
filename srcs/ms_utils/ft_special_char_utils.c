#include "../includes/minishell.h"

void	ft_replace(char **comm, char **new, int *i, int *j)
{
	if ((*comm)[*i] && (*comm)[*i] == 1)
		(*new)[*j] = ' ';
	else if ((*comm)[*i] && (*comm)[*i] == 2)
		(*new)[*j] = '<';
	else if ((*comm)[*i] && (*comm)[*i] == 3)
		(*new)[*j] = '>';
	else if ((*comm)[*i] && (*comm)[*i] == 4)
		(*new)[*j] = ';';
	else if ((*comm)[*i] && (*comm)[*i] == 5)
		(*new)[*j] = '|';
	(*j)++;
	(*i)++;
}

int		ft_len(char **comm)
{
	int	len;

	len = 0;
	while (comm[len])
		len++;
	return (len);
}
