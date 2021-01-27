#include "../includes/minishell.h"

void	ft_end_of_env(char *comm, int *i)
{
	while (comm[*i] && comm[*i] != ' ' && comm[*i] != '$'
		&& comm[*i] != '\'' && comm[*i] != '\"' &&
		comm[*i] != '=' && comm[*i] != '\\' && comm[*i] &&
		comm[*i] != '}')
		(*i)++;
}

void	ft_tmp(char ***new, char **tmp, t_copy *copy, int *k)
{
	*tmp = ft_strdup((*new)[0]);
	free_read(NULL, (*new));
	*k = 0;
	copy->j = 0;
}

void	ft_init_env_check(int *k, char **tmp, char *comm, t_copy *copy)
{
	*k = copy->i;
	*tmp = &comm[copy->i];
}

void	ft_env(char *comm, char ***new, t_copy *copy, t_all *all)
{
	char	*tmp;
	int		k;
	int		res;

	ft_init_env_check(&k, &tmp, comm, copy);
	if (comm[copy->i])
	{
		ft_check_if_err_nb(comm, copy, new, all);
		ft_end_of_env(comm, &copy->i);
		tmp = ft_substr(comm, k, (copy->i - k));
		if ((res = ft_check_env(all->alst, tmp, new)) == 0 &&
			(ft_strchr(comm, '>') || (ft_strchr(comm, '>'))))
			return (ft_ambiguous_redir(new, &tmp));
		ft_free((void **)&tmp);
		if (copy->i - k < res)
			all->cmd_len += res;
		if (comm[copy->i] == '\"')
			++(copy->i);
		ft_tmp(new, &tmp, copy, &k);
		if (((*new)[0] = ft_calloc(all->cmd_len + 1, sizeof(char))) == NULL)
			return ;
		while (tmp[k])
			ft_cmd_fill(&tmp, new, &k, &copy->j);
		ft_free((void **)&tmp);
	}
}
