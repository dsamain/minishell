/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:59:45 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:24:35 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_path_perm(char *path)
{
	int	perm;

	perm = 0;
	if (access(path, F_OK))
		return (-1);
	else
	{
		if (!access(path, R_OK))
			perm |= 4;
		if (!access(path, W_OK))
			perm |= 2;
		if (!access(path, X_OK))
			perm |= 1;
		return (perm);
	}
}

int	here_doc(char *dlmtr, char *file, int r)
{
	char	buffer[1025];
	int		pip[2];

	pipe(pip);
	while (1)
	{
		ft_memset((void *)buffer, 0, r);
		write(STDOUT, "> ", 2);
		while (!ft_strnstr(buffer, "\n", ft_strlen(buffer)))
		{
			buffer[0] = 0;
			r = read(STDIN, buffer, 1024);
			if (r >= 0)
				buffer[r] = 0;
			if (ft_strncmp(dlmtr, buffer, ft_strlen(dlmtr) - 1))
				file = ft_strjoin(file, buffer);
			else
			{
				file = expand(file);
				write(pip[1], file, ft_strlen(file));
				close(pip[1]);
				return (pip[0]);
			}
		}
	}
}

int	open_in(t_cmd *cmd)
{
	int	fd_in;
	int	i;

	i = 0;
	fd_in = -1;
	while ((cmd->in && cmd->in[i]))
	{	
		if (fd_in > 0)
			close(fd_in);
		if (cmd->t_in && cmd->t_in[i])
			fd_in = here_doc(cmd->in[i], NULL, 0);
		else
		{	
			fd_in = open(cmd->in[i], O_RDONLY, S_IRWXU);
			if (fd_in < 0)
				return (ft_error("minishell", cmd->in[i],
						"No such file or directory", -1));
		}
		dup2(fd_in, STDIN);
		i++;
	}
	return (fd_in);
}

int	open_out(t_cmd *cmd, int fd_to)
{
	int	fd_out;
	int	i;

	i = 0;
	fd_out = -1;
	while (cmd->out && cmd->out[i])
	{	
		if (fd_out > 0)
			close(fd_out);
		if (cmd->t_out[i])
			fd_out = open(cmd->out[i], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		else
			fd_out = open(cmd->out[i], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (fd_out < 0)
			return (ft_error("minishell", cmd->out[i],
					"No such file or directory", -1));
		else
			dup2(fd_out, fd_to);
		i++;
	}
	return (fd_out);
}
