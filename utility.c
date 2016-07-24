/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 17:01:02 by simzam            #+#    #+#             */
/*   Updated: 2016/07/21 17:01:05 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		len(char **s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		rlen(t_room **s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_room		*dictionary(char *key, t_room ***value)
{
	unsigned int		i;

	if (!*value)
		return (0);
	i = 0;
	while ((**value))
	{
		if (!ft_strcmp((*value)[i]->name, key))
			return ((*value)[i]);
		i++;
	}
	return (0);
}

t_room		*dictionary2(int key, t_room ***value)
{
	unsigned int		i;

	if (!*value)
		return (0);
	i = 0;
	while ((**value))
	{
		if ((*value)[i]->is_start == key)
			return ((*value)[i]);
		i++;
	}
	return (0);
}

char	**read_file(int *fd, char *stream)
{
	mode_t		mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	*fd = open ("map.txt", O_RDONLY | O_CREAT, mode);
	read(*fd, stream, 1000000000);
	stream[ft_strlen(stream) + 1] = 0;
	close(*fd);
	return (ft_strsplit(stream, '\n'));
}