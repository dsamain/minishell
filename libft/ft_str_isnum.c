/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:09:13 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:09:21 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isnum(const char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	if (ft_atol(str) > (__INT_MAX__) || ft_atol(str) < (1 << 31))
		return (0);
	if (!(str[++i] == '+' || str[i] == '-')
		&& !((str[i] >= '0' && str[i] <= '9')))
		return (0);
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}
