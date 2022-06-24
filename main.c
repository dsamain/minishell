/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:49:14 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 00:29:59 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ctrl-c doesnt give back prompt

//ctrl-d needs to be pressed twice if command wanst found
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

void	init_mini(void)
{
	if (!isatty(STDIN_FILENO))
	{	
		g_clear("");
		ft_exit(NULL, 1);
	}
	g_mini.garbage = NULL;
	g_mini.env = NULL;
}

char	*ft_readline(char *prompt)
{
	char	*tmp;

	interact(0);
	tmp = readline(prompt);
	interact(1);
	free(tmp);
	return (ft_substr(tmp, 0, ft_strlen(tmp)));
}

int	run(char *s)
{		
	char	*line;
	t_cmd	*cmds;

	line = expand(s);
	if (!line)
		return (1);
	cmds = parse(line);
	execute_cmds(cmds);
	add_history(s);
	if (g_mini.flag)
		g_mini.ret = 130;
	return (0);
}

int	main(int ac, char **av, char **d_env)
{
	char	*s;

	ac += 1;
	av += 1;
	g_mini.env = ft_strs_cpy(d_env);
	g_mini.exit = 0;
	while (!g_mini.exit)
	{
		s = ft_readline("\033[34;1;4mminishell$>\033[0m ");
		if (!s)
		{
			g_mini.sig = SIGQUIT;
			g_mini.ret = 131;
			exit(0);
		}
		if (s && *s && g_mini.sig != SIGINT && g_mini.sig != SIGQUIT)
			if (run(s))
				continue ;
		g_mini.sig = 0;
	}
	g_clear("");
	rl_clear_history();
	return (0);
}
