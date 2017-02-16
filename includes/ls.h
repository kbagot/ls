/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 19:57:00 by kbagot            #+#    #+#             */
/*   Updated: 2017/02/16 20:10:48 by kbagot           ###   ########.fr       */
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

typedef struct		s_data
{
	char			*inode;
	int				hlinks;
	char			*user;
	char			*grp;
	int				bytes;
	char			*time;
	char			*name;
	int				blocks;
	struct s_data	*next;
}					t_data;

typedef struct		s_len
{
	int				ulen;
	int				glen;
	int				blen;
}					t_len;

t_data	*make_line(char *path, t_data *fp, char *name);
void	make_dir(char *path, DIR *dr);
t_data	*make_list(t_data *fp);

#endif
