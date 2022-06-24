/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:55:11 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 00:33:01 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(char **argv)
{
	int	ret;

	ret = g_mini.ret;
	if (argv)
	{		
		if (!ft_strcmp(argv[0], "echo"))
			ret = ft_echo(argv);
		else if (!ft_strcmp(argv[0], "unset"))
			ret = ft_unset(argv);
		else if (!ft_strcmp(argv[0], "export"))
			ret = ft_export(argv, g_mini.env);
		else if (!ft_strcmp(argv[0], "cd"))
			ret = ft_cd(argv);
		else if (!ft_strcmp(argv[0], "pwd"))
			ret = ft_pwd();
		else if (!ft_strcmp(argv[0], "env"))
			ret = ft_env(g_mini.env);
		else if (!ft_strcmp(argv[0], "exit"))
			ret = ft_exit(argv, 0);
		else if ((!ft_strcmp(argv[0], "env")))
			ret = ft_env(g_mini.env);
	}
	return (ret);
}

int	fork_program(t_cmd *cmd)
{
	int		pipefd[2];
	int		ret;

	ret = 0;
	pipe(pipefd);
	g_mini.pid = fork();
	if (g_mini.pid)
	{
		close(pipefd[1]);
		if (g_mini.fd_in > 0)
			close(g_mini.fd_in);
		if (cmd->arg)
			ret = exec_builtin(cmd->arg);
		if (!cmd->arg || !is_builtin(cmd->arg))
			waitpid(g_mini.pid, &ret, 0);
		g_mini.fd_in = pipefd[0];
	}
	else
		child_process(cmd, pipefd);
	return (status_child(ret));
}	

int	execute_cmds(t_cmd *cmds)
{
	g_mini.fd_in = -1;
	g_mini.fd_out = -1;
	while (cmds)
	{
		g_mini.ret = fork_program(cmds);
		cmds = cmds->next;
	}
	return (0);
}
