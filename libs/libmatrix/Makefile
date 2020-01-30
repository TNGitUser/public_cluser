# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbianco <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 20:09:50 by gbianco           #+#    #+#              #
#    Updated: 2020/01/23 09:44:35 by lucmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = matrix.a
OBJD = compiled/
FILE = utility_0.c functions_0.c functions_1.c functions_2.c functions_3.c \
	   functions_4.c functions_5.c functions_6.c display.c 
SANI = -g #-fsanitize=address
FLAG = -Wall -Werror -Wextra $(SANI)

# Colors
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRC = \033[0;36m
CLRW = \033[0m
MTRC = $(CLRC)[LBMTX]$(CLRW)

OBJS = $(addprefix $(OBJD),$(FILE:.c=.o))

all : $(NAME)

$(NAME) : $(OBJD) $(OBJS)
	@printf	"$(MTRC)%-50s [$(CLRR)%s$(CLRW)]" "Libmtrx compiled" "✘"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf	"\r$(MTRC)$(CLRG)%-50s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "Libmtrx compiled" "✔"	

$(OBJD) :
	@mkdir -p $(OBJD)
	@printf	"$(MTRC)%-50s [$(CLRG)%s$(CLRW)]\n" "Repository: $@ created" "✔"

$(OBJD)%.o : %.c matrix.h
	@printf	"$(MTRC)%-50s [$(CLRR)%s$(CLRW)]" "Object: $@ compiled" "✘"
	@gcc $(FLAG) -o $@ -c $<
	@printf	"\r$(MTRC)%-50s [$(CLRG)%s$(CLRW)]\n" "Object: $@ compiled" "✔"

.PHONY : clean fclean re dir
.NOTPARALLEL : $(OBJS)

clean :
	@rm -rf $(OBJD)
	@printf	"$(MTRC)%-50s [$(CLRG)%s$(CLRW)]\n" "Objects removed" "∙"

fclean : clean
	@rm -f $(NAME)
	@printf	"$(MTRC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: $(NAME) removed" "∙"

re : fclean all
