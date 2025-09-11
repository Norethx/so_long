NAME := so_long

CC := cc

CFLAGS := -Wall -Wextra -Werror -g3

MLXFLAGS := -ldl -lglfw -pthread -lm

LIBFT := srcs/libft/libft.a

MLX42 := MLX42/build/libmlx42.a

SRCS_LIBFT := srcs/libft

INCLUDES := includes MLX42/include/MLX42

CPPFLAGS :=  $(addprefix -I,$(INCLUDES))

SRCS_MANDATORY := ft_fill_scenario.c   ft_flood_fill.c     ft_generate_images.c \
                  ft_handle_game.c     ft_handle_player.c  ft_hook_idle.c \
                  ft_verify_map.c      handle_error.c      so_long.c

SRCS_BONUS := ft_fill_scenario.c      ft_flood_fill.c        ft_generate_images.c \
              ft_handle_game.c        ft_handle_patrol_aux.c ft_handle_patrol.c \
              ft_handle_player.c      ft_hook_idle.c         ft_hook_player_idle.c \
              ft_upload_textures.c    ft_verify_map.c        handle_error.c \
              so_long.c

OBJTS   := $(SRCS_MANDATORY:.c=.o)

SRCS_BONUS := $(addprefix srcs/bonus/,$(SRCS_BONUS))

OBJTS_BONUS	:= $(SRCS_BONUS:.c=.o)

OBJTS_LIBFT = $(shell $(MAKE) -s -C $(SRCS_LIBFT) get_var)

OBJTS_LIBFT := $(addprefix $(SRCS_LIBFT)/,$(OBJTS_LIBFT))


# Cores ANSI
GREEN  = \033[0;32m
RED    = \033[0;31m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
MAGENTA= \033[0;35m
CYAN   = \033[0;36m
NC     = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJTS) $(MLX42)
		@echo "$(YELLOW)+==========================================+"
		@echo "          Build $(NAME)          	"
		@echo "+==========================================+$(NC)"
		$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJTS) $(LIBFT) $(MLX42) $(MLXFLAGS) -o $(NAME)

$(MLX42):
		@echo "$(CYAN)+==========================================+"
		@echo "          Build MLX          	"
		@echo "+==========================================+$(NC)"
		cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

$(LIBFT): $(OBJTS_LIBFT)
		@echo "$(MAGENTA)+==========================================+"
		@echo "                Github: Norethx       "
		@echo "+==========================================+\n\n$(NC)"
		@echo "$(GREEN)	⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆"
		@echo "	⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿"
		@echo "	⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀"
		@echo "	⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉\n\n$(NC)"
		@echo "$(RED)+==========================================+"
		@echo "      Welcome to so_long - Build libft       "
		@echo "+==========================================+$(NC)"
		@echo "Compilando código...\n"
		@make -C $(SRCS_LIBFT) all
		@echo "$(BLUE)+==========================================+"
		@echo "          Build Objts so_long          	"
		@echo "+==========================================+$(NC)"

%.o: %.c
		$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean fclean re all bonus $(OBJTS_LIBFT)

bonus:
		$(MAKE) SRCS_MANDATORY="$(SRCS_BONUS)" all

clean:
		@make -C $(SRCS_LIBFT) clean
		rm -f $(OBJTS) $(OBJTS_BONUS)

fclean:
		@make -C $(SRCS_LIBFT) fclean
		rm -f $(OBJTS) $(OBJTS_BONUS)
		rm -f $(NAME) $(MLX42)

re: fclean all
