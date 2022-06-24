/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:26:11 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:27:44 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_pwd(char **env)
{
	char	*args_pwd[3];
	char	*args_oldpwd[3];
	char	path[PATH_MAX + 1];

	getcwd(path, PATH_MAX);
	args_oldpwd[0] = "export";
	args_oldpwd[1] = ft_strjoin("OLDPWD=", get_val_env(env, "PWD"));
	args_oldpwd[2] = NULL;
	args_pwd[0] = "export";
	args_pwd[1] = ft_strjoin("PWD=", path);
	args_pwd[2] = NULL;
	ft_export(args_pwd, env);
	ft_export(args_oldpwd, env);
}

//getcwd,chdir
int	driver_cd(char *path)
{
	char	*abs_path;
	char	*tmp;
	int		ret;

	ret = -1;
	if (!ft_strncmp(path, "/", 1))
	{
		ret = chdir(path);
		update_env_pwd(g_mini.env);
	}
	else
	{
		if (!ft_strncmp(path, "./", 2))
			path += 2;
		tmp = ft_strjoin(get_val_env(g_mini.env, "PWD"), "/");
		abs_path = ft_strjoin(tmp, path);
		ret = chdir(abs_path);
		update_env_pwd(g_mini.env);
		free(tmp);
		free(abs_path);
	}
	return (ret);
}

int	ft_cd(char **av)
{
	if (ft_strarrsize(av) == 1)
	{	
		if (!get_val_env(g_mini.env, "HOME"))
			return (ft_error("minishell : cd", 0, "HOME not set", 1));
		return (driver_cd(get_val_env(g_mini.env, "HOME")));
	}
	else if (ft_strarrsize(av) > 2)
		return (ft_error("minishell : cd", 0, "too many arguments", 1));
	else if (ft_strarrsize(av) == 2)
	{
		if (!ft_strcmp(av[1], "-"))
		{
			if (get_val_env(g_mini.env, "OLDPWD"))
			{
				printf("%s\n", get_val_env(g_mini.env, "OLDPWD"));
				return (driver_cd(get_val_env(g_mini.env, "OLDPWD")));
			}
			else
				return (ft_error("minishell : cd", NULL, "OLDPWD not set", 1));
		}
		else if (driver_cd(av[1]))
			return (ft_error("minishell : cd", av[1],
					"No such file or directory", 1));
	}
	return (0);
}
