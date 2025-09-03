/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:04:47 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/03 16:07:13 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_error(t_map error)
{
	if (error == ARGS_ERROR)
		ft_printf("Error: invalid arguments\n");
	if (error == MAP_ERROR)
		ft_printf("Error: map is too small\n");
	if (error == FILE_ERROR)
		ft_printf("Error: invalid file\n");
	if (error == ERROR_NOEXIT)
		ft_printf("Error: map has no exit\n");
	if (error == ERROR_NOSTART)
		ft_printf("Error: map has no start position\n");
	if (error == ERROR_NOWALL)
		ft_printf("Error: map has no wall\n");
	if (error == ERROR_MAPNOTREC)
		ft_printf("Error: map is not rectangular\n");
	if (error == ERROR_NOCOLLEC)
		ft_printf("Error: map has no collectibles\n");
	if (error == ERROR_OTHERSCHARS)
		ft_printf("Error: map has invalid characters\n");
	if (error == ERROR_MOREONESTART)
		ft_printf("Error: map has more than one start position\n");
	if (error == ERROR_MOREONEEXIT)
		ft_printf("Error: map has more than one exit\n");
	ft_gc_end();
	return (1);
}
