/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:30:44 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/24 19:31:33 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(char **args, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (!args[1])
		print_sorted_env(env);
	else
	{	
		while (args[++i])
		{
			if (is_valid_env(args[i]))
			{
				j = 0;
				if (!is_in_env(args[i]))
					g_mini.env = add_to_strarr(g_mini.env, args[i]);
			}
			else
				return (ft_error("bash: export", args[i],
						"not a valid identifier", -1));
		}
	}
	return (0);
}
