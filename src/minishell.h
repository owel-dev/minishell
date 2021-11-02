/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:07:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/02 16:04:11 by hyospark         ###   ########.fr       */
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
# define TRUE 1
# define FALSE 0
# define D_OPEN 1
# define S_OPEN 2
# define STR 1
# define CMD 2
# define BUILT 3
# define REDIR_IN 4
# define REDIR_OUT 5
# define D_REDIR_IN 6
# define D_REDIR_OUT 7
# define PIPE 8
# define P_OR 1
# define P_AND 2

typedef struct s_token
{
	struct s_token	*pre; 
	struct s_token	*next;
	char			*content;
	int				token_type;
}				t_token;

typedef struct s_bundle
{
	t_token		*token;
	char		*cmd_line;
	int			is_quote;
	int			priority;
	int			fds[2];
	char		**env;
}			t_bundle;

// main
void	start_sh(char **env, char *input);
char	**dup_envp(char **envp);
void	loop(char **env);

//utils_lst
void		ft_lstdelone(t_token *lst);
void		ft_lstclear(t_token **lst);
void		ft_lstadd_front(t_token **lst, t_token *new);
void		ft_lstadd_back(t_token **lst, t_token *new);
t_token		*ft_lstnew(char *content);
t_token		*ft_lstlast(t_token *lst);

//parsing_token
//parsing_bundle

int		set_bundle_line(t_bundle *bundle, int word_len);
void	set_bundle(t_bundle *bundle, char **env, int bundles_num);


//utils_split
int			sh_count_word(char const *s);
int			sh_make_word(t_bundle *bundle, char const *s, int j, int word_len);
int			cut_cmd(t_bundle *bundles, char const *s);
t_bundle	*split_bundle(char **env, char const *str);


//utils_str
int		is_space_str(char *str);
int		check_priority(const char *str, int start);
int		is_quote(char str, int preval);

//parsing
void	parsing(char *str);
void	split_command(char *str);

//builtin
//error
void	print_error(char *str);


#endif
