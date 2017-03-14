/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:07:38 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/14 11:40:48 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

static int	ft_intlen(int nb)
{
	int len;

	len = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

void		init_t_len(t_len *len)
{
	len->hlen = 0;
	len->ulen = 0;
	len->glen = 0;
	len->blen = 0;
	len->total = 0;
	len->mlen = 0;
}

void		set_len(t_len *len, t_data *fp)
{
	if (ft_intlen(fp->hlinks) > len->hlen)
		len->hlen = ft_intlen(fp->hlinks);
	if ((int)ft_strlen(fp->user) > len->ulen)
		len->ulen = ft_strlen(fp->user);
	if ((int)ft_strlen(fp->grp) > len->glen)
		len->glen = ft_strlen(fp->grp);
	if (ft_intlen(fp->bytes) > len->blen)
		len->blen = ft_intlen(fp->bytes);
	if ((fp->inode[0] == 'c' || fp->inode[0] == 'b') &&
			(ft_intlen(fp->minor) > len->mlen))
		len->mlen = ft_intlen(fp->minor);
	len->total += fp->blocks;
}

static void	print_f(t_data *save, t_len *len, int devf, t_opt *opt)
{
	if (opt->l == 1)
		if (save->inode[0] == 'c' || save->inode[0] == 'b')
		{
			ft_printf("%s  %*d %-*s  %-*s  %*d, %*d %s %s", save->inode,
len->hlen, save->hlinks, len->ulen, save->user,
len->glen, save->grp, len->blen, save->bytes,
len->mlen, save->minor, save->time, save->name);
		}
		else
			ft_printf("%s  %*d %-*s  %-*s  %*d %s %s", save->inode,
len->hlen, save->hlinks, len->ulen, save->user, len->glen + devf, save->grp,
len->blen, save->bytes, save->time, save->name);
	else
		ft_printf("%s", save->name);
}

void		print_file(t_data *save, t_len *len, t_opt *opt)
{
	int	devf;

	devf = 0;
	if (len->mlen != 0)
	{
		devf = ft_intlen(len->mlen) + 4;
		len->glen += 2;
	}
	opt->tricks = 1;
	opt->dpcount = 1;
	while (save)
	{
		print_f(save, len, devf, opt);
		if (save->linkname && opt->l == 1)
			ft_printf(" -> %s", save->linkname);
		save = save->next;
		ft_printf("\n");
	}
	free(len);
	len = NULL;
}
