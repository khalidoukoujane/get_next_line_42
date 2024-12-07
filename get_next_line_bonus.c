/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoukouj <khoukouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:10:25 by khoukouj          #+#    #+#             */
/*   Updated: 2024/11/20 15:37:08 by khoukouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(char *str, int fd)
{
	char	*buff;
	char	*tmp;
	int		b_read;

	b_read = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(str), NULL);
	while (b_read != 0)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read == -1)
			return (free(buff), free(str), NULL);
		buff[b_read] = '\0';
		tmp = ft_strjoin(str, buff);
		if (!tmp)
			return (free(buff), free(str), NULL);
		free(str);
		str = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

static char	*extract_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_substr(str, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*update_buff(char *str)
{
	int		i;
	char	*new_buff;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	i++;
	new_buff = ft_substr(str, i, ft_strlen(str) - i);
	if (!new_buff)
		return (free(str), NULL);
	free(str);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	static char	*s_str[OPEN_MAX];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0
		|| BUFFER_SIZE >= INT_MAX || read(fd, NULL, 0) == -1)
		return (free(s_str[fd]), s_str[fd] = NULL);
	if (!ft_strchr(s_str[fd], '\n'))
		s_str[fd] = read_line(s_str[fd], fd);
	if (!s_str[fd] || *s_str[fd] == 0)
		return (free(s_str[fd]), s_str[fd] = NULL);
	line = extract_line(s_str[fd]);
	if (!line)
		return (free(s_str[fd]), s_str[fd] = NULL);
	s_str[fd] = update_buff(s_str[fd]);
	return (line);
}
