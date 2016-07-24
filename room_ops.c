/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 17:05:21 by simzam            #+#    #+#             */
/*   Updated: 2016/07/21 17:05:22 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*new_room(char *name)
{
	t_room	*new_room;
	char	**splitted_specs;

	splitted_specs = NULL;
	if (!(new_room = (t_room *)ft_memalloc(sizeof(t_room))))
		return (NULL);
	if (name && *name != '\0')
	{
		splitted_specs = ft_strsplit(name, ' ');
		if(!(new_room->name = ft_strdup(splitted_specs[0])))
		{
			free(new_room);
			return (NULL);
		}
		if (splitted_specs && (splitted_specs + 1))
		{
			new_room->x = ft_atoi(splitted_specs[1]);
			new_room->y = ft_atoi(splitted_specs[2]);
		}
	}
	else
	{
		new_room->name = NULL;
		new_room->x = 0;
		new_room->y = 0;
	}
	if (new_room)
		new_room->next = NULL;
	free(*splitted_specs);
	return (new_room);
}

t_room	*get_rooms_and_coords(char ***lines, t_room **rooms)
{
	if (lines && *lines && ***lines && ft_strchr((*lines)[0], '-'))
	{
		return (*rooms)++;
	}
	else if (!strcmp((*lines)[0], "##start"))
	{
		(*lines)++;
		*rooms = new_room((*lines)[0]);
		(*rooms)->is_start = 1;
		(*rooms)->is_end = 0;
	}
	else if (!strcmp((*lines)[0], "##end"))
	{
		(*lines)++;
		*rooms = new_room((*lines)[0]);
		(*rooms)->is_start = 0;
		(*rooms)->is_end = 1;
	}
	else if (***lines == '#')
	{
		(*lines)++;
		*rooms = new_room((*lines)[0]);
		(*rooms)->is_start = 0;
		(*rooms)->is_end = 0;
	}
	else if (lines && *lines && **lines && ***lines != EOF)
	{
		*rooms = new_room((*lines)[0]);
		(*rooms)->is_start = 0;
		(*rooms)->is_end = 0;
	}
	return (*rooms);
}

int		contains(t_room *lines, char *line)
{
	unsigned int	i;

	i = 0;
	while (lines && (lines->links[i]))
	{
		if (ft_strcmp(lines->links[i++], line) == 0)
			return (42);
	}
	return (-42);
}

void	get_links(char ***lines, t_room **rlst)
{
	char	**links;
	t_room	*tmp;
	int		i;

	i = 0;
	while (lines && *lines && **lines && (strchr(**lines, '-')))
	{
		i = 0;
		while (lines && ***lines == '#')
			(*lines)++;
		links = ft_strsplit(**lines, '-');
		tmp = dictionary(links[0], &rlst);
		(tmp->links)[len(tmp->links)] = ft_strdup(links[1]);
		if (tmp && contains(tmp, links[1]))
			free((tmp->links)[len(tmp->links)]);
		tmp = dictionary(links[1], &rlst);
		(tmp->links)[len(tmp->links)] = ft_strdup(links[1]);
		if (tmp && contains(tmp, links[0]))
			free((tmp->links)[len(tmp->links)]);
		(*lines)++;
		free(links);
	}
	tmp->links[len(tmp->links)] = 0;
}