/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 21:41:26 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/24 16:55:39 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*ans;
	int		len;

	len = ft_strlen_1(s1) + ft_strlen_1(s2);
	if (!(ans = (char *)malloc(len + 1)))
		return (NULL);
	while (*s1)
		*ans++ = *s1++;
	while (*s2)
		*ans++ = *s2++;
	*ans = '\0';
	return (ans - len);
}

int		checkerror(int fd, char **str, char **line)
{
	if (fd < 0 || line == NULL
	|| fd > FOPEN_MAX || read(fd, *str, 0) == -1 || BUFFER_SIZE < 1)
	{
		return (-1);
	}
	if (!*str)
	{
		if (!(*str = ft_strdup("")))
			return (-1);
	}
	return (0);
}

int		check_newl(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*readline(char *str, int fd, int *i)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	char	*temp;

	if (check_newl(str))
		return (str);
	ret = read(fd, buff, BUFFER_SIZE);
	buff[ret] = '\0';
	temp = str;
	str = ft_strjoin(temp, buff);
	free(temp);
	temp = NULL;
	if (ret == 0)
	{
		*i = 0;
		return (str);
	}
	else
	{
		str = readline(str, fd, i);
	}
	return (str);
}

int		get_next_line(int const fd, char **line)
{
	static char	*str;
	int			i;
	int			ret;
	char		*temp;
	
	if (checkerror(fd, &str, line) == -1) // Check all errors in input file and return (-1) ina nany found
		return (-1);
	i = 0;
	ret = 1;
	str = readline(str, fd, &ret);
	while (str[i] != '\n' && str[i])
		i++;
	*line = (i == 0) ? ft_strdup("") : ft_strsub(str, 0, i);
	temp = str;
	str = ft_strsub(temp, i + 1, ft_strlen_1(temp) - i);
	free(temp);
	temp = NULL;
	if (ret == 0 && !check_newl(str))
	{
		free(str);
		str = NULL;
	}
	return (ret);
}