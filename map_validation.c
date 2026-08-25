#include "parsing.h"

int character_validation(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (!(map[i][j] == '0'
                || map[i][j] == '1'
                || map[i][j] == 'N'
                || map[i][j] == 'S'
                || map[i][j] == 'E'
                || map[i][j] == 'W'
                || map[i][j] == ' '))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

void    get_max_col_and_row(t_info *info)
{
    int i;
    int len;

    i = 0;
    len = 0;
    info-> max_col = 0;
    while(info->map[i])
    {
        len = ft_strlen(info->map[i]);
        if (len > info->max_col)
            info->max_col = len;
        i++;
    }
    info->row = i;
}

int last_non_space_character(char *line)
{
    int len;

    len = ft_strlen(line);
    if (len == 0)
        return (0);
    len--;
    while (len >= 0 && (line[len] == ' ' || line[len] == '\t'))
        len--;
    if (len < 0)
        return (0);
    if (line[len] != '1')
        return (0);
    return (1);
}

int first_non_space_character(char *line)
{
    int i;

    i = 0;
    while(line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '1')
        return (0);
    return (1);
}

int top_bottom_wall(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '1')
            return (0);
        i++;
    }
    return (1);
}

int wall_validation(t_info *info)
{
    int i;

    i = 0;
    while (info->map[i])
    {
        if (!first_non_space_character(info->map[i]))
            return (0);
        if (i == 0 || i == (info->row - 1))
        {
            if (!top_bottom_wall(info->map[i]))
                return (0);
        }
        if (!last_non_space_character(info->map[i]))
            return (0);
        i++;
    }
    return (1);
}

int map_validation(t_info *info)
{
    if (!character_validation(info->map))
        return (0);
    get_max_col_and_row(info);
    if (!wall_validation(info))
        return (0);
    return (1);
}