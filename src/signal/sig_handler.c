#include "../minishell.h"

void ctrl_c__no_process()
{
	rl_on_new_line();
	rl_redisplay();
	printf("%c[K\n", 27);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 1;
}

void ctrl_c__yes_process()
{
	g_status = 130;
	write(1, "\n", 1);
}

void ctrl_slash__yes_process()
{
	write(1, "Quit: 3\n", 8);
	g_status = 131;
}

void ctrl_slash__no_process()
{
	rl_on_new_line();
	rl_redisplay();
	printf("%c[K", 27);
}

void sig_handler(int signum)
{
	int pid;
	int status;
	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
			ctrl_c__no_process();
		else
			ctrl_c__yes_process();
	}
	else if (signum == SIGQUIT && pid != -1)
		ctrl_slash__yes_process();
	else
		ctrl_slash__no_process();
}
