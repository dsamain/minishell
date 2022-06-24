/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:08:15 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:08:38 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrdup(char **strings)
{
	char	**ret;
	int		n;
	int		i;

	n = 0;
	while (strings[n])
		n++;
	ret = (char **)ft_malloc((n + 1) * sizeof(char *));
	i = -1;
	while (++i < n)
		ret[i] = ft_strdup(strings[i]);
	ret[n] = NULL;
	return (ret);
}
