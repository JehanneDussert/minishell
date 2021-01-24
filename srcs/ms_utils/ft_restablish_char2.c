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

int		ft_len_without_quotes(char *comm)
{
	int	d;
	int	s;
	int	len;

	s = 0;
	d = 0;
	len = 0;
	while (comm[len] != '\'' && comm[len] != '\"')
		len++;
	if_in_quote(&d, &s, comm);
	if (d > s)
		len += d;
	else
		len += s;
	return (len);
}

void	ft_check_sep(char **comm)
{
	int		i;
	int		s;
	int		d;
	char	*new;
	int		j;

	ft_init_check_sep(&i, &j, &d, &s);
	if ((new = ft_calloc(ft_len_without_quotes(*comm) + 1, sizeof(char))) == NULL)
		return ;
	while ((*comm)[i])
	{
		if ((s % 2 || d % 2) && is_charset((*comm)[i], ";|><"))
			ft_s_char(comm, &new, &i, &j);
		else
		{
			ft_check_sep_cdt(comm, &i, &s, &d);
			new[j++] = (*comm)[i++];
		}
	}
	free_read(NULL, comm);
	if (new)
	{
		(*comm) = (new);
		//ft_free((void **)&new);
	}
}
