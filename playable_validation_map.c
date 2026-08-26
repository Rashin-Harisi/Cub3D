/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playable_validation_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:01:32 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 11:01:37 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

int	is_void_neighbor(int i, int j, char **map)
{
	if (i < 0 || !map[i])
		return (1);
	if (j < 0 || j >= (int)ft_strlen(map[i]))
		return (1);
	if (map[i][j] == ' ')
		return (1);
	return (0);
}

int	is_playable(int i, int j, char **map)
{
	if (map[i][j] == '0' || map[i][j] == 'W'
		|| map[i][j] == 'S' || map[i][j] == 'N'
		|| map[i][j] == 'E')
		return (1);
	return (0);
}

int	playable_tile(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_playable(i, j, map))
			{
				if (is_void_neighbor(i - 1, j, map)
					|| is_void_neighbor(i + 1, j, map)
					|| is_void_neighbor(i, j - 1, map)
					|| is_void_neighbor(i, j + 1, map))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
