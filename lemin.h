/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 17:01:39 by simzam            #+#    #+#             */
/*   Updated: 2016/07/21 17:01:41 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct 		s_list_of_rooms
{
	int				x;
	int				y;
	char			*name;
	char			*links[10000];
	int				num_ants;
	int				is_start;
	int				is_end;
	struct s_list_of_rooms	**next;
}					t_room;

typedef struct  	s_the_farm
{
	int				fd;
	int				i;
	unsigned int	ant_amt;
	t_room			*rooms;
	t_room			*room_lst[100000];
	char 			stream[1000000];
	t_room			**rlst;
	char			**lines;
	char			**line_alias;
}					t_farm;

t_room				*dictionary(char *key, t_room ***value);
t_room				*dictionary2(int key, t_room ***value);
t_room				*new_room(char *name);
t_room				*get_rooms_and_coords(char ***lines, t_room **rooms);
void				get_links(char ***lines, t_room **rlst);
char				*find_path(t_room *start, t_farm *farm);
char				**read_file(int *fd, char *stream);
int					len(char **s);
int					rlen(t_room **s);

#endif