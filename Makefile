# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbianco <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 16:07:40 by gbianco           #+#    #+#              #
#    Updated: 2020/01/30 11:48:19 by lucmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
FLAG = -Wall -Wextra
FRAM = -framework OpenGL -framework AppKit
SANI = -g -fsanitize=address
MTHR = -lpthread -lm

SRCD = ./srcs/
PRSD = ./srcs/parser/
LOSD = ./srcs/loader/
VOSD = ./srcs/void/
INCD = ./includes/
OBJD = ./compiled/
LFTD = ./libs/libft/
VECD = ./libs/libvector/
MTXD = ./libs/libmatrix/
MLXD = ./libs/libmlxmac/

CLSD = ./srcs/cluster/
CL_IO = $(CLSD)IO/
CL_HL = $(CLSD)helpers/
CL_MS = $(CLSD)misc/
CL_PR = $(CLSD)protocols/
CL_SV = $(CLSD)server/
CL_SO = $(CLSD)socket/

VECF = $(VECD)vec.a
LIBF = $(LFTD)libft.a
MLXF = $(MLXD)libmlx.a
MTXF = $(MTXD)matrix.a

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Linux)
FRAM = -lX11 -lXext -lbsd
MLXD = ./libs/libmlxlinux/
else
FRAM = -framework OpenGL -framework AppKit
MLXD = ./libs/libmlxmac/
endif


FILE =	afterparser.c afterparser_imp.c anaglyph.c antialiasing.c camera.c \
		camera_qtn.c cartoon.c color_anaglyph.c color_effects.c errors.c \
		hit.c intersections.c events_keys.c events_mouse.c main.c \
		saveimageppm.c shaders.c shaders_color.c shaders_cartoon.c transform.c \
		transform_trn.c render.c render_single.c render_distributed.c \
		render_timed_obj.c render_timed_cam.c \
		light.c light_rct.c light_cam.c \
		obj_plane.c obj_sphere.c obj_cylinder.c obj_disk.c obj_cone.c \
		obj_triangle.c \
		assigner.c assignerb.c assignersp.c count.c counttags.c deepcount.c \
		deepcountb.c parser.c xml_nested.c xml_validity.c xml_equality.c \
		split.c split_alloc.c split_effect.c split_light.c split_prmtrn.c \
		split_white.c split_mesh_group.c split_mesh.c split_group.c \
		split_group_utils.c split_group_rotation.c split_group_light.c debug.c
FILE += void_sort.c void_regions.c
FILE += loader_main.c loader_colors.c loader_graphic.c

# CLUSTER FILES
FILE += cluster_main.c options.c
FILE += read_file.c
FILE += commands_helper.c server_helper.c string_helper.c colors_helper.c
FILE += get_name_base.c ip_validity.c
FILE += close.c naive.c run.c return.c set.c status.c commands.c send.c recv.c
FILE += server_cmd.c server_process.c server_select.c server_return.c \
		server_mlx.c
FILE += socket.c socket_aux.c
# END OF CLUSTER FILES


INCL = $(INCD)rtv1.h
ALLI = -I $(INCD) -I $(LFTD) -I $(VECD) -I $(MLXD) -I $(MTXD)

# Colors
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRB = \033[0;34m
CLRC = \033[0;36m
CLRW = \033[0m
LIBC = $(CLRC)[LIBFT]$(CLRW)
VECC = $(CLRC)[LBVEC]$(CLRW)
MTXC = $(CLRC)[LBMTX]$(CLRW)
RTVC = $(CLRB)[RT]$(CLRW)

OBJF = $(addprefix $(OBJD), $(FILE:.c=.o))

all : $(NAME)

$(NAME) : $(LIBF) $(VECF) $(MLXF) $(MTXF) $(OBJD) $(OBJF) 
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "$(NAME) compiled" "✘"
	@gcc $(FRAM) $(SANI) $(MTHR) -o $@ $(OBJF) $(LIBF) $(VECF) $(MLXF) $(MTXF)
	@printf	"\r$(RTVC)$(CLRG)%-53s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "$(NAME) compiled" "✔"

$(LIBF) :
	@sh logo/showlogo.sh
	@make -j -C $(LFTD)
$(VECF) :
	@ make -j -C $(VECD)
$(MLXF) :
	@ make -j -s -C $(MLXD)
$(MTXF) :
	@ make -j -s -C $(MTXD)

$(OBJD) :	
	@mkdir -p $(OBJD)
	@printf	"$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Repository: compiled created" "✔"

$(OBJD)%.o: $(SRCD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(PRSD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(LOSD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(VOSD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"

$(OBJD)%.o: $(CLSD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"

$(OBJD)%.o: $(CL_IO)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(CL_HL)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(CL_MS)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(CL_PR)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(CL_SV)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(CL_SO)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"

clean:
	@make -C $(LFTD) clean
	@make -C $(VECD) clean
	@make -C $(MLXD) clean
	@make -C $(MTXD) clean
	@rm -rf $(OBJD)
	@printf	"$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Objects removed" "∙"

fclean: clean
	@rm -f $(LIBF)
	@printf	"$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: libft.a removed" "∙"
	@rm -f $(VECF)
	@printf	"$(VECC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: vec3.a removed" "∙"	
	@rm -f $(MTXF)
	@printf	"$(MTXC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: matrix.a removed" "∙"
	@rm -rf $(NAME)
	@printf	"$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "File: $(NAME) removed" "∙" 

re: fclean all

.PHONY : clean fclean re
.NOTPARALLEL : $(LIBF)
