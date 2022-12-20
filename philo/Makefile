# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2022/12/20 16:31:31 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
CC				= cc
RM				= rm -f
CFLAGS			= #-Wall -Wextra -Werror


LIB_DIR			= lib
LIBFT_DIR		= $(LIB_DIR)/libft
LIBFT_LIB		= libft.a
LIBFT			= $(LIBFT_DIR)/$(LIBFT_LIB)
LIBFT_GIT		= https://github.com/fsandel/libft

SRC				= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_DIR			= src
SRC_FILES		= main.c


OBJ				= $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))
OBJ_DIR			= obj
OBJ_FILES		= $(SRC_FILES:.c=.o)

HDR				= $(addprefix $(HDR_DIR)/, $(HDR_FILES))
HDR_DIR			= include
HDR_FILES		= philo.h


all:			obj_dir $(LIBFT) $(NAME)
				
$(NAME):		$(OBJ) | $(HDR)
				@$(CC) $^ $(LIBFT) -o $@ $(CFLAGS)
				@echo "created $@"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@$(CC) -c $< $(CFLAGS) -o $@
				@echo "created $@"

clean:
				@$(RM) $(OBJ)
				@$(RM) -r $(OBJ_DIR)
				@make clean -C $(LIBFT_DIR)
				@echo "cleaned $(NAME)"

fclean:			
				@make clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@echo "fcleaned $(NAME)"


re:
				@make fclean
				@make all

libft:			$(LIBFT)

obj_dir:
				@mkdir -p $(OBJ_DIR)


$(LIBFT):
				@make clone_libft
				@make -C $(LIBFT_DIR)

clone_libft:
ifeq ($(shell (ls $(LIB_DIR) | grep libft)), libft)
				@echo "libft found"
else
				@echo "no libft found, downloading now"
				@git clone $(LIBFT_GIT) $(LIBFT_DIR)
endif

.PHONY:			all clean fclean re libft clone_libft
