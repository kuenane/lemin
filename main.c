/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 10:32:56 by simzam            #+#    #+#             */
/*   Updated: 2016/07/24 10:10:39 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_farm		farm;
	int			i;

	farm.i = -1;
	farm.lines = read_file(&farm.fd, farm.stream);
	farm.line_alias = farm.lines;
	farm.rlst = farm.room_lst;
	while ((farm.lines)[++farm.i])
		ft_memcpy((farm.lines)[farm.i],
			((farm.lines)[farm.i] = ft_strtrim((farm.lines)[farm.i])),
				ft_strlen((farm.lines)[farm.i]));
	farm.ant_amt = ft_atoi((farm.lines)[0]);
	farm.i = -1;
	while (farm.lines && !strchr(*farm.lines, '-') && *(farm.lines++))
		farm.rlst[++farm.i] =  get_rooms_and_coords(&farm.lines, &farm.rooms);
	farm.rlst[rlen(farm.rlst) + 1] = 0;
	get_links(&farm.lines, farm.rlst);

	/* Test for the rooms and respective links */
	i = -1;
	while (farm.rlst[++i])
	{
		if ((farm.rlst[i])->is_start)
		{
			(farm.rlst[i])->num_ants = farm.ant_amt;
			printf("This is the start: %s with %d ant(s)\n", farm.rlst[i]->name, farm.rlst[i]->num_ants);
		}
		if ((farm.rlst[i])->is_end || !(farm.rlst[i])->is_start)
		{
			(farm.rlst[i])->num_ants = 0;
			printf("This is the end: %s\n", farm.rlst[i]->name);
		}
		if (farm.rlst[i]->is_end)
			i = 1000;
	}
	i = -1;
	int b;
	while (farm.rlst[++i] && i < rlen(farm.rlst) - 1)
	{
		b = 0;
		printf("Room: %s is linked to:\n", farm.rlst[i]->name);
		while (farm.rlst && farm.rlst[i] && farm.rlst[i]->links[b])
			printf("%s\n", farm.rlst[i]->links[b++]);
	}
	/* END TEST! */
	printf("The path is: %s\n", find_path(dictionary2(1, &farm.rlst), &farm));
	free(farm.line_alias);
	return (0);
}
