#include "../includes/minishell.h"

int	ft_syntax_error(char *str, char *error)
{
    free(str);
    str = NULL;
	if (ft_strncmp(error, "double", 6) == 0)
		ft_putstr_fd("minishell : syntax error near unexpected token", 1);
	else if (ft_strncmp(error, "ps", 2) == 0)
		ft_putstr_fd("minishell : syntax error near unexpected token", 1);
    return(0);
}
