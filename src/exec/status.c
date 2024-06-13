#include "../includes/minishell.h"

int		control_status(int status)
{
	static int	status_backup;

	if (status == -1)
		return (status_backup);
	status_backup = status;
	return (status_backup);
}

void	handle_signal_exec(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		control_status(signum + 128);
	}
}

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
		control_status(signum + 128);
	}
}

void	prepare_signals(void)
{
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
}