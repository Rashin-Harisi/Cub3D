#include "cub3d.h"

void print_map(char **map)
{
	int i;

	i = 0;
	if (!map)
	{
		printf("Map is NULL\n");
		return;
	}
	while (map[i])
	{
		printf("|%s|\n", map[i]);
		i++;
	}
	printf("Total rows: %d\n", i);
}

void print_rgb(t_info *info)
{
	printf("Floor RGB: %d,%d,%d\n",
		   info->rgb_floor[0],
		   info->rgb_floor[1],
		   info->rgb_floor[2]);
	printf("Ceiling RGB: %d,%d,%d\n",
		   info->rgb_ceil[0],
		   info->rgb_ceil[1],
		   info->rgb_ceil[2]);
}

void print_textures(t_info *info)
{
	printf("NO: %s\n", info->textures.NO);
	printf("SO: %s\n", info->textures.SO);
	printf("WE: %s\n", info->textures.WE);
	printf("EA: %s\n", info->textures.EA);
}

void print(t_info *info)
{
	print_textures(info);
	print_rgb(info);
	printf("parsed map:\n");
	print_map(info->map);
	printf("normalized map: \n");
	print_map(info->rect_map);
}