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

void	ft_check_sep_cdt(char **comm, int *i, int *s, int *d)
{
	if ((*comm)[*i] == '\'' && ft_check_bs(*comm, *i - 1))
		(*s)++;
	else if ((*comm)[*i] == '\"' && ft_check_bs(*comm, *i - 1))
		(*d)++;
}

void	ft_check_sep(char **comm)
{
	int		i;
	int		s;
	int		d;
	char	*new;
	int		j;

	ft_init_check_sep(&i, &j, &d, &s);
	if ((new = ft_calloc(ft_strlen(*comm) + 1, sizeof(char))) == NULL)
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
		(*comm) = ft_strdup(new);
		ft_free((void **)&new);
	}
}
