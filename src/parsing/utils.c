/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:43:47 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 10:47:27 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

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

int all_data_found(t_info *info)
{
	if (!info->textures.NO || !info->textures.SO || !info->textures.WE || !info->textures.EA || !info->floor || !info->ceil)
		return (0);
	return (1);
}

void free_info(t_info *info)
{
	if (!info)
		return;
	free(info->textures.NO);
	free(info->textures.SO);
	free(info->textures.WE);
	free(info->textures.EA);
	free(info->floor);
	free(info->ceil);
	free_array(info->map);
	free_array(info->rect_map);
}

void free_array(char **array)
{
	int i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
