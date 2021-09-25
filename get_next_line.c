/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:38:19 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/25 11:38:11 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi(const char *str)
{
	char		*s;
	int			result;
	int			i;
	short int	sign;

	i = 0;
	sign = 1;
	result = 0;
	s = (char *)str;
	while (s[i] == '\t' || s[i] == '\r' || s[i] == '\n'
		   || s[i] == ' ' || s[i] == '\f' || s[i] == '\v')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{	
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = (result * 10) + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

// size_t	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if (c == 0)
// 		return ((char *)&s[i]);
// 	return (NULL);
// }

// char	*ft_strdup(char *s1)
// {
// 	char	*new;
// 	size_t	counter;
// 	size_t	len;

// 	len = ft_strlen(s1) + 1;
// 	counter = 0;
// 	new = (char *)malloc(sizeof(char) * len);
// 	if (new == NULL)
// 		return (NULL);
// 	while (s1[counter] != '\0')
// 	{
// 		new[counter] = s1[counter];
// 		counter++;
// 	}
// 	new[counter] = '\0';
// 	return (new);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*res;

// 	i = 0;
// 	j = 0;
// 	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!res)
// 		return (NULL);
// 	if (s1)
// 	{
// 		while (s1[i])
// 			res[j++] = s1[i++];
// 	}
// 	i = 0;
// 	if (s2)
// 	{
// 		while (s2[i])
// 			res[j++] = s2[i++];
// 	}
// 	res[j] = '\0';
// 	if (s1)
// 		free(s1);
// 	return (res);
// }

// char	*ft_strcpy(char *dest, char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// int	save_line(char **line, char **box)
// {
// 	char	*position_n;
// 	int		result;

// 	position_n = ft_strchr(*box, '\n');
// 	if (position_n)
// 	{
// 		*position_n = '\0';
// 		*line = ft_strdup(*box);
// 		position_n++;
// 		ft_strcpy(*box, position_n);
// 		result = 1;
// 	}
// 	else
// 	{
// 		*line = ft_strdup(*box);
// 		free(*box);
// 		*box = NULL;
// 		result = 0;
// 	}
// 	return (result);
// }

// int	get_next_line(int fd, char **line)
// {
// 	char		buf[BUFFER_SIZE + 1];
// 	static char	*box;
// 	char		*position_n;
// 	int			file;

// 	if (fd < 0 || !line || BUFFER_SIZE < 1)
// 		return (-1);
// 	file = 1;
// 	while (file > 0)
// 	{
// 		file = read(fd, buf, BUFFER_SIZE);
// 		if (file >= 0)
// 			buf[file] = '\0';
// 		else
// 			return (-1);
// 		box = ft_strjoin(box, buf);
// 		position_n = ft_strchr(box, '\n');
// 		if (position_n)
// 			break ;
// 	}
// 	return (save_line(line, &box));
// }

static void	ft_finish(char *tmp, char **line, char c, int i)
{
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	*line = tmp;
}

int	ft_exit(char **line)
{
	free(*line);
	return (-1);
}

static void	ft_fill(char *tmp, char **line, char c, int *i)
{
	tmp[*i] = (*line)[*i];
	(*i)++;
}

int	get_next_line(int fd, char **line)
{
	int		i;
	int		len;
	int		r;
	char	c;
	char	*tmp;

	r = 0;
	len = 1;
	*line = malloc(len);
	(*line)[0] = 0;
	if (!line)
		return (-1);
	while ((r = read(fd, &c, 1)) && len++ && c != '\n')
	{
		tmp = malloc(len);
		if (!tmp)
			ft_exit(line);
		i = 0;
		while (i < len - 2)
			ft_fill(tmp, line, c, &i);
		ft_finish(tmp, line, c, i);
	}
	return (r);
}
