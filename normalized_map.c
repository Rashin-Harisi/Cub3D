#include "parsing.h"

int normalized_map(t_info *info)
{
    int i;
    int j;
    int len;

    len = 0;
    i = 0;
    info->rect_map = malloc(sizeof(char *) * (info->row + 1));
    if (!info->rect_map)
        return (0);
    info->rect_map[0] = NULL;
    info->rect_map[info->row] = NULL;
    while (i < info->row)
    {
        info->rect_map[i] = malloc(sizeof(char) * (info->max_col + 1));
        if (!info->rect_map[i])
        {
            free_array(info->rect_map);
            info->rect_map = NULL;
            return (0);
        }
        info->rect_map[i + 1] = NULL;
        info->rect_map[i][info->max_col]= '\0';
        j = 0;
        len = ft_strlen(info->map[i]);
        while (j < info->max_col)
        {
            if (j >= len || info->map[i][j] == ' ')
                info->rect_map[i][j] = '1';
            else
                info->rect_map[i][j] = info->map[i][j];
            j++;
        }
        i++;
    }
    return (1);
}