/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:44:39 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/22 18:49:36 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static int	parse_opt(char *opt)
{
	int	j;
	char *val;

	j = 0;
	val = "-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
	if (opt[0] == '-')
		while (opt[j] && j != -1)
		{
			if (ft_strchr(val, opt[j]) == NULL)
			{
				ft_printf("ls: illegal option -- %c\n", opt[j]);
				ft_printf("usage: ls [%s] [file ...]\n", val);
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
}

static t_opt	*stock_opt(t_opt *opt, char **arg)
{
	int i;

	i = 1;
	while (arg[i][0] == '-' && parse_opt(arg[i]))
	{
		if (ft_strchr(arg[i], 'l'))
			opt->l = 1;
		if (ft_strchr(arg[i], 'R'))
			opt->R = 1;
		if (ft_strchr(arg[i], 'a'))
			opt->a = 1;
		if (ft_strchr(arg[i], 'r'))
			opt->r = 1;
		if (ft_strchr(arg[i], 't'))
			opt->t = 1;
		i++;
	}
	if (errno == 2)
		free(opt);
	return (opt);
}

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

static void	print_error(t_error *error)
{
	while (error)
	{
		printf("ls: %s: No such file or directory\n", error->ename);
		error = error->next;
	}
}

static char **parse_arg(char **arg)
{
	int i;
	int j;
	char *tmp;

	j = 1;
	i = 1;
	tmp = NULL;
	while (arg[i])
	{
		while (arg[j] && (ft_strcmp(arg[i], arg[j])) >= 0)
			j++;
		if (arg[j] && ft_strcmp(arg[i], arg[j]) < 0)
		{
			tmp = arg[i];
			arg[i] = arg[j];
			arg[j] = tmp;
		}
		i++;
		j = 1;
	}
	return (arg);
}

static void	find_error(char **arg)
{
	DIR *dr;
	int i;
	t_error *error;

	i = 1;
	error = NULL;
	while (arg[i][0] == '-' && parse_opt(arg[i]))
		i++;
	arg = parse_arg(arg);
	while (arg[i])
	{
		dr = opendir(arg[i]);
		if (errno == 2)
			error = make_error_list(error, arg[i]);
		errno = 0;
		i++;
	}
	if (error != NULL)
		print_error(error);
}

int			main(int argc, char **argv)
{
	int i;
	DIR *dr;
	t_opt *opt;

	i = 1;
	opt = NULL;
	opt = (t_opt*)malloc(sizeof(t_opt));
	init_opt(opt);
	if (argc > 1)
	{
		if (parse_opt(argv[1])) // parse and stock opt/put error and free
		{
			opt = stock_opt(opt, argv);
				if (errno == 2)
					return (0);
		}
		find_error(argv); // find and print error arg
		argv = parse_arg(argv);
		while (argv[i])
		{
			dr = opendir(argv[i]);
			if (errno == 20) // FICHIER
				printf("%s\n", argv[i]);
			errno = 0;
			i++;
		}
		i = 1;
		while (argv[i])
		{
			dr = opendir(argv[i]);
			if (errno == 0 && opt->R == 0) //PATH DOSSIER
				make_dir(ft_strjoin(argv[i], "/"), opt);
			else if (errno == 0 && opt->R == 1)
				make_all_r(argv[i], dr, opt);
			errno = 0;
			i++;
		}
	}
	else // simple ls
	{
		dr = opendir("./");
		make_dir("./", opt);
	}
	free(opt);
	return (0);
}
