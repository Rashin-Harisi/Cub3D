#include "parsing.h"

int	ft_haschar(char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (0);
	return (1);
}

void	ft_moveuntil(char *str, size_t start)
{
	size_t	i;

	i = -1;
	while (str[++i + start])
		str[i] = str[i + start];
	str[i] = 0;
}

int	ft_lenuntil(char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i])
		return (i + 1);
	return (i);
}

char	*ft_dupuntil(char *str, int c)
{
	size_t	i;
	size_t	len;
	char	*new_str;

	i = -1;
	len = ft_lenuntil(str, c);
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	while (++i < len)
		new_str[i] = str[i];
	new_str[len] = 0;
	return (new_str);
}


char	*ft_gnl_linejoin(char *str1, char *str2)
{
	size_t	i;
	size_t	str1_len;
	size_t	str2_len;
	char	*new_str;

	i = -1;
	str1_len = 0;
	str2_len = 0;
	if (str1)
		str1_len = ft_lenuntil(str1, '\0');
	if (!str2)
		return (str1);
	str2_len = ft_lenuntil(str2, '\n');
	new_str = malloc(sizeof(char) * (str1_len + str2_len + 1));
	if (!new_str)
		return (free(str1), NULL);
	while (++i < str1_len)
		new_str[i] = str1[i];
	i = -1;
	while (++i < str2_len)
		new_str[str1_len + i] = str2[i];
	new_str[str1_len + i] = 0;
	free(str1);
	return (new_str);
}

char	*ft_gnl_createline(char *str, long bytes, int fd)
{
	char	*new_str;

	new_str = NULL;
	while (bytes)
	{
		new_str = ft_gnl_linejoin(new_str, str);
		if (!new_str)
			return (NULL);
		if (ft_haschar(new_str, '\n'))
			break ;
		bytes = read(fd, str, BUFFER_SIZE);
		str[bytes] = 0;
	}
	if (bytes <= 0)
		return (new_str);
	ft_moveuntil(str, ft_lenuntil(str, '\n'));
	return (new_str);
}

char	*get_next_line(int fd)
{
	long		bytes;
	static char	buf[1024][BUFFER_SIZE + 1];
	char		*str;

	bytes = 1;
	str = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 0 || BUFFER_SIZE > 10000000)
		return (NULL);
	if (!*buf[fd])
	{
		bytes = read(fd, buf[fd], BUFFER_SIZE);
		if (bytes <= 0)
			return (NULL);
		buf[fd][bytes] = 0;
	}
	if (ft_haschar(buf[fd], '\n'))
	{
		str = ft_dupuntil(buf[fd], '\n');
		if (!str)
			return (NULL);
		ft_moveuntil(buf[fd], ft_lenuntil(str, '\0'));
		return (str);
	}
	return (ft_gnl_createline(buf[fd], bytes, fd));
}
