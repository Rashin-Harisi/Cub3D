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

int map_validation(char **map)
{}