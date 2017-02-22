/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_all_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:24:18 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/22 18:49:39 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

void	make_all_r(char *path, DIR *dr, t_opt *opt)
{
	struct dirent *ent;

	if (path[ft_strlen(path) - 1] != '/')
	path = ft_strjoin(path, "/");
	make_dir(path, opt);
//	if (!dr)
	dr = opendir(path);
	while ((ent = readdir(dr)))
	{
		if (ent->d_type == 4 && ent->d_name[0] != '.'/*ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0*/)
		{
//	free (path);
//	printf("salut\n");
			make_all_r(ft_strjoin(path, ent->d_name), dr, opt);
		}
	}
	closedir(dr);
	dr = NULL;
	printf("%s\n", path);
}
