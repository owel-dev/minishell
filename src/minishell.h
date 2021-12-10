/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:07:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/10 17:11:30 by ulee             ###   ########.fr       */
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
# include <dirent.h>
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
# define STATUS 9
# define P_OR 1
# define P_AND 2
# define SUCCESS 0
# define FAIL 1
# define NO_BUILTIN -1
# define EXIT_1 1 << 8
# define EXIT_2 2 << 8
# define EXIT_3 3 << 8
# define EXIT_4 4 << 8
# define EXIT_5 5 << 8
# define EXIT_6 6 << 8
# define EXIT_7 7 << 8

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
	int			is_redir;
	char		*cmd_line;
	char		**env;
	t_token		*pipe_token;
	char		*input;
	char		*error_msg;
}				t_bundle;

// main
void		start_sh(char ***env, char *input);
char		**dup_env(char **envp);
void		loop(char **env, char **av);


char *builtin_getenv(t_bundle *bundle, char *key);

//execute
int			execute_cmd(t_bundle *bundle);
int			execute_cmd_classify(t_bundle *bundle);

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
t_token		*tokenlst_new(char *content, int token_type, int back_space);
void		tokenlst_add_back(t_token **lst, t_token *new);
void		tokenlst_clear(t_token *lst);
int			tokenlst_size(t_token *lst);
t_token		*tokenlst_last(t_token *lst);
void		tokenlst_delete(t_token *lst);
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
int	is_vaild_char(char c);
//token_utils
int			is_redir_token(t_token *token);
int			is_io_token(t_token *token);
void		replace_env_token(t_token *temp, t_bundle *bundle);

//builtin
int			execute_bin(t_bundle *bundle);
int			execute_builtin(t_bundle *bundle);

//redir_handler
int			redir_handler(t_bundle *bundle, t_token *token);
void		set_fd(t_token *token);
int			redir_in(t_bundle *bundle, t_token *token);
int			redir_out(t_bundle *bundle, t_token *token);
int			d_redir_out(t_bundle *bundle, t_token *token);
int	 		d_redir_in(t_bundle *bundle, t_token *token);
int			read_here_document(t_bundle *bundle, t_token *token);
void		get_readline(int fd[], t_token *t_token);
void		check_env_token(t_token *token, t_bundle *bundle);
int	set_redir_fd(t_bundle *bundle, t_token *token);

//pipe_handler
int	pipe_cmd(t_bundle *bundle);
//error
void		print_error_exit(char *str, int error_num);
void		print_error(char *str);
void		free_bundle(t_bundle *bundles);
void		child_exit(t_bundle *bundles, int status);

//buitin
int			builtin_cd(t_bundle *bundle);
int			builtin_env(t_bundle *bundle);
int			builtin_export(t_bundle *bundle);
int			builtin_pwd(t_bundle *bundle);
char		*builtin_getenv(t_bundle *bundle, char *key);
int			builtin_unset(t_bundle *bundle);
int			builtin_echo(t_bundle *bundle);
int			builtin_exit(t_bundle *bundle);\

//bin
int			run_cmd(t_bundle *bundle, char *cmd, char **arr);
t_list		*make_list(t_bundle *bundle);
char		**make_arr(t_list *list);

void sig_handler(int signum);

t_list *execute_wildcard(char *token_content);
char **execute_make_arr(t_bundle *bundle);
int execute_run_paths(t_bundle *bundle, char *cmd, char **arg_arr);
int run_cmd(t_bundle *bundle, char *cmd, char **arr);
void sig_handler(int signum);
int ft_isallblank(char *str);
char	**dup_env(char **envp);



int g_status;
#endif
