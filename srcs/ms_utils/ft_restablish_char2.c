#include "../includes/minishell.h"

int		ft_check_bs(char *comm, int i)
{
	int bs;

	bs = 0;
	while (comm[i] && comm[i] == '\\' && i > 0)
	{
		bs++;
		i--;
	}
	if (bs % 2)
		return (0);
	return (1);
}

void	ft_s_char(char **comm, char **new, int *i, int *j)
{
	while (is_charset(comm[0][*i], "><;|"))
	{
		if (is_charset(comm[0][*i], "<"))
			new[0][*j] = 2;
		else if (is_charset(comm[0][*i], ">"))
			new[0][*j] = 3;
		else if (is_charset(comm[0][*i], ";"))
			new[0][*j] = 4;
		else if (is_charset(comm[0][*i], "|"))
			new[0][*j] = 5;
		else if (is_charset(comm[0][*i], "\'\""))
			return ;
		(*j)++;
		(*i)++;
	}
}

void	ft_init_check_sep(int *i, int *j, int *d, int *s)
{
	*i = 0;
	*j = 0;
	*s = 0;
	*d = 0;
}

void	ft_check_sep_cdt(char **comm, int *i, int *s, int *d)
{
	if ((*comm)[*i] == '\'' && ft_check_bs(*comm, *i - 1))
		(*s)++;
	else if ((*comm)[*i] == '\"' && ft_check_bs(*comm, *i - 1))
		(*d)++;
}

char	*ft_sep(char **comm)
{
	int		i;
	int		s;
	int		d;
	char	*new;
	int		j;

	ft_init_check_sep(&i, &j, &d, &s);
	if ((new = ft_calloc(ft_strlen(*comm) + 1, sizeof(char))) == NULL)
		return (NULL);
	while ((comm)[0][i])
	{
		if ((s % 2 || d % 2) && is_charset((*comm)[i], ";|><"))
			ft_s_char(comm, &new, &i, &j);
		else
		{
			ft_check_sep_cdt(comm, &i, &s, &d);
			new[j++] = (*comm)[i++];
		}
	}
	if (comm[0] && new)
	{
		free(comm[0]);
		printf("ici ca va pas :\n");
		printf("%p\n", new);
		comm[0] = ft_strdup(new);
		ft_free((void **)&new);
	}
	return (comm[0]);
}

int		ft_check_sep(char **comm)
{
	int	i;

	i = -1;
	while (comm[0][++i])
	{
		if (!is_charset(comm[0][i], "\'\""))
			continue ;
		while (comm[0][i] && !is_charset(comm[0][i], ";|><"))
			i++;
		if (comm[0][i] && !(comm[0] = ft_sep(comm)))
			return (0);
		else
			return (1);
	}
	return (1);
}
