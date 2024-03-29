# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2023/01/18 15:55:55 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRC				= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_DIR			= src
SRC_FILES		= main.c lifestyle.c time.c utils.c input.c setup.c thread.c waitress.c

OBJ				= $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))
OBJ_DIR			= obj
OBJ_FILES		= $(SRC_FILES:.c=.o)

HDR				= $(addprefix $(HDR_DIR)/, $(HDR_FILES))
HDR_DIR			= include
HDR_FILES		= philo.h

GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"

all:			obj_dir $(NAME)
				
$(NAME):		$(OBJ) | $(HDR)
				@$(CC) $^ -o $@ $(CFLAGS)
				@echo $(GREEN)Compiled$(DEFAULT) $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@echo $(LGREEN)Compiling$(DEFAULT) $<
				@$(CC) -c $< $(CFLAGS) -o $@

clean:
				@$(RM) $(OBJ)
				@$(RM) -r $(OBJ_DIR)
				@echo "cleaned $(NAME)"

fclean:			
				@make clean
				@$(RM) $(NAME)
				@echo "fcleaned $(NAME)"

re:
				@make fclean
				@make all

obj_dir:
				@mkdir -p $(OBJ_DIR)

.PHONY:			all clean fclean re obj_dir
