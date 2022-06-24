/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:28:47 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:28:33 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_to_strarr(char **strings, char *s)
{
	int		i;
	char	**ret;

	i = 0;
	while (strings[i])
		i++;
	ret = (char **)ft_malloc((i + 2) * sizeof(char *));
	i = -1;
	while (strings[++i])
		ret[i] = ft_strdup(strings[i]);
	ret[i] = ft_strdup(s);
	ret[i + 1] = NULL;
	return (ret);
}

int	is_valid_env(const char *var)
{
	int		i;

	if (!var || ft_isdigit(var[0]))
		return (0);
	i = -1;
	while (var[++i] && var[i] != '=')
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
	if (i < 1)
		return (0);
	return (1);
}

char	*get_val_env(char **m_env, char *name)
{
	int	i;

	i = -1;
	while (m_env[++i])
		if (!ft_strncmp(name, m_env[i], ft_strlen(name)))
			return (ft_strrchr(m_env[i], '=') + 1);
	return (NULL);
}

void	print_sorted_env(char **env)
{
	char	**dup;
	int		i;
	int		j;

	dup = ft_sortstrarr(ft_strarrdup(env));
	i = 0;
	while (dup[i])
	{
		j = 0;
		if (ft_strncmp("_", dup[i], ft_strichr(dup[i], '=')))
		{	
			printf("declare -x ");
			while (dup[i][j] && dup[i][j] != '=')
				printf("%c", dup[i][j++]);
			if (ft_strchr(dup[i], '='))
			{
				printf("=");
				printf("\"%s\"", ft_strchr(dup[i], '=') + 1);
			}
			printf("\n");
		}
		i++;
	}
	ft_freestrarr(dup);
}

int	is_in_env(char *val)
{
	int	i;

	i = -1;
	while (g_mini.env[++i])
	{		
		if (!ft_strcmp(get_name(g_mini.env[i]), get_name(val)))
		{
			g_mini.env[i] = val;
			return (1);
		}
	}
	return (0);
}
