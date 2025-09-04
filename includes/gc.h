/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:57:31 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/04 20:07:16 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_gc_type
{
	GC_DATA,
	GC_ROOT,
	GC_SYSROOT,
	GC_META
}						t_gc_type;

typedef struct s_gc_list
{
	void				*content;
	struct s_gc_list	*next;
	struct s_gc_list	*prev;
	t_gc_type			type;
	int					marked;
}						t_gc_list;

typedef struct s_gcext_list
{
	t_gc_list			*head;
	t_gc_list			*tail;
}						t_gcext_list;

typedef struct s_root_list
{
	char				*categ;
	t_ext_list			*lst;
}						t_root_list;

t_gcext_list			*ft_gc_start(void);
void					ft_gclstadd_back(t_gcext_list **lst, t_gc_list *new);
t_gc_list				*ft_gc_calloc(size_t nmemb, size_t size,
							t_gc_type type);
t_gc_list				*ft_gc_malloc(size_t size, t_gc_type type);
t_gc_list				*ft_gcfct_register(void *content, t_gc_type type);
t_root_list				*ft_root_newlst(void);
int						ft_gc_rm(t_gc_list **lst);
void					*ft_gc_new_root(char *categ);
int						ft_gc_init(void);
void					ft_gclstdelone(t_gc_list **lst, void (*del)(void *));
void					ft_gc_mark(t_gc_list *lst);
void					ft_gc_sweep(void);
void					ft_gc_collect(void);
void					*ft_gc_register_root(t_gc_list *n_root, char *categ);
t_gc_list				*ft_to_gc_list(void *x);
t_root_list				*ft_to_root_list(void *x);
void					ft_gc_rm_root(t_ext_list **root, t_list *rm_root);
t_list					*ft_gc_clean_root(char *categ);
void					ft_gc_del_root(char *categ);
void					ft_gc_rm_meta(char *categ);
void					ft_gc_end(void);
t_gc_list				*ft_gcfct_arr_register(void **content, t_gc_type type);
t_ext_list				*ft_ext_newlst(void);
t_root_list				*ft_gc_call_root(char *categ);

#endif
