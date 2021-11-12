/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: g_ulee <g_ulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:07:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/12 14:50:48 by g_ulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include "libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# define TRUE 1
# define FALSE 0
# define D_OPEN 1
# define S_OPEN 2
# define S_CLOSE 10
# define D_CLOSE 11
# define STR 1
# define CMD 2
# define BUILT 3
# define REDIR_IN 4
# define REDIR_OUT 5
# define D_REDIR_IN 6
# define D_REDIR_OUT 7
# define PIPE 8
# define ENV 9
# define P_OR 1
# define P_AND 2

typedef struct s_token
{
	struct s_token	*pre;
	struct s_token	*next;
	char			*content;
	int				token_type;
	int				back_space;
}				t_token;

typedef struct s_bundle
{
	t_token		*token;
	int			quote;
	int			priority;
	int			is_pipe;
	char		*cmd_line;
	char		**env;
}			t_bundle;

// main
void		start_sh(char **env, char *input);
char		**dup_envp(char **envp);
void		loop(char **env);

//execute
int			execute_cmd(t_bundle *bundle);

//parsing_bundle
int			set_bundle_line(t_bundle *bundle, int word_len);
void		set_bundle(t_bundle *bundle, char **env, int bundles_num);

//parsing_token
int			parsing_token(t_bundle *bundles);
char		*make_token(char *str, int start, int end, int token_type);
int			get_token(t_bundle *bnde, char *cmd, int i, int start);
//parsing_str
int			check_quote(char *str, int start, int end);
int			parsing_quote_str(char *str, int start, int quote);
int			parsing_env_str(char *str, int start);

//utils_lst
t_token		*ft_lstnew(char *content, int token_type, int back_space);
void		ft_lstadd_back(t_token **lst, t_token *new);
void		ft_lstclear(t_token **lst);
int			ft_lstsize(t_token *lst);
t_token		*ft_lstlast(t_token *lst);

//utils_split
int			sh_count_word(char const *s);
int			sh_make_word(t_bundle *bundle, char const *s, int j, int word_len);
int			cut_cmd(t_bundle *bundles, char const *s);
t_bundle	*split_bundle(char **env, char const *str);

//utils_str
int			is_space_str(char *str);
int			check_priority(const char *str, int start);
int			is_quote(char str, int preval);
int			check_vaild_str(char *str, int start);
int			parsing_quote_str(char *str, int start, int quote);

//builtin

//error
void		print_error(char *str);
void		free_bundle(t_bundle *bundles, int i);

//command
void		ft_cd(char *path);
void		ft_env(char **env);
void		ft_export(char *str);
void		ft_pwd(void);
void		ft_unset(char *str);

char **g_env;

#endif
