/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:51:59 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 10:52:15 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int extract_floor(char *line, int i, t_info *info)
{
	if (info->floor != NULL)
		return (printf("Duplicated Floor RGB\n"), 0);
	i++;
	info->floor = extract_rgb(line, &i);
	if (!info->floor)
		return (printf("Invalid Floor Data\n"), 0);
	return (1);
}

int extract_ceil(char *line, int i, t_info *info)
{
	if (info->ceil != NULL)
		return (printf("Duplicated Ceiling RGB\n"), 0);
	i++;
	info->ceil = extract_rgb(line, &i);
	if (!info->ceil)
		return (printf("Invalid Ceiling Data\n"), 0);
	return (1);
}

int fill_rgb(char *line, int *i, char *rgb)
{
	int j;
	int status;

	j = 0;
	while (line[*i] && line[*i] != '\n')
	{
		if (line[*i] == ' ' || line[*i] == '\t')
		{
			status = handle_rgb_space(line, i, rgb, j);
			if (status == 2)
				break;
			if (status == 1)
				continue;
			return (0);
		}
		rgb[j++] = line[(*i)++];
	}
	rgb[j] = '\0';
	return (1);
}

int handle_rgb_space(char *line, int *i, char *rgb, int j)
{
	int a;

	a = *i;
	skip_spaces(line, &a);
	if (line[a] == '\n' || line[a] == '\0')
		return (2);
	if (line[a] == ',' || (j > 0 && rgb[j - 1] == ','))
	{
		*i = a;
		return (1);
	}
	return (0);
}

char *extract_rgb(char *line, int *i)
{
	char *rgb;

	skip_spaces(line, i);
	if (line[*i] == '\n' || line[*i] == '\0')
		return (NULL);
	rgb = malloc(sizeof(char) * (ft_strlen(line + *i) + 1));
	if (!rgb)
		return (NULL);
	if (!fill_rgb(line, i, rgb))
		return (free(rgb), NULL);
	return (rgb);
}
