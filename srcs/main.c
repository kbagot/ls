/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:44:39 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/15 20:43:04 by kbagot           ###   ########.fr       */
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
				j = -2;
				return (1);
			}
			j++;
		}
	return (0);
}

int			main(int argc, char **argv)
{
	DIR *dr;
	int i;

	i = 1;
	if (argc > 1)
	{
		while (argv[i])
		{
			dr = opendir(argv[i]);
			if (parse_opt(&argv[1][0]))
				errno = 1;
			else if (errno == 20) // FICHIER
				print_line(argv[i]);
			else if (errno == 0) //PATH DOSSIER
				ft_printf("{%s}\n", argv[i]);
			else if (errno == 2 && argv[i][0] != '-')
				ft_printf("ls: %s: No such file or directory\n", argv[i]);		
			//	ft_printf("errno: %d\n", errno);
			errno = 0;
			i++;
		}
	}
	else // simple ls
	{
		dr = opendir("./");
	}
	return (0);
}
