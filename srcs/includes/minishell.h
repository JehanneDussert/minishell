/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:28:08 by marvin            #+#    #+#             */
/*   Updated: 2020/10/06 17:28:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structures.h"
# include "../../libft/libft.h"
# include "../../get_next_line/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>


/*
**MAIN FCTS
*/
int		main();
void	welcomer();
char	*ft_read();
void	ft_count_commands(int *count, char **buf);
void	ft_command_exec(char *comm);

/*
**UTILS FCTS
*/
int 	skipspace(char *line, int *i);
char	**ft_skip_quote(char *str, char *charset);
char	**ft_split_quote(char *str, char *charset);
void	if_in_quote(int *d, int *s, int *i, char *str);

/*
**MS_ERRORS
*/
int     ft_syntax_error_ps(char *str);
int		check_double(char *str, char *charset);
int		ft_check_errors_line(char *line);
// This function will free line + send a msg error :
int     ft_syntax_error(char *str, char *error);


#endif