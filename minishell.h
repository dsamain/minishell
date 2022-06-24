/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:30:35 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:30:36 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2
//# define SPACE 1
//# define TAB 2
# define NEW_LINE 3
# define INPUT 4
# define OUTPUT 5
# define PIPE 6
# define HEREDOC 7 
# define APPEND 8
# define ARG 9
# define DQUOTE 10
# define QUOTE 11
# define INF 2000000000

//garbage node
typedef struct s_node {
	void			*elem;
	struct s_node	*next;
}	t_node;

typedef struct s_mini {
	int		ret;
	t_node	*garbage;
	char	**env;
	int		exit;
	int		fd_in;
	int		fd_out;
	int		sig;
	int		pid;
	char	*rline;
	int		flag;
}	t_mini;

typedef struct s_token {
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd {
	char			**arg;
	char			**in;
	char			**out;
	int				*t_in;
	int				*t_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_termcaps
{
	struct termios	old_term;	
	struct termios	new_term;	
	char			*buffer;
	char			*keys_on;
	char			*keys_off;
	char			*up_arrow;
	char			*down_arrow;
	char			*backspace;
	char			*del_line;
	char			*set_cursor_begin;
}				t_termcaps;

t_mini	g_mini;
//--------------------

//execution
int		open_in(t_cmd *cmd);
int		open_out(t_cmd *cmd, int fd_to);
int		execute_cmds(t_cmd *cmds);
int		status_child(pid_t status);
int		exec(t_cmd *cmd);
void	child_process(t_cmd *cmd, int *pipefd);
int		is_builtin(char **argv);

//builtin
int		ft_exit(char **av, int silent);
int		ft_cd(char **av);
int		ft_env(char **env);
int		ft_export(char **args, char **env);
int		ft_pwd(void);
int		ft_echo(char **av);
int		ft_unset(char **av);//, char **env);
int		driver_unset(char *name);
char	*get_name(char *val);
char	**add_to_strarr(char **strings, char *s);
int		is_valid_env(const char *var);
char	*get_val_env(char **m_env, char *name);
void	print_sorted_env(char **env);
int		is_in_env(char *val);

//env
int		shell_env(char **def_env);
char	*ft_get_env(char *key);
char	*expand(char *s);
char	*get_val_env(char **m_env, char *name);

//Parse
t_cmd	*parse(char *s);

//Token
t_token	*tokenise(char *s);
int		is_sep(char c);
int		is_space(char c);
t_token	*new_token(void);
t_token	*token_back(t_token *root);
t_token	*token_front(t_token *node);
t_token	*token_push_back(t_token *root);

//cmds
int		get_cmds_size(t_token *token_list);
t_cmd	*new_cmd(void);
t_cmd	*init_cmds(int sz);
void	print_cmds(t_cmd *cmds);

//garbage
void	*ft_malloc(int size);
int		g_push(void *elem);
t_node	*create_node(void *new_elem);
void	g_print(void);
int		g_clear(char *msg);

//utils
void	interact(int f);
char	*s_append(char *s, char c);
void	ft_putstr_fd(char *str, int fd);
char	*ft_itoa(int n);

int		*int_append(int *arr, int val, int sz);

//str
int		ft_strncmp(char *s, char *t, int n);
char	*ft_substr(char *s, unsigned int start, unsigned int n);
char	*s_append_str(char *s1, char *s2);

//	strs
char	**ft_strs_cpy(char **strs);
int		ft_strslen(char **strs);
void	ft_strs_print(char **strs);
char	**strs_append(char **strs, char *s);
int		ft_clstize(t_cmd *cmds);

#endif