/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:44:39 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/07 20:42:09 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"
/*
t_error		*make_error_list(t_error *error, char *path)
{
	t_error *find;
	t_error	*mnew;

	find = error;
	if (find == NULL)
	{
		if ((find = (t_error*)malloc(sizeof(t_error))) == NULL)
			return (NULL);
		find->ename = ft_strdup(path);
		find->next = NULL;
		error = find;
	}
	else
	{
		if ((mnew = (t_error*)malloc(sizeof(t_error))) == NULL)
			return (NULL);
		mnew->ename = ft_strdup(path);
		if (ft_strcmp(find->ename, path) > 0)
		{
			mnew->next = find;
			error = mnew;
			return (error);
		}
			while (find->next && (ft_strcmp(find->next->ename, path)) <= 0)
				find = find->next;
			mnew->next = find->next;
			find->next = mnew;
	}
	return (error);
}
*/
static int	parse_opt(char *opt)
{
	int	j;
	char *val;

	j = 1;
	val = "-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
	if (opt[0] == '-')
		while (opt[j])
		{
			if (ft_strchr(val, opt[j]) == NULL)
			{
				ft_putstr_fd("ls: illegal option -- ", 2);
				ft_putchar_fd(opt[j], 2);
				ft_putchar_fd('\n', 2);
				ft_putstr_fd("usage: ls [", 2);
			//	ft_putchar_fd('-', 2);
				ft_putstr_fd(val, 2);
				ft_putstr_fd("] [file ...]\n", 2);
				errno = 2;
				return (0);
			}
			j++;
		}
	return (1);
}

static void		init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->tricks = 0;
	opt->dpcount = 0;
}

static t_opt	*stock_opt(t_opt *opt, char **arg)
{
	DIR *dr;
	int i;
	struct stat		buf;

	i = 1;
	dr = opendir(arg[i]);
	while (arg[i] && arg[i][0] == '-' && parse_opt(arg[i]) && errno != 0 &&
((lstat(arg[i], &buf) == -1) || (stat(arg[i], &buf) == -1)))
	{
		if (ft_strchr(arg[i], 'l'))
			opt->l = 1;
		if (ft_strchr(arg[i], 'R'))
			opt->R = 1;
		if  (ft_strchr(arg[i], 'a'))
			opt->a = 1;
		if (ft_strchr(arg[i], 'r'))
			opt->r = 1;
		if (ft_strchr(arg[i], 't'))
			opt->t = 1;
		i++;
		if (dr)
		closedir(dr);
		errno = 0;
		dr = opendir(arg[i]);
	}
//	printf("%d\n", errno);
	return (opt);
}

static char **parse_arg(char **arg, t_opt *opt)
{
	int i;
	int j;
	char *tmp;

	j = 0;
	i = 0;
	tmp = NULL;
	while (arg[i])
	{
		while (arg[j])
		{
		if (arg[j] && ((opt->r == 0 && ft_strcmp(arg[i], arg[j]) < 0) ||
(opt->r == 1 && ft_strcmp(arg[i], arg[j]) > 0)))
		{
			tmp = arg[j];
			arg[j] = arg[i];
			arg[i] = tmp;
		}	
			j++;
		}
		i++;
		j = 0;
	}
	return (arg);
}

static char	**find_error(char **arg, t_opt *opt)
{
	DIR *dr;
	int i;
	int dircount;
	struct stat		buf;

	dircount = 0;
	i = 1;
	while (arg[i] && arg[i][0] == '-' && parse_opt(arg[i]) && stat(arg[i], &buf) == -1 && lstat(arg[i], &buf) == -1)
		i++;
//		printf("salut\n");
	arg = parse_arg(&arg[i], opt);
	i = 0;
	while (arg[i])
	{
		errno = 0;
		dr = opendir(arg[i]);
		if (errno != 20 && errno != 0 && (errno == 2 && (lstat(arg[i], &buf) == -1)))
		{
			perror(ft_strjoin("ft_ls : " , arg[i]));
			opt->tricks = 1;
		}
		if (errno == 0)
			dircount += 1;
		i++;
	}
	if (dircount > 1)
		opt->tricks = 1;
	return (arg);
}

int			main(int argc, char **argv)
{
	int i;
	DIR *dr;
	t_opt *opt;
	t_data *dir;
	t_data *save;
	int  tmplol;
	t_len *len;

	len = NULL;
	tmplol = 0;
	dir = NULL;
	i = 0;
	save = NULL;
	opt = NULL;
	opt = (t_opt*)malloc(sizeof(t_opt));
	init_opt(opt);
//	if (argc > 1 && parse_opt(argv[1])) // parse and stock opt/put error and free
//	{
		opt = stock_opt(opt, argv);
			if (errno == 2)
				return (1);
//	}
//	else///WTFFF
//		return (1);
struct stat		buf;
		argv = find_error(argv, opt); // find and print error arg
		if (argv[i] && argc > 1)
		{
		while (argv[i])
		{
			dr = opendir(argv[i]);
			if (errno != 0 && ((lstat(argv[i], &buf) == 0) || (stat(argv[i], &buf) == 0)))// FICHIER
			{
				opt->tricks = 1;
				len = (t_len*)malloc(sizeof(t_len));
				init_t_len(len);
				dir = make_line(ft_strdup(argv[i]), ft_strdup(argv[i]), dir, ft_strdup(argv[i]));
				if (save == NULL)
					save = dir;
				else if (dir)
					save = make_list(dir, save, opt);
				set_len(len, dir);
				tmplol = 1;
			}
			errno = 0;
			i++;
		}
		if (save)
			print_file(save, len, opt);
		i = 0;
		while (argv[i])
		{
			dr = opendir(argv[i]);
	//	printf("%d\n", errno);	
			if (errno == 0)
				tmplol = 1;
			if (errno == 0 && opt->R == 0) //PATH DOSSIER
				dir = make_dir(ft_strjoin(argv[i], "/"), opt);
			else if (errno == 0 && opt->R == 1)
				make_all_r(ft_strdup(argv[i]), dir, opt);

			//	perror(path);
			errno = 0;
			i++;
		}
	}
	if (tmplol == 0)// simple ls
	{
		if (opt->R == 1)
			make_all_r(ft_strdup("."), dir, opt);
		else
			make_dir("./", opt);
	}
	free(opt);
	return (1);
}
