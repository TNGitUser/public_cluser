#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2 -w

# Colors
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRC = \033[0;36m
CLRW = \033[0m
MLXC = $(CLRC)[LBMLX]$(CLRW)

all: $(NOM)

$(NOM):	$(OBJ)
	@printf	"$(MLXC)%-50s [$(CLRR)%s$(CLRW)]" "Libmlx compiled" "✘"
	@ar rc $(NOM) $(OBJ)
	@ranlib $(NOM)
	@printf	"\r$(MLXC)$(CLRG)%-50s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "Libmlx compiled" "✔"

clean:
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app
	@printf	"$(MLXC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: $(NOM) removed" "∙"

re: clean all
