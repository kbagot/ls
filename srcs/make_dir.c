/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:07:38 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/16 20:10:45 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static void	set_len(t_len *len, t_data *fp)
{
	if (ft_strlen(fp->user) > len->ulen)
		len->ulen = ft_strlen(fp->user) + 1;
	if (ft_strlen(fp->grp) > len->glen)
		len->glen = ft_strlen(fp->grp) + 1;
	if (ft_intlen(fp->byte) > len->blen)
		len->blen = ft_strlen(fp->byte) + 1;
}

void		make_dir(char *path, DIR *dr)
{
//	DIR *dr;
	t_data	*fp;
	t_data	*save;
	t_len	*len;
	struct dirent *ent;
	char *cleanpath;

//	dr = opendir(path);
	save = NULL;
	fp = NULL;
	len = (t_len*)malloc(sizeof(t_len));
	init_t_len(len);
	while ((ent = readdir(dr)))
	{
		cleanpath = ft_strjoin("/", ent->d_name);
		cleanpath = ft_strjoin(path, cleanpath);
	//	printf("CHEKC : {%hu}\n", ent->d_reclen);
		fp = make_list(fp);
		if (save == NULL)
			save = fp;
		fp = make_line(cleanpath, fp, ent->d_name);
		set_len(len, fp);
	}
	while (save)
	{
		printf("name :[%s]\n", save->name);
		save = save->next;
	}
}
