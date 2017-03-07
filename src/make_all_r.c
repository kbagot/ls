/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_all_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:24:18 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/07 20:42:05 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

void	make_all_r(char *path, t_data *dir, t_opt *opt)
{
	t_data *save;
	char *tmp;
//	if (path[ft_strlen(path) - 1] != '/')
	tmp = path;	
	path = ft_strjoin(tmp, "/");
	ft_strdel(&tmp);
	dir = make_dir(path, opt);
	save = dir;
//	ft_printf("%s\n", path);
	while (dir)
	{
		if (dir->inode[0] == 'd' && ((dir->name[0] != '.' && opt->a == 0) ||
opt->a == 1) && ft_strcmp(dir->name, ".") != 0 && ft_strcmp(dir->name, "..")
!= 0)
			make_all_r(ft_strjoin(path, dir->name), dir, opt);
		dir = dir->next;
	}
	ft_strdel(&path);
	while (save)
	{
		dir = save;
		save = save->next;
		free(dir->path);
		free(dir->inode);
		free(dir->user);
		free(dir->grp);
		free(dir->name);
		free(dir);
		dir = NULL;
	}
}
