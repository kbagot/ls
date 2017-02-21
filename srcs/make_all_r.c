/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_all_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:24:18 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/21 20:53:49 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

void	make_all_r(char *path, DIR *dr, t_opt *opt)
{
	struct dirent *ent;
	DIR *ndr;

	ndr = opendir(path);
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	make_dir(path, opt);
	while ((ent = readdir(ndr)))
	{
		if (ent->d_type == 4 && ent->d_name[0] != '.')
		{
			make_all_r(ft_strjoin(path, ent->d_name), dr, opt);
		}
	}
}
