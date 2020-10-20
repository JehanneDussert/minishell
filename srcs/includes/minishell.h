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
void	byebye();
char	*ft_read();
void	ft_count_commands(int *count, char **buf);
void	ft_command_exec(char *comm, t_exit *exit);

/*
**UTILS FCTS
*/
char	*pipes_id(t_cmd **cmd, t_exit *exit);
int 	skipspace(char *line, int *i);
char	**ft_skip_quote(char *str, char *charset);
char	**ft_split_quote(char *str, char *charset);
void	if_in_quote(int *d, int *s, int *i, char *str);

/*
**MS_ERRORS
*/
int		ft_syntax_error_ps(char *str);
int		check_double(char *str, char *charset);
int		ft_check_errors_line(char *line);
// This function will free line + send a msg error :
/*
** Error msg :
*/
int     ft_syntax_error(char *str, char *error);
int	    ft_malloc_error(void);
void	error_msg(char *bin, char *message);

/*
**MS_PARSING
*/
char	*command_id(char **comm, t_exit *exit);;
void	ft_echo(char **comm);
void	cd_id(char **cmd);
void	pwd_id();

/*
**FREE
*/
void	free_read(char ***buf, char **line);

#endif