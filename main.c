/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:38:26 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/03 14:23:02 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**ft_read_map(int fd);
static char	**ft_size_map(t_gc_list *map);
static char	**ft_array_dup(char **arr);
static int	ft_verify_map(char **map);

int	main(int argc, char **argv)
{
	char		**map;
	int			fd;
	t_obj_map	meta_map;

	ft_gc_init();
	if (!argv[1] || argc > 2)
		return (handle_error(ARGS_ERROR));
	fd = open(argv[1], 0);
	if (fd < 0)
		return (handle_error(FILE_ERROR));
	map = ft_read_map(fd);
	meta_map = ft_handle_map(ft_array_dup(map));
	if (meta_map.starting == 0)
		return (1);
	ft_printf("%s", map[0]);
	ft_printf("%s", map[1]);
	ft_printf("%s", map[2]);
	ft_printf("%s", map[3]);
	ft_printf("%s", map[4]);
	ft_printf("%s", map[5]);
	close(fd);
	ft_gc_end();
}

static char	**ft_read_map(int fd)
{
	t_gc_list	*map;
	char		*line;
	char		**map_full;
	int			i;

	i = 1;
	map = ft_gc_new_root("map");
	while (i != 0)
	{
		line = get_next_line(fd);
		if (line && ft_strcmp(line, ""))
			ft_gc_register_root(ft_gcfct_register(line, GC_DATA), "map");
		else
			i = 0;
	}
	if (line && !ft_strcmp(line, ""))
		free(line);
	map_full = ft_size_map(map);
	return (map_full);
}
static char	**ft_size_map(t_gc_list *map)
{
	int		i;
	char	**map_char;
	t_list	*map_line;

	i = 0;
	map_line = ((t_root_list *)map->content)->lst->head;
	while (map_line)
	{
		map_line = map_line->next;
		i++;
	}
	map_char = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	map_line = ((t_root_list *)map->content)->lst->head;
	while (map_line)
	{
		map_char[i++] = ((t_gc_list *)map_line->content)->content;
		map_line = map_line->next;
	}
	ft_gc_new_root("full_map");
	ft_gc_register_root(ft_gcfct_register(map_char, GC_DATA), "full_map");
	return (map_char);
}

static char	**ft_array_dup(char **arr)
{
	char	**n_arr;
	int		i;

	i = 0;
	while (arr[i++])
		;
	n_arr = ft_gc_calloc(i + 1, sizeof(void *), GC_DATA)->content;
	i = 0;
	while (arr[i])
	{
		n_arr[i] = ft_gcfct_register(ft_strdup(arr[i]), GC_DATA)->content;
		i++;
	}
	return (n_arr);
}
