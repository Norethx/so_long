/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_root_newlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:47:45 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/01 19:25:46 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_root_list	*ft_root_newlst(void)
{
	t_root_list	*new;

	new = ft_calloc(1, sizeof(t_root_list));
	if (!new)
		return (NULL);
	return (new);
}
