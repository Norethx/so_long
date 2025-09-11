/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:03:25 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/11 12:25:01 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	multiplier;

	i = 0;
	result = 0;
	multiplier = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			multiplier *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = (nptr[i++] - '0') + (result * 10);
	return (result * multiplier);
}


//wdjwhd
