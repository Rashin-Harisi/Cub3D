/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:47:51 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 10:49:31 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

int	extract_info(char *line, t_info *info)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (extract_no(line, i, info));
	if (line[i] == 'S' && line[i + 1] == 'O' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (extract_so(line, i, info));
	if (line[i] == 'W' && line[i + 1] == 'E' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (extract_we(line, i, info));
	if (line[i] == 'E' && line[i + 1] == 'A' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (extract_ea(line, i, info));
	if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (extract_floor(line, i, info));
	if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (extract_ceil(line, i, info));
	return (0);
}

int	reading_config_file(int fd, t_info *info)
{
	char	*line;
	int		map_start;

	map_start = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_start)
		{
			if (is_empty_line(line))
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			if (!all_data_found(info))
			{
				if (!extract_info(line, info))
					return (free(line), 0);
			}
			else
			{
				map_start = 1;
				if (!extract_map(line, info))
					return (free(line), 0);
			}
		}
		else
		{
			if (!extract_map(line, info))
				return (free(line), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!map_start)
		return (printf("Map does not detected.\n"),0);
	return (1);
}

void	print_textures(t_info *info)
{
	printf("NO: %s\n", info->textures.NO);
	printf("SO: %s\n", info->textures.SO);
	printf("WE: %s\n", info->textures.WE);
	printf("EA: %s\n", info->textures.EA);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
	{
		printf("Map is NULL\n");
		return ;
	}
	while (map[i])
	{
		printf("|%s|\n", map[i]);
		i++;
	}
	printf("Total rows: %d\n", i);
}

void	print_rgb(t_info *info)
{
	printf("Floor RGB: %d,%d,%d\n",
		info->rgb_floor[0],
		info->rgb_floor[1],
		info->rgb_floor[2]);

	printf("Ceiling RGB: %d,%d,%d\n",
		info->rgb_ceil[0],
		info->rgb_ceil[1],
		info->rgb_ceil[2]);
}


int	main(int argc, char **argv)
{
	int		fd;
	t_info	info = {0};

	if (argc != 2)
		return (printf("Error\n"), 1);
	if (!file_extension_check(argv[1]))
		return (printf("Error\nNot valid extension\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("Error\nOpening file intrupted.\n"), 1);
	if (!reading_config_file(fd, &info))
	{
		printf("Error\n");
		close(fd);
		free_info(&info);
		return (1);
	}
	close(fd);
	if (!all_data_found(&info))
	{
		free_info(&info);
		return (printf("Error\nInvalid texture configuration\n"), 1);
	}
	if (!info_validation(&info))
	{
		free_info(&info);
		return (printf("Error\n"), 1);
	}
	if (!normalized_map(&info))
	{
		free_info(&info);
		return (printf("Error\n"), 1);
	}
	//print_textures(&info);
	//print_rgb(&info);
	printf("parsed map:\n");
	print_map(info.map);
	printf("normalized map: \n");
	print_map(info.rect_map);
	free_info(&info);
	return (0);
}
