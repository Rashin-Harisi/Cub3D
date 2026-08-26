/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 extract_utils.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: rabdolho <rabdolho@student.42vienna.c		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/08/26 11:09:57 by rabdolho		   #+#	  #+#			  */
/*	 Updated: 2026/08/26 11:10:01 by rabdolho		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "parsing.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

char	*copy_path(char *line, int start, int end)
{
	char	*path;
	int		i;

	path = malloc(sizeof(char) * (end - start + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (start < end)
		path[i++] = line[start++];
	path[i] = '\0';
	return (path);
}

char	*extract_texture(char *line, int *i)
{
	char	*path;
	int		j;
	int		start;

	j = 0;
	skip_spaces(line, i);
	if (line[*i] == '\n' || line[*i] == '\0')
		return (NULL);
	start = (*i);
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n')
		(*i)++;
	path = copy_path(line, start, *i);
	if (!path)
		return (NULL);
	skip_spaces(line, i);
	if (line[*i] != '\n' && line[*i] != '\0')
		return (free(path), NULL);
	return (path);
}
