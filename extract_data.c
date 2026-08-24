#include "parsing.h"


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

int extract_floor(char *line, int i, t_info *info)
{
    if (info->floor != NULL)
        return (printf("Duplicated Floor RGB\n"), 0);
    i++;
    info->floor = extract_texture(line, &i);
    if (!info->floor)
        return (printf("Invalid Floor Data\n"), 0);
    return (1);
}

int extract_ceil(char *line, int i, t_info *info)
{
    if (info->ceil != NULL)
        return (printf("Duplicated Ceiling RGB\n"), 0);
    i++;
    info->ceil = extract_texture(line, &i);
    if (!info->ceil)
        return (printf("Invalid Ceiling Data\n"), 0);
    return (1);
}