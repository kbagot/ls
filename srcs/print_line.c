/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:56:09 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/15 20:43:03 by kbagot           ###   ########.fr       */
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

static char	*set_time(char *time)
{
	char *ntime;
//6month !
	ntime = ft_strsub(time, 4, 12);
	return (ntime);	
}

t_data	*make_line(char *path, t_data *fp)
{
	struct stat		*buf;
	struct group	*grp;
	struct passwd	*pwd;

	fp = (t_data*)malloc(sizeof(t_data));
	grp = (struct group*)malloc(sizeof(struct group));
	pwd = (struct passwd*)malloc(sizeof(struct passwd));
	buf = (struct stat*)malloc(sizeof(struct stat));
	if (stat(path, buf) == -1)
		return	(fp);
	grp = getgrgid(buf->st_gid);
	pwd = getpwuid(buf->st_uid);
	fp->inode = get_inode(buf->st_mode);
	fp->hlinks = buf->st_nlink;
	fp->user = ft_strdup(pwd->pw_name);
	fp->grp = ft_strdup(grp->gr_name);
	fp->bytes = buf->st_size;
	fp->time = set_time(ctime(&buf->st_mtime));
	fp->path = ft_strdup(path);
	return (fp);
}

void	print_line(char *path)
{
	t_data *fp;
	time_t *t;

	t = NULL;
	fp = NULL;
	fp = make_line(path, fp);
	printf("%s  %d %s  %s  %d %s %s\n", fp->inode, fp->hlinks, fp->user, fp->grp, fp->bytes, fp->time, fp->path);
}
