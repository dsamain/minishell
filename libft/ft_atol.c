/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:23:55 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:24:00 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

signed long long	ft_atol(const char *str)
{
	signed long long	n;
	int					sign;

	n = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - 48;
		str++;
	}		
	return ((signed long long)n * sign);
}
