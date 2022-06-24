/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:22:25 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 00:53:57 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int sig)
{
	if (!g_mini.pid)
		return ;
	g_mini.sig = sig;
	g_mini.ret = 130;
	kill(g_mini.pid, SIGKILL);
	waitpid(g_mini.pid, NULL, 0);
	g_mini.pid = 0;
	write(1, "^C\n", 3 * (sig == SIGINT));
	g_mini.flag = 1;
}

void	prompt_sig(int sig)
{
	rl_on_new_line();
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
	rl_redisplay();
	sig += 1;
}

void	void_function(int sig)
{
	sig += 1;
}

void	interact(int f)
{
	struct termios	termios_p;
	int				tty;

	tty = ttyslot();
	tcgetattr(tty, &termios_p);
	termios_p.c_lflag &= ~(ECHOCTL);
	if (f)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, void_function);
	}
	else
	{
		g_mini.flag = 0;
		signal(SIGINT, prompt_sig);
		signal(SIGQUIT, prompt_sig);
	}
	tcsetattr(tty, TCSANOW, &termios_p);
}
