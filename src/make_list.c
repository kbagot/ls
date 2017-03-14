/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:56:09 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/14 11:58:20 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

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

static t_data	*make_link(t_data *fp)
{
	if ((fp = (t_data*)malloc(sizeof(t_data))) == NULL)
		return (NULL);
	fp->next = NULL;
	return (fp);
}

static void		make_l(t_data *fp, struct passwd *pwd,
struct group *grp, struct stat buf)
{
	fp->inode = get_inode(buf.st_mode);
	fp->hlinks = buf.st_nlink;
	fp->user = ft_strdup(pwd->pw_name);
	fp->grp = ft_strdup(grp->gr_name);
	fp->times = buf.st_mtime;
	fp->time = set_time(buf.st_mtime);
	fp->blocks = buf.st_blocks;
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
	make_l(fp, pwd, grp, buf);
	fp->path = ft_strdup(cleanpath);
	if (fp->inode[0] == 'c' || fp->inode[0] == 'b')
	{
		fp->bytes = major(buf.st_rdev);
		fp->minor = minor(buf.st_rdev);
	}
	else
		fp->bytes = buf.st_size;
	fp->name = ft_strdup(name);
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
