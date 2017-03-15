/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 19:57:00 by kbagot            #+#    #+#             */
/*   Updated: 2017/03/15 19:49:45 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <sys/types.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <errno.h>
# include <limits.h>
# include <string.h>

typedef struct		s_opt
{
	int				l;
	int				up_r;
	int				a;
	int				r;
	int				t;
	int				tricks;
	int				dpcount;
	int				noarg;
}					t_opt;

typedef struct		s_data
{
	char			*path;
	char			*inode;
	int				hlinks;
	char			*user;
	char			*grp;
	long long int	bytes;
	int				major;
	time_t			times;
	char			*time;
	char			*name;
	int				blocks;
	char			*linkname;
	struct s_data	*next;
}					t_data;

typedef struct		s_len
{
	int				hlen;
	int				ulen;
	int				glen;
	int				blen;
	int				total;
	int				mlen;
}					t_len;

t_data				*make_line
(char *cleanpath, char *path, t_data *fp, char *name);
t_data				*make_dir(char *path, t_opt *opt);
t_data				*make_list(t_data *fp, t_data *save, t_opt *opt);
void				print_file(t_data *save, t_len *len, t_opt *opt);
void				make_all_r(char *path, t_data *dir, t_opt *opt);
void				set_len(t_len *len, t_data *fp);
void				init_t_len(t_len *len);
char				*get_inode(int st_mode);
char				*set_time(time_t timef);
char				**find_error(char **arg, t_opt *opt);
void				free_land(t_data *save);
void				dir_maker(char **argv, t_opt *opt, t_data *dir, int i);
void				file_maker(char **argv, t_opt *opt, t_data *dir, int i);
int					main(int argc, char **argv);
t_opt				*stock_opt(t_opt *opt, char **arg);
int					parse_opt(char *opt);
void				current_dir(t_opt *opt);
void				redirect_arg(char **argv, t_opt *opt);

#endif
