/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:41:40 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 10:43:22 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

int	count_character(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	**simple_rgb_validation(char *str)
{
	char	**rgb;
	int		i;

	i = 0;
	if (count_character(str, ',') != 2)
		return (NULL);
	rgb = ft_split(str, ',');
	if (!rgb)
		return (NULL);
	while (rgb[i])
	{
		if (rgb[i][0] == '\0')
			return (free_array(rgb), NULL);
		i++;
	}
	if (i != 3)
		return (free_array(rgb), NULL);
	return (rgb);
}

int	*advanced_rgb_validation(char **rgb)
{
	int		i;
	int		j;
	int		*rgb_int;

	i = 0;
	rgb_int = malloc(sizeof(int) * 3);
	if (!rgb_int)
		return (NULL);
	while (i < 3)
	{
		j = 0;
		if (rgb[i][j] == '\0')
			return (free(rgb_int), NULL);
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (free(rgb_int), NULL);
			j++;
		}
		rgb_int[i] = ft_atoi(rgb[i]);
		if (rgb_int[i] < 0 || rgb_int[i] > 255)
			return (free(rgb_int), NULL);
		i++;
	}
	return (rgb_int);
}

int	rgb_check(char *str, int *destination)
{
	char	**rgb;
	int		*rgb_int;
	int		i;

	i = 0;
	rgb = simple_rgb_validation(str);
	if (!rgb)
		return (0);
	rgb_int = advanced_rgb_validation(rgb);
	if (!rgb_int)
		return (free_array(rgb), 0);
	while (i < 3)
	{
		destination[i] = rgb_int[i];
		i++;
	}
	free(rgb_int);
	free_array(rgb);
	return (1);
}

int	rgb_validation(t_info *info)
{
	if (!rgb_check(info->ceil, info->rgb_ceil))
		return (0);
	if (!rgb_check(info->floor, info->rgb_floor))
		return (0);
	return (1);
}
