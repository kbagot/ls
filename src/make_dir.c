/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:00:48 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/15 20:21:32 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static int		error_directory(char *path, t_opt *opt)
{
	DIR *dr;

	errno = 0;
	dr = opendir(path);
	if (errno != 0 && opt->up_r == 1)
	{
		if (path[ft_strlen(path) - 1] == '/')
			path[ft_strlen(path) - 1] = '\0';
		if (opt->dpcount == 1 && opt->tricks == 1)
			ft_printf("\n");
		ft_printf("%s:\n", path);
		perror(ft_strjoin("ft_ls: ", &(ft_strrchr(path, '/'))[1]));
		errno = 0;
		if (dr)
			closedir(dr);
		return (-1);
	}
	if (dr)
		closedir(dr);
	return (0);
}

static int		empty_error(char *path, t_opt *opt, t_data *save)
{
	if (opt->tricks == 1 && save)
	{
		if (opt->dpcount == 1)
			ft_printf("\n");
		if (save)
			ft_printf("%.*s:\n", ft_strlen(save->path) - 1, save->path);
		opt->dpcount = 1;
	}
	if (save == NULL)
	{
		if (opt->dpcount == 1)
			ft_printf("\n");
		if (opt->tricks == 1)
			ft_printf("%.*s:\n", (int)ft_strlen(path) - 1, path);
		opt->dpcount = 1;
		return (-1);
	}
	return (0);
}

static t_data	*list_dir(char *path, t_opt *opt, t_data *save, t_len *len)
{
	t_data			*fp;
	DIR				*dr;
	char			*cleanpath;
	struct dirent	*ent;

	errno = 0;
	dr = opendir(path);
	while (dr && (ent = readdir(dr)))
	{
		cleanpath = ft_strjoin(path, ent->d_name);
		if ((opt->a == 0 && ent->d_name[0] != '.') || opt->a == 1)
			fp = make_line(path, cleanpath, fp, ent->d_name);
		if (save == NULL && fp)
			save = fp;
		else if (fp && save)
			save = make_list(fp, save, opt);
		if (fp)
			set_len(len, fp);
		fp = NULL;
		free(cleanpath);
	}
	if (dr)
		closedir(dr);
	return (save);
}

t_data			*make_dir(char *path, t_opt *opt)
{
	t_data	*save;
	t_len	*len;

	save = NULL;
	if (error_directory(path, opt) == -1)
		return (NULL);
	len = (t_len*)malloc(sizeof(t_len));
	init_t_len(len);
	save = list_dir(path, opt, save, len);
	if (empty_error(path, opt, save) == -1)
	{
		free(len);
		len = NULL;
		return (NULL);
	}
	if (opt->l == 1)
		ft_printf("total %d\n", len->total);
	print_file(save, len, opt);
	if (opt->up_r == 0)
		free_land(save);
	return (save);
}
