/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedata_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:34:53 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/14 11:40:46 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static void		get_inode_ptwo(int st_mode, char *inode)
{
	inode[1] = (S_IRUSR & st_mode) ? 'r' : '-';
	inode[2] = (S_IWUSR & st_mode) ? 'w' : '-';
	inode[3] = (S_IXUSR & st_mode) ? 'x' : '-';
	if (inode[3] == 'x' && S_ISUID & st_mode)
		inode[3] = 's';
	else if (S_ISUID & st_mode)
		inode[3] = 'S';
	inode[4] = (S_IRGRP & st_mode) ? 'r' : '-';
	inode[5] = (S_IWGRP & st_mode) ? 'w' : '-';
	inode[6] = (S_IXGRP & st_mode) ? 'x' : '-';
	if (inode[6] == 'x' && S_ISGID & st_mode)
		inode[6] = 's';
	else if (S_ISGID & st_mode)
		inode[6] = 'S';
	inode[7] = (S_IROTH & st_mode) ? 'r' : '-';
	inode[8] = (S_IWOTH & st_mode) ? 'w' : '-';
	inode[9] = (S_IXOTH & st_mode) ? 'x' : '-';
	if (inode[9] == 'x' && S_ISVTX & st_mode)
		inode[9] = 't';
	else if (S_ISVTX & st_mode)
		inode[9] = 'T';
}

char			*get_inode(int st_mode)
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
	else if (S_ISSOCK(st_mode))
		inode[0] = 's';
	get_inode_ptwo(st_mode, inode);
	return (inode);
}

static char		*build_time(char *dtime, int st, int ed)
{
	char *ntime;
	char *tmp;
	char *tmpt;

	tmp = ft_strsub(dtime, 4, 7);
	tmpt = ft_strsub(dtime, st, ed);
	ntime = ft_strjoin(tmp, tmpt);
	ft_strdel(&tmp);
	ft_strdel(&tmpt);
	return (ntime);
}

char			*set_time(time_t timef)
{
	time_t	now;
	char	*ntime;
	char	*dtime;

	now = time(NULL);
	dtime = ctime(&timef);
	ntime = NULL;
	if ((now - timef) >= 15778800 || (now - timef) < 0)
		if (ft_strcmp(&dtime[23], " 10000\n") == 0)
			ntime = build_time(dtime, 23, 6);
		else
			ntime = build_time(dtime, 19, 5);
	else
		ntime = ft_strsub(dtime, 4, 12);
	return (ntime);
}
