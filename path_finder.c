/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 10:34:38 by simzam            #+#    #+#             */
/*   Updated: 2016/07/24 10:37:03 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"	

char	*find_path(t_room *start, t_farm *farm)
{
	int				i;
	static char			*path;
	static char			realpath[10000000];

	i = 0;
	if (start)
	{
		while (start && len(start->links))
		{
			path = ft_strdup(start->name);
			path = ft_strjoin(path, "->");
			ft_strcpy(&realpath[ft_strlen(realpath)], path);
			//printf("Current path: %s\n", path);
			//printf("Full path: %s\n", realpath);
			if (start && start->is_end)
			{
				ft_strcat(realpath, start->name);
				realpath[ft_strlen(realpath)] = '\0';
				free(path);
				printf("Found the end\n");
				return (realpath);
			}
			else if (start)
			{
				free (path);
				if (ft_strcmp(start->name,
					dictionary(start->links[i], &farm->rlst)->name))
					find_path(dictionary(start->links[i++],
						&farm->rlst), farm);
			}
		}
	}
	else
	{
		printf("The start is the end, awesome!!\n");
	}
	return (0);
}
