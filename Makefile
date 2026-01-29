# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 20:19:38 by lde-san-          #+#    #+#              #
#    Updated: 2026/01/29 22:49:31 by lde-san-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a
MISO_LIB = obj/libmisoverse.a

NEOR	= \033[3m\033[38;2;255;153;51m
MINT    = \033[1;38;2;55;250;133m
PURP	= \033[1;38;2;174;5;252m
ORNG    = \033[38;2;255;153;51m
BABY    = \033[38;2;0;255;247m
BLOD	= \033[1;38;2;255;0;0m
LIME    = \033[38;2;0;255;0m
BLAK	= \033[38;2;0;0;0m
B_WI    = \033[1;37m
RSET	= \033[0m

SRC_DIR = src/
OBJ_DIR = obj/

MAIN_FILE = $(SRC_DIR)miso_main.c

FILE = miso_launch.c
FILE += miso_pathfinder.c
FILE += miso_redirection.c
FILE += miso_exec_utils_beta.c
FILE += miso_exec_utils_alpha.c

SRC = $(addprefix $(SRC_DIR),$(FILE))

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

.PRECIOUS: $(SRC) $(SRC_BONUS)

COMPILE = cc -g -O0 -Wall -Werror -Wextra -lreadline -I./inc

all: $(NAME)

$(NAME): $(LIBFT) $(MISO_LIB) ./inc/miso_structs.h ./inc/miso.h
	@printf "$(BABY)"
	$(COMPILE) $(LIBFT) $(MISO_LIB) $(MAIN_FILE) -o $(NAME)
	@printf "$(MINT)"
	@ls -la
	@printf "$(RSET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c ./inc/miso_structs.h ./inc/miso.h | $(OBJ_DIR)
	@printf "$(PURP)"
	$(COMPILE) -c $< -o $@
	@printf "$(RSET)\n"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

open:
	@printf "$(MINT)"
	find . -maxdepth 2 -name "*.c" -exec xdg-open {} \;
	@printf "$(ORNG)"
	find . -maxdepth 2 -name "*.h" -exec xdg-open {} \;
	@printf "$(RSET)"

$(LIBFT):
	@printf "$(NEOR)"
	@make -C ./inc/libft
	@printf "$(RSET)"

$(MISO_LIB): $(OBJ)
	@ar -rcs $@ $^

clean:
	@printf "$(LIME)"
	@make -C ./inc/libft clean
	@sleep 0.3
	@printf "$(BLOD)"
	rm -rf $(OBJ_DIR)
	@sleep 0.3
	@printf "$(RSET)"

fclean: clean
	@printf "$(B_WI)"
	@make -C ./inc/libft fclean
	@sleep 0.3
	@printf "$(PURP)"
	rm -f $(NAME)
	@printf "$(MINT)"
	@sleep 0.3
	@ls -la
	@printf "$(RSET)"

re: fclean all

.PHONY: all clean fclean re bonus open
