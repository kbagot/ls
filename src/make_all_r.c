/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_all_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:24:18 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/13 18:29:38 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

void	make_all_r(char *path, t_data *dir, t_opt *opt)
{
	char	*tmp;
	t_data	*tmp_m;

	tmp = NULL;
	if (path[ft_strlen(path) - 1] != '/')
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strdup(path);
	dir = make_dir(tmp, opt);
	while (dir)
	{
		if (dir->inode[0] == 'd' && ((dir->name[0] != '.' && opt->a == 0) || 
					opt->a == 1) && ft_strcmp(dir->name, ".") != 0 && 
				ft_strcmp(dir->name, "..") != 0)
			make_all_r(ft_strjoin(tmp, dir->name), dir, opt);
		ft_strdel(&dir->path);
		ft_strdel(&dir->inode);
		ft_strdel(&dir->user);
		ft_strdel(&dir->grp);
		ft_strdel(&dir->time);
		ft_strdel(&dir->name);
		ft_strdel(&dir->linkname);
		tmp_m = dir;
		dir = dir->next;
		free(tmp_m);
		tmp_m = NULL;
	}
//	printf("m1\n");
	ft_strdel(&tmp);
//	printf("m2\n");	
	ft_strdel(&path);
//	printf("m3\n");
}
