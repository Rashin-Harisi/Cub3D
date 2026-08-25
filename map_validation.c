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
    while (len >= 0 && (line[len] == ' '))
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
    while(line[i] == ' ')
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
        if (line[i] != ' ' && line[i] != '1')
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

int is_void_neighbor(int i, int j, char **map)
{
    if (i < 0 || !map[i])
        return (1);
    if (j < 0 || j >= (int)ft_strlen(map[i]))
        return (1);
    if (map[i][j] == ' ')
        return (1);
    return (0);
}

int is_playable(int i, int j, char **map)
{
    if (map[i][j] == '0' || map[i][j] == 'W'
        || map[i][j] == 'S' || map[i][j] == 'N'
        || map[i][j] == 'E')
        return (1);
    return (0);
}

int playable_tile(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (is_playable(i, j, map))
            {
                if (is_void_neighbor(i - 1, j, map)
                    || is_void_neighbor(i + 1, j, map)
                    || is_void_neighbor(i, j - 1, map)
                    || is_void_neighbor(i, j + 1, map))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int only_one_player(t_info *info)
{
    int i;
    int j;
    int count;

    count = 0;
    i = 0;
    while (info->map[i])
    {
        j = 0;
        while (info->map[i][j])
        {
            if (info->map[i][j] == 'N' || info->map[i][j] == 'S'
                || info->map[i][j] == 'E' || info->map[i][j] == 'W')
            {
                count++;
                info->player[0] = i;
                info->player[1] = j;
                info->player_dir = info->map[i][j];
            }
            j++;
        }
        i++;
    }
    if (count != 1)
        return (0);
    return (1);
}

int map_validation(t_info *info)
{
    if (!info || !info->map || !info->map[0])
        return (0);
    if (!character_validation(info->map))
        return (printf("charcter\n"), 0);
    get_max_col_and_row(info);
    if (!wall_validation(info))
        return (printf("wall\n"), 0);
    if (!only_one_player(info))
        return (printf("player\n"), 0);
    if (!playable_tile(info->map))
        return (printf("playable\n"), 0);
    return (1);
}