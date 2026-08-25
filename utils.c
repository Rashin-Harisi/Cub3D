#include "parsing.h"

int file_extension_check(char *filename)
{
    int len;

    if (!filename)
        return (0);
    len = ft_strlen(filename);
    if (len < 5)
        return (0);
    if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
        return (0);
    return (1);
}

int is_empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
            return (0);
        i++;
    }
    return (1);
}

char    *extract_texture(char *line, int *i)
{
    char    *path;
    int     j;
    int     start;

    j = 0;
    while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
    if (line[*i] == '\n' || line[*i] == '\0')
		return (NULL);
    start = (*i);
    while (line[*i]	&& line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n')
	    (*i)++;
    path = malloc(sizeof(char) * ((*i - start) + 1));
    if (!path)
        return (NULL);
    while (start < *i)
    {
        path[j] = line[start];
        start++;
        j++;
    }
    path[j] = '\0';
    while (line[*i] == ' ' || line[*i] == '\t')
	    (*i)++;
    if (line[*i] != '\n' && line[*i] != '\0')
	    return (free(path),NULL);
    return (path);
}

char    *extract_rgb(char *line, int *i)
{
    char    *rgb;
    int     j;
    int     a;

    j = 0;
    while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
    if (line[*i] == '\n' || line[*i] == '\0')
		return (NULL);
    rgb = malloc(sizeof(char) * (ft_strlen(line + *i) + 1));
    if (!rgb)
        return (NULL);
    while (line[*i]	&& line[*i] != '\n')
    {
        if (line[*i] == ' ' || line[*i] == '\t')
        {
            a = *i;
            while (line[a] == ' ' || line[a] == '\t')
                a++;
            if (line[a] == '\n' || line[a] == '\0')
                break;
            if (line[a] == ',')
            {
                *i = a;
                continue;
            }
            if (j > 0 && rgb[j - 1] == ',')
            {
                *i = a;
                continue;
            }
            return (free(rgb), NULL);
        }
        rgb[j] = line[*i];
        j++;
        (*i)++;
    }
    rgb[j] = '\0';
    return (rgb);
}

int all_data_found(t_info *info)
{
    if (!info->textures.NO
        || !info->textures.SO
        || !info->textures.WE
        || !info->textures.EA
        || !info->floor
        || !info->ceil)
        return (0);
    return (1);
}

void free_info(t_info *info)
{
    free(info->textures.NO);
    free(info->textures.SO);
    free(info->textures.WE);
    free(info->textures.EA);
    free(info->floor);
    free(info->ceil);
    // later free map
}

void free_array(char **array)
{
    int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}