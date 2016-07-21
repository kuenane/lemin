/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 10:32:56 by simzam            #+#    #+#             */
/*   Updated: 2016/07/21 10:32:59 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_farm		farm;

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
	free(farm.line_alias);
	return (0);
}