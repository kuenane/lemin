#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct 		s_list_of_rooms
{
	int				x;
	int				y;
	char			*name;
	struct s_list_of_rooms	*next;
}					t_room;

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
		new_room->name = strdup(splitted_specs[0]);
		new_room->x = ft_atoi(splitted_specs[1]);
		new_room->y = ft_atoi(splitted_specs[2]);
	}
	else
	{
		new_room->name = NULL;
		new_room->x = 0;
		new_room->y = 0;
	}
	new_room->next = NULL;
	return (new_room);
}


t_room	*get_rooms_and_coords(char ***lines, t_room **rooms)
{
	if (!strcmp((*lines)[0], "##start"))
	{
		(*lines)++;
		*rooms = new_room((*lines)[0]);
	}
	else if (!ft_strcmp((*lines)[0], "#comment") || !ft_strcmp((*lines)[0], "##comment"))
	{
		(*lines)++;
		*rooms = new_room((*lines)[0]);
	}
	else if (!ft_strcmp((*lines)[0], "##end"))
	{
		(*lines)++;
		*rooms = new_room((*lines)[0]);	
	}
	else
	{
		if ((*rooms)->next != NULL)
		{
			*rooms = new_room((*lines)[0]);
		}
		else
			*rooms =  new_room((*lines)[0]);
	}
	return (*rooms);
}

int		main(int argc, char **argv)
{
	mode_t		mode;
	int 		fd;
	int 		i;
	int			ant_amt;
	t_room		*rooms;
	char		*room_name;
	char 		s[1000000];
	char		**lines;
	char		**alias;

	i = 0;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	fd = open ("map.txt", O_RDONLY | O_CREAT, mode);
	read(fd, s, 1000000000);
	s[strlen(s) + 1] = 0;
	lines = ft_strsplit(s, '\n');
	alias = lines;
	/*Map read test */
	printf("Map:\n");
	while (lines[i])
	{
		ft_memcpy(lines[i], (lines[i] = ft_strtrim(lines[i])), ft_strlen(lines[i]));
		printf("%s\n", lines[i++]);
	}
	/* Map read end */

	/* Ant read test */
	printf("Before cut down: %s\n", lines[0]);
	ant_amt = ft_atoi(lines[0]);
	printf("After cut down: %s\n", lines[0]);
	/* Ant read end */
	while (lines++)
	{
		get_rooms_and_coords(&lines, &rooms);
		printf("Room name: %s,\tx: %d,\ty: %d\n", rooms->name, rooms->x, rooms->y);
//		lines++;
	}
	printf("After cut down2: %s\n", lines[0]);

	free(alias);
	return (0);
}