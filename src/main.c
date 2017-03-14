/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:44:39 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/14 12:18:37 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static void	init_opt(t_opt *opt)
{
	opt->l = 0;
	opt->up_r = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->tricks = 0;
	opt->dpcount = 0;
	opt->tmplol = 0;
}

static void	opt_search(t_opt *opt, char *arg)
{
	if (ft_strchr(arg, 'l'))
		opt->l = 1;
	if (ft_strchr(arg, 'R'))
		opt->up_r = 1;
	if (ft_strchr(arg, 'a'))
		opt->a = 1;
	if (ft_strchr(arg, 'r'))
		opt->r = 1;
	if (ft_strchr(arg, 't'))
		opt->t = 1;
}

int			parse_opt(char *opt)
{
	int		j;
	char	*val;

	j = 1;
	val = "-Rrtal1";
	if (opt[0] == '-')
		while (opt[j])
		{
			if (ft_strchr(val, opt[j]) == NULL || (opt[j] == '-' && opt[j + 1]))
			{
				ft_putstr_fd("ls: illegal option -- ", 2);
				ft_putchar_fd(opt[j], 2);
				ft_putchar_fd('\n', 2);
				ft_putstr_fd("usage: ls [", 2);
				ft_putstr_fd(val, 2);
				ft_putstr_fd("] [file ...]\n", 2);
				errno = 42;
				return (0);
			}
			j++;
		}
	return (1);
}

t_opt		*stock_opt(t_opt *opt, char **arg)
{
	DIR			*dr;
	int			i;
	struct stat	buf;

	i = 1;
	errno = 0;
	dr = opendir(arg[i]);
	while (arg[i] && arg[i][0] == '-' && errno != 0 &&
			((lstat(arg[i], &buf) == -1) || (stat(arg[i], &buf) == -1)) &&
			parse_opt(arg[i]))
	{
		opt_search(opt, arg[i]);
		i++;
		if (dr)
			closedir(dr);
		errno = 0;
		dr = opendir(arg[i]);
	}
	if (dr)
		closedir(dr);
	return (opt);
}

int			main(int argc, char **argv)
{
	t_opt *opt;

	opt = NULL;
	opt = (t_opt*)malloc(sizeof(t_opt));
	init_opt(opt);
	opt = stock_opt(opt, argv);
	if (errno == 42)
	{
		free(opt);
		opt = NULL;
		return (1);
	}
	argv = find_error(argv, opt);
	if (argv[0] && argc > 1)
		redirect_arg(argv, opt);
	if (opt->tmplol == 0 && opt->tricks == 0)
		current_dir(opt);
	free(opt);
	opt = NULL;
	return (1);
}
