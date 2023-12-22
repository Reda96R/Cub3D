#::::::::::::::::OS::::::::::::::::#
OS 			= $(shell uname -s)

#:::::::::::::::VARS:::::::::::::::#
NAME 		= cub3D
SRC_DIR		= src/
OBJ_DIR 	= .obj/
FSANITIZE 	= # -g -fsanitize=address
CFLAGS 		= -Wall -Werror -Wextra $(FSANITIZE)
CC 			= cc
MAIN = main
M_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(addprefix src/, $(MAIN))))

#::::::::::::::::MLX:::::::::::::::#
ifeq ($(OS), Darwin)
COMP 		= -lmlx -framework OpenGL -framework AppKit
COMP_O 		= -Imlx
else
COMP 		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
COMP_O 		= -I/usr/include -Imlx_linux
endif

all: $(NAME)

#::::::::::::::::PRS:::::::::::::::#
P_FILES = 

P_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(addprefix src/parsing/, $(P_FILES))))

#::::::::::::::::RAY:::::::::::::::#
R_FILES = ft_shapes ft_drawer ft_keylogger ft_maths_hub ft_starter ft_rays

R_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(addprefix src/ray_casting/, $(R_FILES))))

#:::::::::::::Compile::::::::::::::#
$(NAME): $(M_OBJS) $(P_OBJS) $(R_OBJS)
	@echo $(cursive)$(grey)":::Making object files:::"$(reset)
	@echo $(cursive)$(grey)":::Compiling $(NAME):::"$(reset)
	@$(CC) $(CFLAGS) $(M_OBJS) $(P_OBJS) $(R_OBJS) $(COMP) -o $(NAME)
	@echo $(f_green)":::✅ $(NAME) is ready ✅:::"$(reset)

$(OBJ_DIR)%.o: %.c 
	@mkdir -p .obj/src .obj/src/parsing .obj/src/ray_casting
	@$(CC) $(CFLAGS) $(COMP_O) -c $< -o $@

clean:
	@echo $(cursive)$(grey)":::Deleting object files:::"$(reset)
	@rm -rf $(OBJ_DIR)
	@echo $(red)":::Deleted:::"$(reset)

fclean: clean
	@echo $(cursive)$(grey)":::Deleting executable:::"$(reset)
	@rm -rf $(NAME)
	@echo $(red)":::Deleted:::"$(reset)

re: fclean all

.PHONY: all clean fclean re os

define os
	@echo $(yellow) "          _____                    _____                    _____          " $(reset)
	@echo $(yellow) "         /\    \                  /\    \                  /\    \         " $(reset)
	@echo $(yellow) "        /::\    \                /::\____\                /::\    \        " $(reset)
	@echo $(yellow) "       /::::\    \              /:::/    /               /::::\    \       " $(reset)
	@echo $(yellow) "      /::::::\    \            /:::/    /               /::::::\    \      " $(reset)
	@echo $(yellow) "     /:::/\:::\    \          /:::/    /               /:::/\:::\    \     " $(reset)
	@echo $(yellow) "    /:::/  \:::\    \        /:::/    /               /:::/__\:::\    \    " $(reset)
	@echo $(yellow) "   /:::/    \:::\    \      /:::/    /               /::::\   \:::\    \   " $(reset)
	@echo $(yellow) "  /:::/    / \:::\    \    /:::/    /      _____    /::::::\   \:::\    \  " $(reset)
	@echo $(yellow) " /:::/    /   \:::\    \  /:::/____/      /\    \  /:::/\:::\   \:::\ ___\ " $(reset)
	@echo $(yellow) "/:::/____/     \:::\____\|:::|    /      /::\____\/:::/__\:::\   \:::|    |" $(reset)
	@echo $(yellow) "\:::\    \      \::/    /|:::|____\     /:::/    /\:::\   \:::\  /:::|____|" $(reset)
	@echo $(yellow) " \:::\    \      \/____/  \:::\    \   /:::/    /  \:::\   \:::\/:::/    / " $(reset)
	@echo $(yellow) "  \:::\    \               \:::\    \ /:::/    /    \:::\   \::::::/    /  " $(reset)
	@echo $(yellow) "   \:::\    \               \:::\    /:::/    /      \:::\   \::::/    /   " $(reset)
	@echo $(yellow) "    \:::\    \               \:::\__/:::/    /        \:::\  /:::/    /    " $(reset)
	@echo $(yellow) "     \:::\    \               \::::::::/    /          \:::\/:::/    /     " $(reset)
	@echo $(yellow) "      \:::\    \               \::::::/    /            \::::::/    /      " $(reset)
	@echo $(yellow) "       \:::\____\               \::::/    /              \::::/    /       " $(reset)
	@echo $(yellow) "        \::/    /                \::/____/                \::/____/       " $(reset)
	@echo $(yellow) "         \/____/                  ~~                       ~~              " $(reset)
	@echo $(green) "                                                                    for $(OS)" $(reset)
	@echo $(green) "                                                  " $(reset)
endef

#::::::::::::::Colors::::::::::::::#
black  		= "\033[0;30m"
red    		= "\033[0;31m"
green  		= "\033[0;32m"
f_green		= "\e[92;5;118m"
yellow 		= "\033[0;33m"
purple		= "\033[0;35m"
blue   		= "\033[0;34m"
cyan  		= "\033[0;36m"
grey   		= "\033[0;90m"
reset  		= "\033[0m"

#::::::::::::::Fonts:::::::::::::::#
bold     	= "\033[1m"
cursive    	= "\033[3m"
underline 	= "\033[4m"
