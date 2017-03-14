/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_all_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:24:18 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/14 11:32:29 by kbagot           ###   ########.fr       */
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
		tmp_m = dir;
		free_one(tmp_m);
		dir = dir->next;
	}
	ft_strdel(&tmp);
	ft_strdel(&path);
}
