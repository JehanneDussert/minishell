/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:10:47 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/29 13:57:50 by ede-banv         ###   ########.fr       */
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
int		main(void);
void	welcomer(void);
void	byebye(void);
char	*ft_read(t_all *all);
void	ft_count_commands(int *count, char **buf);
void	ft_command_exec(char *comm, t_all *all);

/*
**MS_PARSING
*/
char	*pipes_id(t_all *all);
char	*command_id(char **comm, t_all *all, int mode);
void	ft_echo(char **comm, t_all *all);
void	cd_id(char **cmd, t_all *all);
void	pwd_id(t_all *all);
void	export_id(char **cmd, t_all *all);
int		export_errors(char *str);
void	print_line(t_lst *lst, int n);
void	ft_unset(char **cmd, t_all *all);
void	env_id(char **comm, t_all *all);
int		ft_exec(char **comm, t_all *all);
int		execve_fct(char **comm, char *path, t_all *all);
char	**make_envp(t_all *all);
void	path_id(char **comm, t_all *all);
void	ft_check_n(int *i, int *res, char *comm, char **opt);
int		ft_echo_n(char *comm, char **opt);
void	ft_redirections(char ***comd, t_all *all);

/*
**UTILS FCTS
*/
void	ft_init_all(t_all *all);
void	ft_init_echo(int *i, char **opt, int *res);
void	ft_init_quote(int *i, int *k, int *d, int *s);
int		skipspace(char *line, int *i);
char	**ft_skip_quote(char *str, char *charset);
char	**ft_split_quote(char *str, char *charset);
void	if_in_quote(int *d, int *s, int *i, char *str);
t_lst	*ft_lstnew_ms(void *w1, void *w2);
t_lst	*ft_lstlast_ms(t_lst *lst);
void	ft_lstadd_back_ms(t_lst **alst, t_lst *new);
int		create_words(char **w1, char **w2, char *cmd);
void	lst_add_env(char **env, t_all *all);
void	ft_lstdelone_ms(t_lst *lst, void (*del)(void *));
void	ft_lstclear_ms(t_lst **lst, void (*del)(void *));
int		export_errors(char *str);
void	empty_tmp(t_all *all);
int		is_charset(char c, char *charset);

/*
**MS_ERRORS
*/
int		ft_error_ps(char *str);
int		ft_quote_error(char *str);
int		check_chevrons(char *str);
int		check_double(char *str, char *charset);
int		ft_check_errors_line(char *line, t_all *all);

/*
**Error msg :
*/
int		ft_syntax_error(char *error, t_all *all);
int		ft_malloc_error(char *bin);
void	error_msg(char *bin, char *message);

/*
**FREE
*/
void	free_read(char ***buf, char **line);
void	free_commands(t_all *all);
void	free_all(t_all *all);

#endif
