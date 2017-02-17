/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 19:57:00 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/17 18:29:20 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdio.h>
# include <pwd.h>
# include <sys/types.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>

typedef struct 		s_error
{
	int				terror;// 1 = usage opt 2 = no exist
	char			*cerror;
	struct s_error	*next;
}					t_error;

typedef struct		s_opt
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_opt;

typedef struct		s_data
{
	char			*inode;
	int				hlinks;
	char			*user;
	char			*grp;
	int				bytes;
	char			*time;
	char			*name;
//total
	int				blocks;
	struct s_data	*next;
}					t_data;

typedef struct		s_len
{
	int				hlen;
	int				ulen;
	int				glen;
	int				blen;
	int				total;
}					t_len;

t_data	*make_line(char *path, t_data *fp, char *name);
void	make_dir(char *path, DIR *dr, t_opt *opt);
t_data	*make_list(t_data *fp);

#endif
