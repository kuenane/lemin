/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 17:21:14 by simzam            #+#    #+#             */
/*   Updated: 2016/07/21 17:21:17 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	/* TESTS */

	i = -1;
	while (rlst[++i])
	{
		if ((rlst[i])->is_start)
			printf("This is the start: %s\n", rlst[i]->name);
		if ((rlst[i])->is_end)
			printf("This is the end: %s\n", rlst[i]->name);
		if (rlst[i]->is_end)
			i = 1000;
	}
	i = -1;
	int b;
	while (rlst[++i] && i < rlen(rlst) - 1)
	{
		b = 0;
		printf("Room: %s is linked to:\n", rlst[i]->name);
		while (rlst && rlst[i] && rlst[i]->links[b])
			printf("%s\n", rlst[i]->links[b++]);
	}