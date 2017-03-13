/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_land.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:54:01 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/13 18:29:19 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

void	free_land(t_data *save)
{
	t_data *ddir;

	while (save)
	{
		ddir = save;
		save = save->next;
		ft_strdel(&ddir->path);
		ft_strdel(&ddir->inode);
		ft_strdel(&ddir->user);
		ft_strdel(&ddir->grp);
		ft_strdel(&ddir->time);
		ft_strdel(&ddir->name);
		ft_strdel(&ddir->linkname);
		free(ddir);
		ddir = NULL;
	}
}
