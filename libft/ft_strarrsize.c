/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:01:40 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:01:40 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarrsize(char **strings)
{
	int	i;

	if (!strings)
		return (0);
	i = 0;
	while (strings && strings[i])
		i++;
	return (i);
}
