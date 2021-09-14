#include <fdf.h>

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	char	*new;
	size_t	counter;
	size_t	len;

	len = ft_strlen(s1) + 1;
	counter = 0;
	new = (char *)malloc(sizeof(char) * len);
	if (new == NULL)
		return (NULL);
	while (s1[counter] != '\0')
	{
		new[counter] = s1[counter];
		counter++;
	}
	new[counter] = '\0';
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	if (s1)
	{
		while (s1[i])
			res[j++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			res[j++] = s2[i++];
	}
	res[j] = '\0';
	if (s1)
		free(s1);
	return (res);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	save_line(char **line, char **box)
{
	char	*position_n;
	int		result;

	position_n = ft_strchr(*box, '\n');
	if (position_n)
	{
		*position_n = '\0';
		*line = ft_strdup(*box);
		position_n++;
		ft_strcpy(*box, position_n);
		result = 1;
	}
	else
	{
		*line = ft_strdup(*box);
		free(*box);
		*box = NULL;
		result = 0;
	}
	return (result);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*box;
	char		*position_n;
	int			file;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	file = 1;
	while (file > 0)
	{
		file = read(fd, buf, BUFFER_SIZE);
		if (file >= 0)
			buf[file] = '\0';
		else
			return (-1);
		box = ft_strjoin(box, buf);
		position_n = ft_strchr(box, '\n');
		if (position_n)
			break ;
	}
	return (save_line(line, &box));
}