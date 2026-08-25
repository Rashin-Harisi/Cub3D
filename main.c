#include "parsing.h"

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
    return (1);
}

int reading_map_file(int fd, t_info *info)
{
    char    *line;
    int     map_start;

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
                continue;
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

void print_textures(t_info *info)
{
    printf("NO: %s\n", info->textures.NO);
    printf("SO: %s\n", info->textures.SO);
    printf("WE: %s\n", info->textures.WE);
    printf("EA: %s\n", info->textures.EA);
    printf("Floor: %s\n", info->floor);
    printf("Ceiling: %s\n", info->ceil);
}

void	print_map(t_info *info)
{
	int	i;

	i = 0;
	if (!info->map)
	{
		printf("Map is NULL\n");
		return ;
	}
	while (info->map[i])
	{
		printf("|%s|\n", info->map[i]);
		i++;
	}
	printf("Total rows: %d\n", i);
}

int main(int argc, char **argv)
{
    int fd;
    t_info info = {0};

    if (argc != 2)
        return (printf("Error\n"), 1);
    if (!file_extension_check(argv[1]))
        return (printf("Error\nNot valid extension\n"), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (printf("Error\nOpening file intrupted.\n"), 1);
    if (!reading_map_file(fd, &info))
    {
        printf("Error\nReading file is failed");
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
    print_textures(&info);
    print_map(&info);
    free_info(&info);
    return (0);
}
