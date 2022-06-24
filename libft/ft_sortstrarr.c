/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortstrarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:09:34 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:10:15 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_sortstrarr(char **strings)
{
	int		i;
	int		j;
	int		n;
	char	*tmp;

	n = 0;
	while (strings[n])
		n++;
	i = 0;
	while (i < n - 1)
	{
		j = i;
		while (j < n)
		{
			if (ft_strcmp(strings[i], strings[j]) > 0)
			{
				tmp = strings[i];
				strings[i] = strings[j];
				strings[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (strings);
}
