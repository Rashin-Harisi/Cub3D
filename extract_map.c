#include "parsing.h"

char    **expand_map(char **map, int map_row)
{
    char    **new;
    int     i;

    i = 0;
    new = malloc(sizeof(char *) * (map_row + 2));
    if (!new)
        return (NULL);
    while (i < map_row)
    {
        new[i] = map[i];
        i++;
    }
    free(map);
    return (new);
}

int extract_map(char *line, t_info *info)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        len--;
    info->map = expand_map(info->map, info->map_row);
    if (!info->map)
        return (0);
    info->map[info->map_row] = malloc(sizeof(char) * (len + 1));
    if (!info->map[info->map_row])
        return (0);
    while (i < len)
    {
        info->map[info->map_row][i] = line[i];
        i++;
    }
    info->map[info->map_row][i] = '\0';
    info->map_row++;
    info->map[info->map_row] = NULL;
    return (1);
}