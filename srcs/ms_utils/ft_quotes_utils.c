#include "../includes/minishell.h"

void	ft_delete_quotes(char comm, char ***tmp, int *j, char c)
{
	if (comm != c)
	{
		(*tmp)[0][*j] = comm;
		(*j)++;
	}
}

void	if_in_quote(int *d, int *s, char *str, t_all *all)
{
	int i;

	i = 0;
	*s = 0;
	*d = 0;
	while (str[i])
	{
		if (str[i] == '$')
			all->env = 1;
		else if (str[i] == '\"')
			while (str[i] && str[i + 1] && str[++i] != '\"')
				(*d)++;
		else if (str[i] == '\'')
			while (str[i] && str[i + 1] && str[++i] != '\'')
				(*s)++;
		i++;
	}
}

int	ft_check_special_case(char **comm, char ***new, int *j, int *i, t_all *all)
{
	if (comm[0][*i] == '#')
	{
		(*new)[0][*j] = '\0';
		return (0);
	}
	ft_err_nb(comm[0], new, j, i, all);
	return (1);
}

void	ft_err_nb(char *comm, char ***new, int *j, int *i, t_all *all)
{
	char *nb;

	while (comm[*i] == '?' || comm[*i] == '{' || comm[*i] == '$' || comm[*i] == '}')
	{
		if (comm[*i] == '?')
		{
			nb = ft_itoa(all->err);
			if (nb)
				(*new)[0] = ft_strjoin_free((*new)[0], nb, 1);
		}
		(*j)++;
		(*i)++;
	}
}