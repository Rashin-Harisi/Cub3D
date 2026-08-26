/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:01:08 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 11:01:12 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

int	last_non_space_character(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len == 0)
		return (0);
	len--;
	while (len >= 0 && (line[len] == ' '))
		len--;
	if (len < 0)
		return (0);
	if (line[len] != '1')
		return (0);
	return (1);
}

int	first_non_space_character(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (0);
	return (1);
}

int	top_bottom_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	wall_validation(t_info *info)
{
	int	i;

	i = 0;
	while (info->map[i])
	{
		if (!first_non_space_character(info->map[i]))
			return (0);
		if (i == 0 || i == (info->row - 1))
		{
			if (!top_bottom_wall(info->map[i]))
				return (0);
		}
		if (!last_non_space_character(info->map[i]))
			return (0);
		i++;
	}
	return (1);
}
