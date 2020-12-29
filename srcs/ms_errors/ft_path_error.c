#include "../includes/minishell.h"

int	ft_path_error(t_all *all, char **comm)
{
	all->err = 1;
	return (ft_malloc_error(comm[0]));
}
