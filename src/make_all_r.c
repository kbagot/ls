/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_all_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:24:18 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/14 19:09:11 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

void	make_all_r(char *path, t_data *dir, t_opt *opt)
{
	char	*tmp;
	t_data	*tmp_m;

	if (ft_strlen(path) - 1 == 0 && path[0] == '/')
		tmp = ft_strdup(path);
	else
		tmp = ft_strjoin(path, "/");
	dir = make_dir(tmp, opt);
	tmp_m = dir;
	while (dir)
	{
		if (dir->inode[0] == 'd' && ((dir->name[0] != '.' && opt->a == 0) ||
					opt->a == 1) && ft_strcmp(dir->name, ".") != 0 &&
				ft_strcmp(dir->name, "..") != 0)
			make_all_r(ft_strjoin(tmp, dir->name), dir, opt);
		dir = dir->next;
	}
	free_land(tmp_m);
	ft_strdel(&tmp);
	ft_strdel(&path);
}
