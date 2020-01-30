# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbianco <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/13 15:06:40 by gbianco           #+#    #+#              #
#    Updated: 2020/01/23 09:44:23 by lucmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJD = compiled/
SANI = -g #-fsanitize=address
FLAGS = -Wall -Wextra -Werror $(SANI)

SRC = ft_atoi.c\
	  ft_atoibase.c\
	  ft_power.c\
	  ft_bzero.c\
	  ft_concat_params.c\
	  ft_count_words.c\
	  ft_degtorad.c\
	  ft_int_buffer.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isprint.c\
	  ft_iscapital.c\
	  ft_itoa.c\
	  ft_llitoa.c\
	  ft_lstadd.c\
	  ft_lstcount.c\
	  ft_lstdel.c\
	  ft_lstdelone.c\
	  ft_lstiter.c\
	  ft_lstmap.c\
	  ft_lstnew.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memdel.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_fmax.c\
	  ft_fmin.c\
	  ft_fmod.c\
	  ft_putchar.c\
	  ft_putchar_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_putstr_fd.c\
	  ft_radtodeg.c\
	  ft_secmemalloc.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strarraydel.c\
	  ft_strarraydeln.c\
	  ft_strdup.c\
	  ft_strequ.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strlcat.c\
	  ft_strlen.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strrev.c\
	  ft_strsplit.c\
	  ft_strstr.c\
	  ft_strinstr.c\
	  ft_strinstr_unlimited.c\
	  ft_strsub.c\
	  ft_strtrim.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  ft_atof.c\
	  ft_isnumber.c\
	  ft_ishex.c\
	  get_next_line.c\
	  ft_strnjoin.c

# Colors
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRC = \033[0;36m
CLRW = \033[0m
LIBC = $(CLRC)[LIBFT]$(CLRW)

OBJS = $(addprefix $(OBJD), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJD) $(OBJS)
	@printf	"$(LIBC)%-50s [$(CLRR)%s$(CLRW)]" "Libft compiled" "✘"	
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf	"\r$(LIBC)$(CLRG)%-50s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "Libft compiled" "✔"

$(OBJD): 
	@mkdir -p $(OBJD)
	@printf "$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "Repository: $@ created" "✔"

$(OBJD)%.o: %.c libft.h
	@printf	"$(LIBC)%-50s [$(CLRR)%s$(CLRW)]" "Object: $@ compiled" "✘"	
	@gcc $(FLAGS) -c $< -o $@
	@printf	"\r$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "Object: $@ compiled" "✔" 

.PHONY: clean fclean re
.NOTPARALLEL : $(OBJS)

clean:
	@rm -rf $(OBJD)
	@printf	"$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "Objects removed" "∙"	

fclean: clean
	@rm -f $(NAME)
	@printf	"$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: $(NAME) removed" "∙"	

re: fclean all
