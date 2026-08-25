#include "parsing.h"
 
int info_validation(t_info *info)
{
    if (!texture_validation(&info->textures))
        return (printf("Textures validation failed\n"), 0);
    if (!rgb_validation(info))
        return (printf("RGB validation failed\n"), 0);
    if (!map_validation(info->map))
        return (printf("Map validation failed\n"), 0);
    return (1);
}