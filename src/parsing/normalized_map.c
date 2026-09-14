/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 normalized_map.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: rabdolho <rabdolho@student.42vienna.c		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/08/26 10:19:29 by rabdolho		   #+#	  #+#			  */
/*	 Updated: 2026/08/26 10:24:29 by rabdolho		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "cub3d.h"

static int fill_rect_map_row(t_info *info, int i)
{
	int j;
	int len;

	j = 0;
	len = 0;
	info->rect_map[i] = malloc(sizeof(char) * (info->max_col + 1));
	if (!info->rect_map[i])
	{
		free_array(info->rect_map);
		info->rect_map = NULL;
		return (0);
	}
	info->rect_map[i + 1] = NULL;
	info->rect_map[i][info->max_col] = '\0';
	len = ft_strlen(info->map[i]);
	while (j < info->max_col)
	{
		if (j >= len || info->map[i][j] == ' ')
			info->rect_map[i][j] = '1';
		else
			info->rect_map[i][j] = info->map[i][j];
		j++;
	}
	return (1);
}

int normalized_map(t_info *info)
{
	int i;

	i = 0;
	info->rect_map = malloc(sizeof(char *) * (info->row + 1));
	if (!info->rect_map)
		return (0);
	info->rect_map[0] = NULL;
	info->rect_map[info->row] = NULL;
	while (i < info->row)
	{
		if (!fill_rect_map_row(info, i))
		{
			free_array(info->rect_map);
			info->rect_map = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}
