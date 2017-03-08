/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:56:09 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/08 20:57:13 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static char		*get_inode(int st_mode)
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
	if (inode [3] == 'x' && S_ISUID & st_mode)
		inode [3] = 's';
	else if (S_ISUID & st_mode)
		inode [3] = 'S';
	inode[4] = (S_IRGRP & st_mode) ? 'r' : '-';
	inode[5] = (S_IWGRP & st_mode) ? 'w' : '-';
	inode[6] = (S_IXGRP & st_mode) ? 'x' : '-';
	if (inode[6] == 'x' && S_ISGID & st_mode)
		inode [6] = 's';
	else if (S_ISGID & st_mode)
		inode [6] = 'S';
	inode[7] = (S_IROTH & st_mode) ? 'r' : '-';
	inode[8] = (S_IWOTH & st_mode) ? 'w' : '-';
	inode[9] = (S_IXOTH & st_mode) ? 'x' : '-';
	if (inode[9] == 'x' && S_ISVTX & st_mode)
		inode [9] = 't';
	else if (S_ISVTX & st_mode)
		inode [9] = 'T';
	return (inode);
}

static char		*set_time(time_t timef)
{
	time_t	now;
	char	*ntime;
	char	*dtime;

	now = time(NULL);
	dtime = ctime(&timef);
	ntime = NULL;
	if ((now - timef) >= 15778800 || (now - timef) < 0)
//	{
		if (ft_strcmp(&dtime[23], " 10000\n") == 0)
			ntime = ft_strjoin(ft_strsub(dtime, 4, 7), ft_strsub(dtime, 23, 6));
		else
			ntime = ft_strjoin(ft_strsub(dtime, 4, 7), ft_strsub(dtime, 19, 5));
//	}
	else
		ntime = ft_strsub(dtime, 4, 12);
	return (ntime);
}

static char		*rlink(char *path, struct stat buf)
{
	char	*linkname;
	ssize_t	bufsiz;

	bufsiz = buf.st_size + 1;
	if (buf.st_size == 0)
		bufsiz = PATH_MAX;
	linkname = ft_strnew(bufsiz);
	bufsiz = readlink(path, linkname, bufsiz);
	return (linkname);
}

t_data			*make_line(char *cleanpath, char *path, t_data *fp, char *name)
{
	struct stat		buf;
	struct group	*grp;
	struct passwd	*pwd;

	if (lstat(path, &buf) == -1)
		if (stat(path, &buf) == -1)
			return (NULL);
	fp = make_link(fp);
	fp->linkname = NULL;
	grp = getgrgid(buf.st_gid);
	pwd = getpwuid(buf.st_uid);
	fp->inode = get_inode(buf.st_mode);
	fp->path = ft_strdup(cleanpath);
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

t_data			*make_list(t_data *fp, t_data *save, t_opt *opt)
{
	t_data *crs;

	crs = save;
	if (((opt->r == 1 && opt->t == 1 && save->times > fp->times) ||
(opt->r == 0 && opt->t == 1 && save->times < fp->times)) || (opt->t == 1 &&
save->times == fp->times && ((opt->r == 0 && ft_strcmp(save->name, fp->name) >
0) || (opt->r == 1 && ft_strcmp(save->name, fp->name) < 0))) || ((opt->t == 0 &&
opt->r == 1 && ft_strcmp(save->name, fp->name) < 0) ||
(opt->t == 0 && opt->r == 0 && ft_strcmp(save->name, fp->name) > 0)))
	{
		fp->next = save;
		save = fp;
		return (save);
	}
	while (crs->next && (((opt->r == 1 && opt->t == 1 && crs->next->times <
fp->times) || (opt->r == 0 && opt->t == 1 && crs->next->times > fp->times)) ||
(opt->t == 1 && crs->next->times == fp->times && ((opt->r == 0 &&
ft_strcmp(crs->next->name, fp->name) <= 0) || (opt->r == 1 &&
ft_strcmp(crs->next->name, fp->name) >= 0))) || ((opt->t == 0 && opt->r == 0 &&
ft_strcmp(crs->next->name, fp->name) <= 0) || (opt->t == 0 && opt->r == 1 &&
ft_strcmp(crs->next->name, fp->name) >= 0))))
		crs = crs->next;
	fp->next = crs->next;
	crs->next = fp;
	return (save);
}
