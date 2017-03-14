/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:45:10 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/14 11:47:24 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

void			redirect_arg(char **argv, t_opt *opt)
{
	t_data	*dir;
	int		i;

	i = 0;
	dir = NULL;
	file_maker(argv, opt, dir, i);
	dir_maker(argv, opt, dir, i);
}

void			current_dir(t_opt *opt)
{
	t_data *dir;

	dir = NULL;
	if (opt->tmplol == 0 && opt->tricks == 0)
	{
		if (opt->up_r == 1)
			make_all_r(ft_strdup("."), dir, opt);
		else
			make_dir("./", opt);
	}
}
