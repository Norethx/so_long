/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:38:26 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/05 19:41:19 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**ft_read_map(char *argv);
static char	**ft_size_map(t_gc_list *map);
static char	**ft_array_dup(char **arr);
int			teste(t_game *meta_map);
// void				hook(void *param);

int	main(int argc, char **argv)
{
	char	**map;
	t_game	*meta_map;

	ft_gc_init();
	if (!argv[1] || argc > 2)
		return (handle_error(ARGS_ERROR));
	ft_printf("Argument detected, trying to open file...\n");
	map = ft_read_map(argv[1]);
	if (!map || map[0][0] == 0)
		return (handle_error(FILE_ERROR));
	ft_printf("Parsing map...\n");
	meta_map = ft_handle_map(ft_array_dup(map));
	if (!meta_map)
		return (1);
	meta_map->map = map;
	meta_map->qt_col = meta_map->collect->qt;
	ft_printf("Map is valid.\n");
	ft_handle_game(meta_map);
	ft_gc_end();
}

static char	**ft_read_map(char *argv)
{
	t_gc_list	*map;
	char		*line;
	char		**map_full;
	int			fd;

	if (ft_check_extension(argv, ".ber"))
		return (NULL);
	fd = open(argv, 0);
	if (fd < 0)
		return (NULL);
	map = ft_gc_new_root("map");
	ft_printf("Processing file...\n");
	line = get_next_line(fd);
	while (line && ft_strcmp(line, ""))
	{
		ft_gc_register_root(ft_gcfct_register(line, GC_DATA), "map");
		line = get_next_line(fd);
	}
	if (line && !ft_strcmp(line, ""))
		free(line);
	map_full = ft_size_map(map);
	ft_printf("File fully read.\n");
	close(fd);
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
	char **n_arr;
	int i;

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
