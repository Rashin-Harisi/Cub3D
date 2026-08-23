#include "parsing.h"

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

int extract_no(char *line, int i, t_info *info)
{
    if (info->textures.NO != NULL)
        return (printf("Duplicated Texture NO\n"), 0);
    i += 2;
    info->textures.NO = extract_texture(line, &i);
    if (!info->textures.NO)
        return (printf("Invalid Texture NO\n"), 0);
    return (1);
}

int extract_so(char *line, int i, t_info *info)
{
    if (info->textures.SO != NULL)
        return (printf("Duplicated Texture SO\n"), 0);
    i += 2;
    info->textures.SO = extract_texture(line, &i);
    if (!info->textures.SO)
        return (printf("Invalid Texture SO\n"), 0);
    return (1);
}

int extract_we(char *line, int i, t_info *info)
{
    if (info->textures.WE != NULL)
        return (printf("Duplicated Texture WE\n"), 0);
    i += 2;
    info->textures.WE = extract_texture(line, &i);
    if (!info->textures.WE)
        return (printf("Invalid Texture WE\n"), 0);
    return (1);
}

int extract_ea(char *line, int i, t_info *info)
{
    if (info->textures.EA != NULL)
        return (printf("Duplicated Texture EA\n"), 0);
    i += 2;
    info->textures.EA = extract_texture(line, &i);
    if (!info->textures.EA)
        return (printf("Invalid Texture EA\n"), 0);
    return (1);
}

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
    return (1);
}

int reading_map_file(int fd, t_info *info)
{
    char *line;

    line = get_next_line(fd);
    while (line)
    {
        if (!is_empty_line(line))
        {
            if (!extract_info(line, info))
                return (free(line), 0);
        }
        free(line);
        line = get_next_line(fd);
    }
    return (1);
}

int all_textures_found(t_info *info)
{
    if (!info->textures.NO)
        return (printf("Missing Texture NO\n"), 0);
    if (!info->textures.SO)
        return (printf("Missing Texture SO\n"), 0);
    if (!info->textures.WE)
        return (printf("Missing Texture WE\n"), 0);
    if (!info->textures.EA)
        return (printf("Missing Texture EA\n"), 0);
    return (1);
}

void print_textures(t_info *info)
{
    printf("NO: %s\n", info->textures.NO);
    printf("SO: %s\n", info->textures.SO);
    printf("WE: %s\n", info->textures.WE);
    printf("EA: %s\n", info->textures.EA);
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
    if (!all_textures_found(&info))
    {
        free_info(&info);
        return (printf("Error\nInvalid texture configuration\n"), 1);
    }
    print_textures(&info);
    free_info(&info);
    return (0);
}
