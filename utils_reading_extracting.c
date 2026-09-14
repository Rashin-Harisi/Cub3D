#include "cub3d.h"

int extract_info(char *line, t_info *info)
{
	int i;

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

int process_line(char *line, t_info *info, int *map_start)
{
	if (!*map_start)
	{
		if (is_empty_line(line))
			return (1);
		if (!all_data_found(info))
			return (extract_info(line, info));
		*map_start = 1;
	}
	return (extract_map(line, info));
}

int reading_config_file(int fd, t_info *info)
{
	char *line;
	int map_start;

	map_start = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(line, info, &map_start))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (!map_start)
		return (printf("Map does not detected.\n"), 0);
	return (1);
}

int validate_and_normalize(t_info *info)
{
	if (!all_data_found(info))
		return (printf("Error\nInvalid texture configuration\n"), 0);
	if (!info_validation(info))
		return (printf("Error\n"), 0);
	if (!normalized_map(info))
		return (printf("Error\n"), 0);
	return (1);
}

int read_file(char *file, t_info *info)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nOpening file interrupted.\n"), 0);
	if (!reading_config_file(fd, info))
	{
		close(fd);
		return (printf("Error\n"), 0);
	}
	close(fd);
	return (1);
}