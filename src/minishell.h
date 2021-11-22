/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:07:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/22 20:55:14 by hyospark         ###   ########.fr       */
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
# define ENV 3
# define REDIR_IN 4
# define REDIR_OUT 5
# define D_REDIR_IN 6
# define D_REDIR_OUT 7
# define PIPE 8
# define P_OR 1
# define P_AND 2
# define SUCCESS 0
# define FAIL 1

typedef struct s_token
{
	struct s_token	*pre;
	struct s_token	*next;
	int				pipe;
	int				redir;
	int				fd[2];
	char			*content;
	int				token_type;
	int				back_space;

}				t_token;

typedef struct s_bundle
{
	t_token		*token;
	t_token		*head;
	int			quote;
	int			priority;
	int			is_pipe;
	char		*cmd_line;
	char		**env;
	t_token		*pipe_token;
	char		*input;
}				t_bundle;

// main
void		start_sh(char **env, char *input);
char		**dup_envp(char **envp);
void		loop(char **env);

char *ft_getenv(t_bundle *bundle, char *key);

//execute
int			execute_cmd(t_bundle *bundle);

//parsing_bundle
int			set_bundle_line(t_bundle *bundle, int word_len);
void		set_bundle(t_bundle *bundle, char **env, int bundles_num, char const *str);

//parsing_token
int			set_token_type(int token_type, t_bundle *bnde, int i);
int			parsing_token(t_bundle *bundles);
char		*make_token(char *str, int start, int end, int token_type);
int			get_token(t_bundle *bnde, int i, int start);

//parsing_str
int			check_quote(char *str, int start, int end);
int			parsing_quote_str(char *str, int start, int quote);
int			parsing_env_str(char *str, int start);


//fd_utils
int			is_fdnum(char *str, int back);


//lst_utils
t_token		*ft_lstnew(char *content, int token_type, int back_space);
void		ft_lstadd_back(t_token **lst, t_token *new);
void		ft_lstclear(t_token *lst);
int			ft_lstsize(t_token *lst);
t_token		*ft_lstlast(t_token *lst);
void		ft_lst_delete(t_token *lst);
//utils_split
int			sh_count_word(char const *s);
int			sh_make_word(t_bundle *bundle, char const *s, int j, int word_len);
int			cut_cmd(t_bundle *bundles, char const *s);
t_bundle	*split_bundle(char **env, char const *str);
void		set_iotoken(t_bundle *bundle);

//utils_str
int			is_space_str(char *str);
int			check_priority(const char *str, int start);
int			is_quote(char str, int preval);
int			check_vaild_str(char *str, int start);
int			parsing_quote_str(char *str, int start, int quote);
char		*ft_strndup(const char *s, int start);


//token_utils
int			is_redir_token(t_token *token);
int			is_io_token(t_token *token);
void		replace_env_token(t_token *temp, t_bundle *bundle);

//builtin
int			is_bin(t_bundle *bundle);
int			is_builtin(t_bundle *bundle);

//redir_handler
int			redir_handler(t_bundle *bundle);
void		set_fd(t_token *token);
int			redir_in(t_bundle *bundle);
int			redir_out(t_bundle *bundle);
int			d_redir_out(t_bundle *bundle);
int	 		d_redir_in(t_bundle *bundle);
int			read_here_document(t_bundle *bundle);
void		get_readline(int fd[], t_bundle *bundle);

//pipe_handler
int	pipe_cmd(t_bundle *bundle);
//error
int			print_error(char *str, int error_num);
void		free_bundle(t_bundle *bundles);
void		child_exit(t_bundle *bundles, int status);

//command
int			ft_cd(t_bundle *bundle);
int			ft_env(t_bundle *bundle);
int			ft_export(t_bundle *bundle);
int			ft_pwd(t_bundle *bundle);
char		*ft_getenv(t_bundle *bundle, char *key);
int			ft_unset(t_bundle *bundle);
int			ft_echo(t_bundle *bundle);

#endif
