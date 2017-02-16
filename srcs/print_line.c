/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:56:09 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/16 20:10:46 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static char	*get_inode(int st_mode)
{
	char *inode;

	inode = ft_strnew(10);
	if (S_ISREG(st_mode))
		inode[0] = '-';
	else if (S_ISDIR(st_mode))
		inode[0] = 'd';
	else if (S_ISLNK(st_mode))
		inode[0] = 'l';
	else if (S_ISBLK(st_mode))
		inode[0] = 'b';
	else if (S_ISCHR(st_mode))
		inode[0] = 'c';
	else if (S_ISFIFO(st_mode))
		inode[0] = 'i';
	inode[1] = (S_IRUSR & st_mode) ? 'r' : '-';
	inode[2] = (S_IWUSR & st_mode) ? 'w' : '-';
	inode[3] = (S_IXUSR & st_mode) ? 'x' : '-';
	inode[4] = (S_IRGRP & st_mode) ? 'r' : '-';
	inode[5] = (S_IWGRP & st_mode) ? 'w' : '-';
	inode[6] = (S_IXGRP & st_mode) ? 'x' : '-';
	inode[7] = (S_IROTH & st_mode) ? 'r' : '-';
	inode[8] = (S_IWOTH & st_mode) ? 'w' : '-';
	inode[9] = (S_IXOTH & st_mode) ? 'x' : '-';
	return (inode);
}

static char	*set_time(time_t timef)
{
	char *dtime;
	char *ntime;
	time_t now;

	now = time(NULL);
	dtime = ctime(&timef);
	if ((now - timef) >= 15778800)
		ntime = ft_strjoin(ft_strsub(dtime, 4, 7), ft_strsub(dtime, 19, 5));
	else
		ntime = ft_strsub(dtime, 4, 12);
	return (ntime);
}

t_data	*make_line(char *path, t_data *fp, char *name)
{
	struct stat		buf;
	struct group	*grp;
	struct passwd	*pwd;

	if (stat(path, &buf) == -1)
		return (fp);
	grp = getgrgid(buf.st_gid);
	pwd = getpwuid(buf.st_uid);
	fp->inode = get_inode(buf.st_mode);
	fp->hlinks = buf.st_nlink;
	fp->user = ft_strdup(pwd->pw_name);
	fp->grp = ft_strdup(grp->gr_name);
	fp->bytes = buf.st_size;
	fp->time = set_time(buf.st_mtime);
	fp->name = ft_strdup(name);
	fp->blocks = buf.st_blocks;
	fp->next = NULL;
	return (fp);
}

t_data	*make_list(t_data *fp)
{
	t_data *new;

	if (fp == NULL)
	{// SAVE first
		if ((new = (t_data*)malloc(sizeof(t_data))) == NULL)
			return (NULL);
	}
	else
	{
		if ((new = (t_data*)malloc(sizeof(t_data))) == NULL)
			return (NULL);
		fp->next = new;
		new->next = NULL;
	}
	return (new);
}
/*
void	print_line(char *path, char *name, t_data *fp)
{
	static int total = 0;

	fp = make_line(path, fp);
	total += fp->blocks;
	printf("%s  %d %s  %s  %d %s %s\n", fp->inode, fp->hlinks, fp->user, fp->grp, fp->bytes, fp->time, name);
	printf("%d\n", total);
}*/
