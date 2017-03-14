/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:43:33 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/14 19:38:14 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static void		file_m(t_data *dir, t_len *len, t_opt *opt)
{
	opt->noarg = 1;
	opt->tricks = 1;
	set_len(len, dir);
	errno = 0;
}

static t_len	*init_len(t_len *len)
{
	len = (t_len*)malloc(sizeof(t_len));
	init_t_len(len);
	errno = 0;
	return (len);
}

static t_data	*list(t_data *save, t_data *dir, t_opt *opt)
{
	if (save == NULL)
		save = dir;
	else if (dir)
		save = make_list(dir, save, opt);
	return (save);
}

void			file_maker(char **argv, t_opt *opt, t_data *dir, int i)
{
	struct stat	buf;
	DIR			*dr;
	t_data		*save;
	t_len		*len;

	save = NULL;
	len = NULL;
	while (argv[++i])
	{
		errno = 0;
		dr = opendir(argv[i]);
		lstat(argv[i], &buf);
		if (errno == 20 || (errno == 2 && lstat(argv[i], &buf) != -1 && S_ISLNK
(buf.st_mode) == 1) || (errno == 0 && S_ISLNK(buf.st_mode) == 1 && opt->l == 1))
		{
			len = init_len(len);
			dir = make_line(argv[i], argv[i], dir, argv[i]);
			save = list(save, dir, opt);
			file_m(dir, len, opt);
		}
		if (dr)
			closedir(dr);
	}
	if (save)
		print_file(save, len, opt);
}

void			dir_maker(char **argv, t_opt *opt, t_data *dir, int i)
{
	struct stat	buf;
	DIR			*dr;

	while (argv[++i])
	{
		errno = 0;
		dr = opendir(argv[i]);
		lstat(argv[i], &buf);
		if ((errno == 0 && S_ISLNK(buf.st_mode) == 0) || (errno == 0 &&
S_ISLNK(buf.st_mode) == 1 && opt->l == 0))
		{
			opt->noarg = 1;
			if (opt->up_r == 0)
				dir = make_dir(ft_strjoin(argv[i], "/"), opt);
			else if (opt->up_r == 1)
				make_all_r(ft_strdup(argv[i]), dir, opt);
		}
		if (dr)
			closedir(dr);
	}
}
