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

static void	ft_finish(char *tmp, char **line, char c, int i)
{
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	*line = tmp;
}

static int	ft_exit(char **line)
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
