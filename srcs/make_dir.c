/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:07:38 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/23 18:13:59 by kbagot           ###   ########.fr       */
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

t_data	*make_link(t_data *fp)
{
	if ((fp = (t_data*)malloc(sizeof(t_data))) == NULL)
		return (NULL);
	fp->next = NULL;
	return (fp);
}

t_data		*make_dir(char *path, t_opt *opt)
{
	DIR *dr;
	t_data	*fp;
	t_data	*save;
	t_len	*len;
	struct dirent *ent;
	char *cleanpath;

	save = NULL;
	fp = NULL;
	len = (t_len*)malloc(sizeof(t_len));
	init_t_len(len);
	dr = opendir(path);
	if (errno != 0)
	{

		printf("%s\nls: [GETENDPATH]%s\n\n", path, strerror(errno));
		errno = 0;
		return (NULL);
	}
	printf("error :%d\n", errno);
	while ((ent = readdir(dr)))
	{
		cleanpath = ft_strjoin(path, ent->d_name);
//		if (opt->R == 0)
//			free(path);
		fp = make_link(fp); // malloc maillon
		fp = make_line(cleanpath, fp, ent->d_name, ent);
		if (errno != 0)
		{// to printfile
 			printf("ls: %s: %s\n", ent->d_name, strerror(errno));
			errno = 0;
			//return (NULL);
		}
//	printf("cleanpath :%s\n", cleanpath);
		if (save == NULL)
			save = fp;
		else if (fp)
			save = make_list(fp, save);
//	printf("salut\n");
		if (fp)
		set_len(len, fp);
	}
	if (fp == NULL)
		return (NULL);
	print_file(save, len, opt);
	free(cleanpath);
	closedir(dr);
	if (opt->R == 0)
		while (save)
		{
			fp = save;
			save = save->next;
			free(fp->path);
			free(fp->inode);
			free(fp->user);
			free(fp->grp);
			free(fp->name);
			free(fp);
		}
	return (save);
}

void print_file(t_data *save, t_len *len, t_opt *opt)
{
	printf("PATH %s\n", save->path);
	printf("total %d\n", len->total);
	
	while (save)
	{
		if (opt->l == 1)
		printf("%s  %*d %-*s  %-*s  %*d %s %s", save->inode, len->hlen, save->hlinks, len->ulen, save->user, len->glen, save->grp, len->blen, save->bytes, save->time, save->name);
		else 
			printf("%s", save->name);
		if (save->linkname && opt->l == 1)
			printf(" -> %s", save->linkname);
		printf("\n");
		save = save->next;
	}
		printf("\n");
		free(len);
}
