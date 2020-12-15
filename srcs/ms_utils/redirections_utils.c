#include "../includes/minishell.h"

int		ft_nb_to_print(char **comd)
{
	int	w;
	int	i;

	w = 0;
	i = 0;
	while (comd[0] && comd[0][i])
	{
		while (comd[0][i] && !is_charset(comd[0][i], "><"))
		{
			w++;
			i++;
		}
		ft_skip_redirection(comd, &i);
	}
	return (w);
}

void	ft_copy_clean_comd(char **comd, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (comd[0] && comd[0][i])
	{
		while (comd[0][i] && !is_charset(comd[0][i], "><"))
		{
			tmp[0][j] = comd[0][i];
			j++;
			i++;
		}
		ft_skip_redirection(comd, &i);
	}
}

char	*ft_return_new_comd(char **comd)
{
	char	*tmp;
	int		w;

	w = ft_nb_to_print(comd);
	if ((tmp = ft_calloc(w + 1, sizeof(char))) == NULL)
		return (NULL);
	ft_copy_clean_comd(comd, &tmp);
	free_read(NULL, comd);
	if (tmp)
	{
		comd[0] = ft_strdup(tmp);
		ft_free((void **)&tmp);
	}
	return (comd[0]);
}

char	*ft_create_file(char *str, char **file)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (is_charset(str[j], "> "))
		j++;
	while (str[i + j] && str[i + j] != ' ')
		i++;
	(*file) = ft_substr(str, j, i);
	return (*file);
}
