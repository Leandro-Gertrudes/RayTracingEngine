# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 20:39:24 by ghenriqu          #+#    #+#              #
#    Updated: 2026/02/16 15:41:42 by lgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

# Compiler
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
LDFLAGS     = -lm

# Directories
SRC_DIR     = srcs
I_DIR       = includes
LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux
MLX_REPO	= https://github.com/42Paris/minilibx-linux.git
MLX			= $(MLX_DIR)/libmlx.a

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext

# Includes
INCLUDES    = -I$(I_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Sources
SRC	=	$(SRC_DIR)/parser/0-main.c \
			$(SRC_DIR)/parser/1-get_scene.c \
			$(SRC_DIR)/parser/2-allocate.c \
			$(SRC_DIR)/parser/3-parser.c \
			$(SRC_DIR)/parser/3.1-parser_utils.c \
			$(SRC_DIR)/parser/3.2-parser_utils.c \
			$(SRC_DIR)/parser/3.3-parser_utils.c \
			$(SRC_DIR)/parser/3.4-parser_obj_utils.c \
			$(SRC_DIR)/parser/3.5-parser_l.c \
			$(SRC_DIR)/parser/support_functions.c \
			$(SRC_DIR)/parser/support_functions1.c \
		$(SRC_DIR)/vectors/vec3_add.c \
			$(SRC_DIR)/vectors/vec3_atovec3.c \
			$(SRC_DIR)/vectors/vec3_cmp.c \
			$(SRC_DIR)/vectors/vec3_cross.c \
			$(SRC_DIR)/vectors/vec3_cos.c \
			$(SRC_DIR)/vectors/vec3_dot.c \
			$(SRC_DIR)/vectors/vec3_len.c \
			$(SRC_DIR)/vectors/vec3_new.c \
			$(SRC_DIR)/vectors/vec3_normalize.c \
			$(SRC_DIR)/vectors/vec3_scale.c \
			$(SRC_DIR)/vectors/vec3_sub.c \
			$(SRC_DIR)/vectors/vec3_rgb_scale.c \
			$(SRC_DIR)/vectors/vec3_reflect.c \
		$(SRC_DIR)/ray/cam_data.c \
			$(SRC_DIR)/ray/ray.c \
		$(SRC_DIR)/object_intersection/hit_objects.c \
			$(SRC_DIR)/object_intersection/hit_cylinder.c \
			$(SRC_DIR)/object_intersection/hit_sphere.c \
			$(SRC_DIR)/object_intersection/hit_plane.c \
			$(SRC_DIR)/object_intersection/hit_triangle.c \
		$(SRC_DIR)/lighting/ambient_light.c \
			$(SRC_DIR)/lighting/diffuse.c \
			$(SRC_DIR)/lighting/shade_hit.c \
			$(SRC_DIR)/lighting/support_lighting.c \
		$(SRC_DIR)/render/render.c \
			$(SRC_DIR)/render/normal.c \
			$(SRC_DIR)/render/low_render.c \
			$(SRC_DIR)/render/transition.c \
		$(SRC_DIR)/graphics/events.c \
			$(SRC_DIR)/graphics/minilibx_setup.c \
		$(SRC_DIR)/animation/image.c \
			$(SRC_DIR)/animation/action.c \
			$(SRC_DIR)/animation/updates.c \
		$(SRC_DIR)/editor/edit_camera.c \
			$(SRC_DIR)/editor/edit_obj.c \
			$(SRC_DIR)/editor/move_obj.c  \
			$(SRC_DIR)/editor/angule_obj.c  \
			$(SRC_DIR)/editor/size_obj.c  \
			$(SRC_DIR)/editor/color_obj.c  \
			$(SRC_DIR)/editor/add_obj.c  \
			$(SRC_DIR)/editor/remove_obj.c  \
			$(SRC_DIR)/editor/add_light.c  \
			$(SRC_DIR)/editor/remove_light.c  \
			$(SRC_DIR)/editor/edit_light.c  \
			$(SRC_DIR)/editor/hit_light.c  \
			$(SRC_DIR)/editor/pos_light.c  \
			$(SRC_DIR)/editor/save_scene.c \
		$(SRC_DIR)/menu/start_menu.c \
		$(SRC_DIR)/menu/load_scenes.c \

OBJS        = $(SRC:.c=.o)
OBJS_BONUS  = $(SRC_BONUS:.c=.o)

# Colors
GREEN       = \033[32m
YELLOW      = \033[33m
RED         = \033[31m
RESET       = \033[0m

# Rules
.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: $(NAME_BONUS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(YELLOW)Cloning minilibx...$(RESET)"; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@$(MAKE) -s -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1 || true
	@echo "$(GREEN)✓ MLX ready!$(RESET)"


%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiled:$(RESET) $<"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) ready!$(RESET)"

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(RED)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C @$(MLX_DIR) clean --no-print-directory 2>/dev/null || true
	@echo "$(RED)Cleaned executables$(RESET)"

re: fclean all
