/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 16:25:09 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/15 19:59:34 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static void	swap_arg(char **arg, int i, int j)
{
	char *tmp;

	tmp = NULL;
	tmp = arg[j];
	arg[j] = arg[i];
	arg[i] = tmp;
}

static char	**parse_arg(char **arg, t_opt *opt)
{
	struct stat	buf;
	struct stat buf2;
	int			i;
	int			j;

	j = -1;
	i = -1;
	while (arg[++i])
	{
		lstat(arg[i], &buf);
		while (arg[++j])
		{
			lstat(arg[j], &buf2);
			if (arg[j] && ((opt->t == 0 &&
((opt->r == 0 && ft_strcmp(arg[i], arg[j]) < 0) ||
(opt->r == 1 && ft_strcmp(arg[i], arg[j]) > 0))) ||
(opt->t == 1 && ((opt->r == 0 && buf.st_mtime > buf2.st_mtime) ||
(opt->r == 1 && buf.st_mtime < buf2.st_mtime)))))
				swap_arg(arg, i, j);
		}
		j = -1;
	}
	return (arg);
}

static void	print_er(char *arg, t_opt *opt)
{
	if (arg[0])
		perror(ft_strjoin("ft_ls: ", &(ft_strrchr(arg, '/'))[1]));
	else
	{
		perror(ft_strjoin("ft_ls: ", "fts_open"));
		exit(0);
	}
	opt->tricks = 1;
}

static void	print_error(char **arg, t_opt *opt, int dircount, struct stat buf)
{
	int	i;
	DIR	*dr;

	i = 0;
	while (arg[i])
	{
		errno = 0;
		dr = opendir(arg[i]);
		if (errno == 13 || (errno != 20 && errno != 0 && (errno == 2 &&
lstat(arg[i], &buf) == -1)))
			print_er(arg[i], opt);
		if (dr)
			closedir(dr);
		if (errno == 0)
			dircount += 1;
		i++;
	}
	if (dircount > 1)
		opt->tricks = 1;
}

char		**find_error(char **arg, t_opt *opt)
{
	int			i;
	struct stat	buf;
	int			dircount;

	dircount = 0;
	i = 1;
	while (arg[i] && arg[i][0] == '-' && stat(arg[i], &buf) == -1 &&
			lstat(arg[i], &buf) == -1 && parse_opt(arg[i]))
		i++;
	if (arg[i] && (ft_strcmp(&arg[i][0], "--") == 0))
		i++;
	if (opt->r == 1)
	{
		opt->r = 0;
		arg = parse_arg(&arg[i], opt);
		opt->r = 1;
	}
	else
		arg = parse_arg(&arg[i], opt);
	print_error(arg, opt, dircount, buf);
	if (opt->r == 1)
		arg = parse_arg(&arg[0], opt);
	return (arg);
}
