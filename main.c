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
	int				is_start;
	int				is_end;
	int				is_non;
	struct s_list_of_rooms	**next;
}					t_room;

t_room		*dictionary(char *key, t_room ***value)
{
	unsigned int		i;

	i = 0;
	while ((**value))
	{
		if (!ft_strcmp((*value)[i]->name, key))
			return ((*value)[i]);
		i++;
	}
	return (0);
}

t_room	*new_room(char *name)
{
	t_room	*new_room;
	char	**splitted_specs;

	if (!(new_room = (t_room *)ft_memalloc(sizeof(t_room))))
		return (NULL);
	if (name && *name != '\0')
	{
		splitted_specs = ft_strsplit(name, ' ');
		if(!(new_room->name = ft_memalloc(sizeof(char) * ft_strlen(splitted_specs[0]))))
		{
			free(new_room);
			return (NULL);
		}
		new_room->name = ft_strdup(splitted_specs[0]);
		if (splitted_specs && splitted_specs[1])
		{new_room->x = ft_atoi(splitted_specs[1]);
		new_room->y = ft_atoi(splitted_specs[2]);}
	}
	else
	{
		new_room->name = NULL;
		new_room->x = 0;
		new_room->y = 0;
	}
	if (new_room)
		new_room->next = NULL;
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
	else if (!ft_strcmp((*lines)[0], "#comment") || !ft_strcmp((*lines)[0], "##comment") || !ft_strcmp(ft_strsub((*lines)[0], 0, 6), "#anoth"))
	{
		(*lines)++;
		*rooms = new_room((*lines)[0]);
		(*rooms)->is_start = 0;
		(*rooms)->is_end = 0;
		(*rooms)->is_non = 1;
	}
	else if (lines && *lines && **lines && ***lines != EOF)
	{
		*rooms = new_room((*lines)[0]);
	}
	return (*rooms);
}

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

int		main(void)
{
	mode_t		mode;
	int 		fd;
	int 		i;
	unsigned int			ant_amt;
	t_room		*rooms;
	t_room		*room_lst[100000];
	char 		stream[1000000];
	t_room		**rlst;
	char		**lines;
	char		**line_alias;

	i = -1;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	fd = open ("map.txt", O_RDONLY | O_CREAT, mode);
	read(fd, stream, 1000000000);
	stream[ft_strlen(stream) + 1] = 0;
	lines = ft_strsplit(stream, '\n');
	line_alias = lines;
	rlst = room_lst;
	while (lines[++i])
		ft_memcpy(lines[i], (lines[i] = ft_strtrim(lines[i])), ft_strlen(lines[i]));
	ant_amt = ft_atoi(lines[0]);
	i = -1;
	while (lines && !strchr(*lines, '-') && *(lines++))
		rlst[++i] =  get_rooms_and_coords(&lines, &rooms);
	while (lines && (strchr(*lines, '-')) && *(lines++))
	{

		int		i;
		int		k;
		char	**links;
		t_room	*tmp;

		i = -1;
		k = 0;
		while (lines && *lines && **lines &&  (strchr(*lines, '-')))
		{
			++i;
			while (strchr(lines[i], '#'))
			{
				lines++;
				i = 0;
			}
			links = ft_strsplit(lines[i], '-');
			tmp = dictionary(links[0], &rlst);
			tmp->links[len(tmp->links)] = ft_strdup(links[1]);
			//printf("Room: %s\tis linked to room [%s]\n", dictionary(links[0], &rlst)->name, dictionary(links[0], &rlst)->links[0]);
			tmp = dictionary(links[1], &rlst);
			tmp->links[len(tmp->links)] = ft_strdup(links[0]);
			//printf("Room: %s\tis linked to room [%s]\n\n", dictionary(links[1], &rlst)->name, dictionary(links[1], &rlst)->links[0]);
			lines++;
			i = 0;
		}
	//	if (lines && !(strchr(*lines, '-')))
		//	lines++;
		
			printf("seemingly\n");
	}
	printf("seemingly %d\n", i);
	rlst[rlen(rlst) + 1] = 0;
	i = -1;
	while (rlst[++i])
	{
		if ((rlst[i])->is_start)
			printf("This is the start: %s\n", rlst[i]->name);
		if ((rlst[i])->is_end)
			printf("This is the end: %s\n", rlst[i]->name);
	}
	i = -1;
	int b;
	while (rlst[++i])
	{
		b = i;
		//printf("Room name: %s,\tx: %d,\ty: %d\n", rlst[i]->name, rlst[i]->x, rlst[i]->y);
		printf("Room: %s is linked to:\n", rlst[b]->name);
		while (rlst && rlst[b] && rlst[b]->links[i])
			printf("%s\n", rlst[b]->links[i++]);
		i = b;
	}
	printf("dictionary: %s\n", (dictionary("6", &rlst))->name);
	free(line_alias);
	return (0);
}