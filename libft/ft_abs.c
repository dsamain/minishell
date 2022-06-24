/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:20:51 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/25 01:21:46 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int n)
{
	return (n * ((n > 0) * 2 - 1));
}

int	my_abs(int x)
{
	return ((x | (1 << 31)) ^ (1 << 31));
}	
