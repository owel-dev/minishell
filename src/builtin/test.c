#include "../minishell.h"
char	**dup_envp(char **envp)
{
	char	**env;
	int		len;
	int		i;

	len = 0;
	while (envp[len])
		len++;
	env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
t_token *new_token(char *content)
{
	t_token *ret;

	ret = malloc(sizeof(t_token));
	if (ft_strcmp(content, "||") == 0)
		ret->token_type = PIPE;
	ret->content = ft_strdup(content);
	ret->back_space = 1;
	ret->next = NULL;
	return (ret);
}
void append_token(t_token **token, char *content)
{
	t_token *temp;
	if (*token == NULL)
	{
		*token = new_token(content);
		return ;
	}
	temp = *token;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_token(content);
}

int main(int ac, char **av, char **env)
{
	t_bundle bundle;
	t_token *token;
	t_token *token2;
	t_token *token3;

	bundle.env = dup_envp(env);
	token = NULL;
	token2 = NULL;
	token3 = NULL;

	printf("===========ls===========\n");
	append_token(&token, "ls");
	append_token(&token, "ll");
	append_token(&token, "||");
	append_token(&token, "-al");
	// append_token(&token2, "pwd");
	bundle.token = token;
	is_builtin(&bundle);
	is_bin(&bundle);
	// bundle.token = token2;
	// is_builtin(&bundle);
	printf("========================\n\n");

	// printf("===========cd===========\n");
	// append_token(&token, "cd");
	// append_token(&token, "../..");
	// append_token(&token2, "pwd");
	// // append_token(&token2, "||");
	// bundle.token = token;
	// is_builtin(&bundle);
	// bundle.token = token2;
	// is_builtin(&bundle);
	// printf("========================\n\n");

	// printf("==========echo==========\n");
	// token = NULL;
	// append_token(&token, "echo");
	// append_token(&token, "hello");
	// append_token(&token, "world");
	// append_token(&token, "hi");
	// append_token(&token, "||");
	// append_token(&token, "hi2");
	// bundle.token = token;
	// is_builtin(&bundle);
	// printf("========================\n\n");

	// printf("=========export=========\n");
	// token = NULL;
	// token2 = NULL;
	// append_token(&token, "export");
	// append_token(&token, "USER2=ttttlee");
	// append_token(&token, "USER3=ttttlee");
	// append_token(&token2, "env");
	// bundle.token = token;
	// is_builtin(&bundle);
	// bundle.token = token2;
	// is_builtin(&bundle);
	// printf("========================\n\n");

	// printf("=========unset=========\n");
	// token = NULL;
	// token2 = NULL;
	// append_token(&token, "unset");
	// append_token(&token, "USER2");
	// append_token(&token, "||");
	// append_token(&token, "TERM");
	// append_token(&token2, "env");
	// bundle.token = token;
	// is_builtin(&bundle);
	// bundle.token = token2;
	// is_builtin(&bundle);
	// printf("========================\n\n");


}
