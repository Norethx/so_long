/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gclstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:11:40 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/01 19:25:59 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	ft_gclstdelone(t_gc_list **lst, void (*del)(void *))
{
	if (lst[0] == 0 || del == 0)
		return ;
	if (lst[0]->content)
		(del)(lst[0]->content);
	free(lst[0]);
	lst[0] = NULL;
}
