/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:38:26 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/15 19:06:00 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_count(const char *s, char c)
{
	size_t	i;
	int		counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			counter++;
		while ((s[i]) && (s[i] != c))
			i++;
	}
	return (counter);
}

static char	*ft_copy(const char *str, size_t n)
{
	char	*new;
	size_t	i;

	new = (char *)malloc(sizeof(char) * (n + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while ((str[i]) && (i < n))
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	place;
	int		word;

	if (s == NULL)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		place = i;
		while ((s[i] != '\0') && (s[i] != c))
			i++;
		if (place < i)
			new[word++] = ft_copy(s + place, i - place);
	}
	new[word] = NULL;
	return (new);
}

int	get_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (!fd)
	{
		printf("Eroorrsr");
		exit(1);
	}
	
	while (get_next_line(fd, &line) > 0)
	{
		height++;
		free(line);
	}
	free(line);
	close(fd);
	return (height);
}

int	get_width(char *filename)
{
	int		fd;
	int		width;
	char	*line;

	width = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		width = ft_count(line, ' ');
		free(line);
	}
	free(line);
	close(fd);
	return (width);
}

void	ft_array(int *z_line, char *line)
{
	int		i;
	char	**nums;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

void	read_file(char *filename, fdf *data)
{
	int		i;
	int		fd;
	char	*line;

	data->height = get_height(filename);
	data->width = get_width(filename);
	i = 0;
	data->z_matrix = (int **)malloc(sizeof(int *) * data->height);
	while (i < data->height)
	{
		data->z_matrix[i] = (int *)malloc(sizeof(int) * data->width);
		i++;
	}
	i = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_array(data->z_matrix[i], line);
		free(line);
		i++;
	}
	free(line);
	close(fd);
}
