#include <fdf.h>

static int	ft_count(const char *s, char c)
{
	size_t	i;
	int		counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			counter++;
		while ((s[i] != '\0') && (s[i] != c))
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
	while ((str[i] != '\0') && (i < n))
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

int get_height(char *filename)
{
    int		fd;
	int		height;
	char	*line;

	height = 0;
    fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int get_width(char *filename)
{
    int		fd;
	int		width;
	char	*line;

	width = 0;
    fd = open(filename, O_RDONLY);
	get_next_line(fd, &line);
	width = ft_split(line, ' ');
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

void    read_file(char *filename, fdf *data)
{
	int		i;
	int		fd;
	char	*line;

    data->height = get_height(filename);
	data->width = get_width(filename);
	i = 0;
	data->z_matrix = (int **)malloc(sizeof(int *) * (data->height) + 1);
	while (i <= data->height)
	{
		data->z_matrix[i] = (int *)malloc(sizeof(int) * data->width + 1);
		i++;	
	}
	i = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_array(data->z_line, line);
		free(line);
		i++;
	}
	close(fd);
	data->z_matrix[i] = NULL;
}