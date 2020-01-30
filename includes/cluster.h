/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:36:27 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/30 13:37:58 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_H
# define CLUSTER_H

# include "sys/socket.h"
# include "arpa/inet.h"
# include "netinet/in.h"

# define PORT			7654
# define MAXCON			10
# define BUFFER_SIZE	1024

# define NAME_BASE	"data/names.dat"

# define SET_CLIENT			0
# define SET_BOUNDS			1
# define SEND_SCENE			2
# define GET_SCENE			3
# define ASK_STATUS			4
# define CLOSE_CLIENT		9

typedef	struct	s_name_base
{
	char	**names;
	size_t	count;
}				t_name_base;

typedef	struct	s_client
{
	char	*file_data;
	int		ready;
	int		set;
	int		active;
	int		socket;
	char	*name;
	int		name_id;
	int		color[3];
	int		start[2];
	int		end[2];
}				t_client;

typedef	struct	s_node
{
	int					type;
	struct sockaddr_in	addr;
	struct sockaddr_in	serv_addr;
	int					socket_fd;
	fd_set				con_set;
	int					con_socket[MAXCON];
	t_client			clients[MAXCON];
	int					read_err[MAXCON];
	char				*computed_scene[MAXCON];
	char				computed[MAXCON];
	int					act;
	t_client			info;
	t_name_base			namebase;
	int					wh[2];
	int					err;
	int					exec;
	int					lock;
	int					bds[4];
	char				*param;
	void				*s_ptr;
}				t_node;

typedef	struct	s_ret
{
	t_node				*node;
	int					cl_id;
}				t_ret;

/*
**	FILE : socket.c / socket_aux.c
*/
int				socket_init();
void			init_server(t_node *node);
void			init_client(t_node *node, char *server_address);

/*
**	FILE : read_file.c
*/
char			*get_data_filename(char *file);

/*
**	FILE : server_cmd.c
*/
int				server_dispatch(t_node *node, char *cmd);

/*
**	FILE : server_mlx.c
*/
void			server_init_mlx(void *sv);
void			server_loop_mlx(void *sv);

/*
**	FILE : server_process.c
*/
void			server_run(t_node *node);

/*
**	FILE : server_return.c
*/
void			server_assemble(void *sv);
void			*server_get(void *ret);

/*
**	FILE : server_select.c
*/
void			set_close_child(t_node *node, int client_id);
void			set_add_child(t_node *node, int *max_fd);
void			manage_con_new(t_node *node);
void			manage_con_event(t_node *node);

/*
**	FOLDER : protocols
*/
int				cmd_status(t_node *node, char *cmd);
int				cmd_set(t_node *node, char *cmd);
int				cmd_run(t_node *node, char *cmd);
int				cmd_return(t_node *node, char *cmd);
int				cmd_close(t_node *node, char *cmd);

void			send_file(char *text, t_node *node, int client_fd);
void			receive_file(t_node *node);
void			receive_client_file(t_node *node, int fd, int id, ssize_t *len);

void			await_command(t_node *node);
void			server_to_client(t_node *node, int client_id, char *cmd
		, int prot);
int				server_send(t_node *node, int client_fd, char *cmd);

char			*receive_client_string(t_node *node, int socket_fd, int *status
		, ssize_t *len);
char			*receive_string(t_node *node, int *status);
void			send_command(t_node *node, char *cmd, int client_id);
void			send_image(int client_fd, t_node *node);
void			send_string(int client_fd, t_node *node, char *string);

/*
**	FILE : get_name_base.c
*/
void			get_name_file(t_node *node);
void			get_client_name(t_node *node, int id);

/*
**	FILE : ip_validity.c
*/
int				is_ip_valid(char *ip);

/*
** **************************************************************************
**								HELPER FILES
** **************************************************************************
*/

/*
**	FILE : server_helper.c
*/
int				server_get_active(t_node *node);
int				server_get_ready(t_node *node);
void			server_get_workload(t_node *node, int act, int wl[2]
		, int mod[2]);
void			server_set_helper(t_node *node, int i[2], char *cmd
		, int wl[2][2]);

/*
**	FILE : colors_helper.c
*/
void			string_to_color(char *str, t_node *node);
char			*color_to_string(int colors[3]);

/*
**	FILE : string_helper.c
*/
char			*extract_string(char **src, char start, char end);
char			*strdelim(char **src, char c);
size_t			strocc(char *src, char c);
char			*strnjoin(char *src, char *add, char *end);
char			*strjoin(char *src, char *add);

/*
**	FILE : command_helper.c
*/
char			*get_other_cmd(int cmd_t, t_node *node);
char			*get_set_cmd(int cmd_t, t_client client, int bounds[4]);
int				is_command(char *cmd, int *prot);
int				cmd_dispatch(t_node *node, char *cmd, int *status);

#endif
