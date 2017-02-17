/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:07:38 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/17 18:29:19 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static void	init_t_len(t_len *len)
{
	len->hlen = 0;
	len->ulen = 0;
	len->glen = 0;
	len->blen = 0;
	len->total = 0;
}

static int	ft_intlen(int nb)
{
	int len;

	len = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static void	set_len(t_len *len, t_data *fp)
{
	if (ft_intlen(fp->hlinks) > len->hlen)
		len->hlen = ft_intlen(fp->hlinks);
	if ((int)ft_strlen(fp->user) > len->ulen)
		len->ulen = ft_strlen(fp->user);
	if ((int)ft_strlen(fp->grp) > len->glen)
		len->glen = ft_strlen(fp->grp);
	if (ft_intlen(fp->bytes) > len->blen)
		len->blen = ft_intlen(fp->bytes);
	len->total += fp->blocks;
}

void		make_dir(char *path, DIR *dr, t_opt *opt)
{
	t_data	*fp;
	t_data	*save;
	t_len	*len;
	struct dirent *ent;
	char *cleanpath;

	save = NULL;
	fp = NULL;
	len = (t_len*)malloc(sizeof(t_len));
	init_t_len(len);
	while ((ent = readdir(dr)))
	{
		cleanpath = ft_strjoin("/", ent->d_name);
		cleanpath = ft_strjoin(path, cleanpath);
		fp = make_list(fp);
		if (save == NULL)
			save = fp;
		fp = make_line(cleanpath, fp, ent->d_name);
		//fct trie goodplace;
		set_len(len, fp);
	}
//
//
	printf("total %d\n", len->total);
	while (save)
	{
		printf("%s  %*d %*s  %*s  %*d %s %s\n", save->inode, len->hlen, save->hlinks, len->ulen, save->user, len->glen, save->grp, len->blen, save->bytes, save->time, save->name);
//		printf("name :[%s]\n", save->name);
		save = save->next;
	}
}
