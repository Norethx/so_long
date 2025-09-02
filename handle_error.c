/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:04:47 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/02 12:52:23 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_error(e_map error)
{
	if (error == ARGS_ERROR)
		ft_printf("Error: invalid argument\n");
	if (error == MAP_ERROR)
		ft_printf("Error: invalid map\n");
	if (error == FILE_ERROR)
		ft_printf("Error: error at open the file\n");
	if (error == ERROR_NOEXIT)
		ft_printf("Error: error map don't have exit\n");
	if (error == ERROR_NOSTART)
		ft_printf("Error: error map don't have start\n");
	if (error == ERROR_NOWALL)
		ft_printf("Error: error map don't have wall\n");
	ft_gc_end();
	return(1);
}
