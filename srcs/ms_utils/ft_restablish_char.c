#include "../includes/minishell.h"

void    ft_replace(char *comm, char **new, int *i, int *j)
{
    if (comm[*i] && comm[*i] == 1)
		new[0][*j] = ' ';
	else if (comm[*i] && comm[*i] == 2)
		new[0][*j] = '<';
	else if (comm[*i] && comm[*i] == 3)
		new[0][*j] = '>';
	else if (comm[*i] && comm[*i] == 4)
		new[0][*j] = ';';
	else if (comm[*i] && comm[*i] == 5)
		new[0][*j] = '|';
    (*j)++;
    (*i)++;
}

void    ft_restablish_char(char ***comm)
{
    int     i;
    int     j;
    char    *new;

    i = 0;
    j = 0 ;
    if ((new = ft_calloc(ft_strlen((*comm)[0]) + 1, sizeof(char))) == NULL)
        return ;
    while ((*comm)[0][i])
    {
        if ((*comm)[0][i] == 4 || (*comm)[0][i] == 5)
            ft_replace((*comm)[0], &new, &i, &j);
        else
        {
            new[j] = (*comm)[0][i];
            i++;
            j++;
        }
    }
    free_read(NULL, *comm);
	if (new)
	{
		(*comm)[0] = ft_strdup(new);
		ft_free((void **)&new);
	}
}

void    ft_restablish_redir(char ***comm, t_all *all)
{
    int     i;
    int     j;
    char    *new;

    i = 0;
    j = 0 ;
    if ((new = ft_calloc(all->cmd_len + 1, sizeof(char))) == NULL)
        return ;
    while ((*comm)[0][i])
    {
        if ((*comm)[0][i] == 1 || (*comm)[0][i] == 2 ||
            (*comm)[0][i] == 3)
            ft_replace((*comm)[0], &new, &i, &j);
        else
        {
            new[j] = (*comm)[0][i];
            i++;
            j++;
        }
    }
    free_read(NULL, *comm);
	if (new)
	{
		(*comm)[0] = ft_strdup(new);
		ft_free((void **)&new);
	}
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

void	ft_check_sep(char **comm)
{
    int		i;
    int		q;
    char	*new;
    int		j;

    i = 0;
    j = 0;
    q = 0;
	if ((new = ft_calloc(ft_strlen(*comm) + 1, sizeof(char))) == NULL)
		return ;
	while ((*comm)[i])
	{
		if ((*comm)[i] == '\'' || (*comm)[i] == '\"')
			q++;
		if ((*comm)[i] && ((*comm)[i] == '\'' || (*comm)[i] == '\"') && !(q % 2))
		{
			while ((*comm)[i] && !is_charset((*comm)[i], "><;|"))
			{
				new[j] = (*comm)[i];
            	i++;
            	j++;
			}
			ft_s_char(comm, &new, &i, &j);
		}
		if ((*comm)[i] && !is_charset(comm[0][i], "><;|\'\""))
        {
            new[j] = (*comm)[i];
            i++;
            j++;
        }
		if ((*comm)[i] && !(q % 2))
			ft_s_char(comm, &new, &i, &j);
		
	}
	free_read(NULL, comm);
	if (new)
	{
		(*comm) = ft_strdup(new);
		ft_free((void **)&new);
	}
	ft_putendl_fd(*comm, 2);
}
