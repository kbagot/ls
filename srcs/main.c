/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:44:39 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/17 18:29:11 by kbagot           ###   ########.fr       */
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
				//			ft_printf("ls: illegal option -- %c\n", opt[j]);
				//			ft_printf("usage: ls [%s] [file ...]\n", val)	;
				return (0);
			}
			j++;
		}
	return (1);
}

static void		*init_opt(t_opt *opt)
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

	i = 0;
	opt = (t_opt*)malloc(sizeof(t_opt));
	init_opt(opt);
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
	return (opt);
}

static void	*print_error(char **arg)
{
	DIR *dr;
	int i;

	i = 0;
	while (argv[i])
	{
		dr = opendir(argv[i]);
		if (errno = 2)
		{
			
		}
		errno = 0;
		i++;
	}
}

int			main(int argc, char **argv)
{
	DIR *dr;
	t_opt *opt;

	opt = NULL;
	if (argc > 1)
	{
		if (parse_opt(argv[1]))
			stock_opt(opt, argv);
		print_error(argv)
			dr = opendir(argv[i]);
		if (errno == 20) // FICHIER
			printf("%s\n", argv[i]);
		else if (errno == 0) //PATH DOSSIER
			make_dir(argv[i], dr, opt);
		else if (errno == 2 && argv[i][0] != '-')
			//		if (parse_opt(&argv[1][0]))
			//			errno = 1;
			//			if (argv[i][0] == '-')
			//				opt = stock_opt(opt, &argv[i][1]);
			//	ft_printf("errno: %d\n", errno);
			errno = 0;
		i++;
	}
	else // simple ls
	{
		dr = opendir("./");
		make_dir("./", dr, opt);
	}
	return (0);
}
