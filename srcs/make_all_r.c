/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_all_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:24:18 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/24 20:33:13 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"
/*
static t_dir	*malloc_dir(t_dir *dir)
{
	if ((dir = (t_dir*)malloc(sizeof(t_dir)) == NULL)
		return (NULL);
	dir->next = NULL;	
	return (dir);
}

static t_dir	*make_list(char *path, t_dir *save)	
{
	t_dir *cursor;

	cursor = save;
	if (ft_strcmp(save->path, path) > 0)
	{
		fp->next = save;
		save = fp;
		return (save);
	}
	while (cursor->next && ft_strcmp(cursor->next->name, fp->name) <= 0)
		cursor = cursor->next;
	fp->next = cursor->next;
	cursor->next = fp;
	return (save);
}

static t_dir	*make_list_dirR(char *path)
{
	t_dir *save;
	DIR *dr;

	save = NULL;
	dr = opendir(path);
	while (ent = readdir(dr))
	{
		save = malloc_dir(save);
		path = ft_strjoin(path, ent->d_name);
		save = make_list;
	}
	return (save);
}
*/

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
//	printf("%s\n", path);
	while (dir)
	{
		if (dir->inode[0] == 'd' && dir->name[0] != '.'/*ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0*/)
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
