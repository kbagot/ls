/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:56:09 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/24 19:40:14 by kbagot           ###   ########.fr       */
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

static char *rlink(char *path, struct stat buf)
{
	char *linkname;
	ssize_t bufsiz;

	bufsiz = buf.st_size + 1;
	if (buf.st_size == 0)
		bufsiz = PATH_MAX;
	linkname = ft_strnew(bufsiz);
	bufsiz = readlink(path, linkname, bufsiz);
	return (linkname);
}

t_data	*make_line(char *cleanpath, char *path, t_data *fp, char *name)
{
	struct stat		buf;
	struct group	*grp;
	struct passwd	*pwd;

	//if (ent->d_type == 10)
	if (lstat(path, &buf) == -1)
	//		return (NULL);
	//if (ent->d_type != 10)Feb 11 17:40
		if (stat(path, &buf) == -1)
			return (NULL);
	fp = make_link(fp);
	fp->linkname = NULL;
	grp = getgrgid(buf.st_gid);
	pwd = getpwuid(buf.st_uid);
	fp->path = ft_strdup(cleanpath);
	fp->inode = get_inode(buf.st_mode);
	fp->hlinks = buf.st_nlink;
	fp->user = ft_strdup(pwd->pw_name);
	fp->grp = ft_strdup(grp->gr_name);
	fp->bytes = buf.st_size;
	fp->times = buf.st_mtime;
	fp->time = set_time(buf.st_mtime);
	fp->name = ft_strdup(name);
	fp->blocks = buf.st_blocks;
	if (fp->inode[0] == 'l')
		fp->linkname = rlink(path, buf);
	fp->next = NULL;
	return (fp);
}

t_data	*make_list(t_data *fp, t_data *save, t_opt *opt)
{
	t_data *cursor;

	cursor = save;
	if (((opt->r == 1 && opt->t == 1 && save->times > fp->times)
|| (opt->r == 0 && opt->t == 1 && save->times < fp->times)) || (opt->t == 1 && 
save->times == fp->times && ((opt->r == 0 && ft_strcmp(save->name, fp->name) > 0)
 || (opt->r == 1 && ft_strcmp(save->name, fp->name) < 0))) || ((opt->t == 0 && 
 opt->r == 1 && ft_strcmp(save->name, fp->name) < 0) ||
(opt->t == 0 && opt->r == 0 && ft_strcmp(save->name, fp->name) > 0)))
	{
		fp->next = save;
		save = fp;
		return (save);
	}
	while (cursor->next && (((opt->r == 1 && opt->t == 1 && cursor->next->times < 
fp->times) || (opt->r == 0 && opt->t == 1 && cursor->next->times > fp->times)) 
|| (opt->t == 1 && cursor->next->times == fp->times && ((opt->r == 0 &&
ft_strcmp(cursor->next->name, fp->name) <= 0) || (opt->r == 1 && 
ft_strcmp(cursor->next->name, fp->name) >= 0))) || ((opt->t == 0 && opt->r == 0
&& ft_strcmp(cursor->next->name, fp->name) <= 0) || (opt->t == 0 && opt->r == 1 
&& ft_strcmp(cursor->next->name, fp->name) >= 0))))
		cursor = cursor->next;
	fp->next = cursor->next;
	cursor->next = fp;
	return (save);
}
