/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:53:53 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:46:13 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*bin_path(char *cmd, char **env)
{
	char	**bins;
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i] && !path)
		path = ft_strnstr(env[i], "PATH=", 5);
	bins = ft_split(path + 5, ":");
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (bins && bins[++i])
	{
		path = ft_strjoin(bins[i], cmd);
		if (!access(path, F_OK))
			return (path);
	}
	return (NULL);
}

int	is_builtin(char **argv)
{
	if ((!ft_strcmp(argv[0], "echo"))
		|| (!ft_strcmp(argv[0], "unset"))
		|| (!ft_strcmp(argv[0], "export"))
		|| (!ft_strcmp(argv[0], "cd"))
		|| (!ft_strcmp(argv[0], "pwd"))
		|| (!ft_strcmp(argv[0], "env"))
		|| (!ft_strcmp(argv[0], "exit"))
		|| (!ft_strcmp(argv[0], "env")))
		return (1);
	return (0);
}

int	status_child(int status)
{
	int	ret;

	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		ret = WTERMSIG(status);
		if (ret != 131)
			ret += (unsigned char) 128;
	}
	return (ret);
}

int	exec(t_cmd *cmd)
{
	char	*path;

	if (is_builtin(cmd->arg))
		return (1);
	if (cmd->arg && ft_strchr(cmd->arg[0], '/'))
		path = cmd->arg[0];
	else
		path = bin_path(cmd->arg[0], g_mini.env);
	if (!path)
		return (ft_error("access", cmd->arg[0],
				"couldn't find path to executable", -2));
	if (execve(path, cmd->arg, g_mini.env) == -1)
		return (ft_error("execve", NULL,
				"couldnt execute command", -1));
	return (0);
}

void	child_process(t_cmd *cmd, int *pipefd)
{
	int	in;
	int	ret;

	close(pipefd[0]);
	if (!cmd->in && g_mini.fd_in > 0)
		dup2(g_mini.fd_in, STDIN);
	in = open_in(cmd);
	if (in == -2)
		exit(0);
	if ((cmd->in && in == -1) || (cmd->out && open_out(cmd, STDOUT) == -1))
		exit(1);
	if (cmd->next)
		dup2(pipefd[1], STDOUT);
	if (is_builtin(cmd->arg))
		exit(0);
	ret = exec(cmd);
	if (ret == -1)
		exit(126);
	if (ret == -2)
		exit(127);
}
