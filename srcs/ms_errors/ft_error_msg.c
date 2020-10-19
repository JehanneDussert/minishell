#include "../includes/minishell.h"

int	ft_syntax_error(char *str, char *error)
{
    free(str);
    str = NULL;
	if (ft_strncmp(error, "double", 6) == 0)
		ft_putstr_fd("~: syntax error near unexpected token : double tokens", 1);
	else if (ft_strncmp(error, "ps", 2) == 0)
		ft_putstr_fd("~: syntax error near unexpected token : pipe or semi error", 1);
	else if (ft_strncmp(error, "chevrons", 8) == 0)
		ft_putstr_fd("~: syntax error near unexpected token : chevrons error", 1);
    return(0);
}
