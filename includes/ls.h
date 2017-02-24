/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 19:57:00 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/24 20:33:12 by kbagot           ###   ########.fr       */
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
# include <errno.h>
# include <limits.h>
# include <string.h>

typedef struct		s_dir
{
	char			*path;
	struct s_dir	*next;
}					t_dir;

typedef struct 		s_error // list stock error
{
	char			*ename;
	struct s_error	*next;
}					t_error;

typedef struct		s_opt //option
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
	int				tricks;
}					t_opt;

typedef struct		s_data // -l data
{
	char			*path;
	char			*inode;
	int				hlinks;
	char			*user;
	char			*grp;
	int				bytes;
	time_t			times;
	char			*time;
	char			*name;
//total
	int				blocks;
	char			*linkname;
	struct s_data	*next;
}					t_data;

typedef struct		s_len // -l data
{
	int				hlen;
	int				ulen;
	int				glen;
	int				blen;
	int				total;
}					t_len;

t_data	*make_line(char *cleanpath, char *path, t_data *fp, char *name);
t_data	*make_dir(char *path, t_opt *opt);
t_data	*make_list(t_data *fp, t_data *save, t_opt *opt);
void	print_file(t_data *save, t_len *len, t_opt *opt);
void	make_all_r(char *path, t_data *dir, t_opt *opt);
t_data	*make_link(t_data *fp);
void	set_len(t_len *len, t_data *fp);
void	init_t_len(t_len *len);
int		ft_intlen(int nb);

#endif
