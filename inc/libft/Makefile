# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 21:11:45 by lde-san-          #+#    #+#              #
#    Updated: 2025/10/16 14:02:13 by lde-san-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

COMPILE = cc -Wall -Werror -Wextra -I/includes.
OBJ = $(FILE:%.c=%.o)
OBJ_BONUS = $(FILE_BONUS:%.c=%.o)

FILE = ft_isalpha.c
FILE += ft_isdigit.c
FILE += ft_isalnum.c
FILE += ft_isascii.c
FILE += ft_isprint.c
FILE += ft_strlen.c
FILE += ft_memset.c
FILE += ft_bzero.c
FILE += ft_memcpy.c
FILE += ft_memmove.c
FILE += ft_strlcpy.c
FILE += ft_strlcat.c
FILE += ft_toupper.c
FILE += ft_tolower.c
FILE += ft_strchr.c
FILE += ft_strrchr.c
FILE += ft_strncmp.c
FILE += ft_memchr.c
FILE += ft_memcmp.c
FILE += ft_strnstr.c
FILE += ft_atoi.c
FILE += ft_calloc.c
FILE += ft_strdup.c
FILE += ft_substr.c
FILE += ft_strjoin.c
FILE += ft_strtrim.c
FILE += ft_split.c
FILE += ft_itoa.c
FILE += ft_strmapi.c
FILE += ft_striteri.c
FILE += ft_putchar_fd.c
FILE += ft_putstr_fd.c
FILE += ft_putendl_fd.c
FILE += ft_putnbr_fd.c
FILE += racc_print.c
FILE += racc_print_utils.c
FILE += get_next_line_bonus.c
FILE += get_next_line_utils_bonus.c

FILE_BONUS = ft_lstnew_bonus.c
FILE_BONUS += ft_lstadd_front_bonus.c
FILE_BONUS += ft_lstsize_bonus.c
FILE_BONUS += ft_lstlast_bonus.c
FILE_BONUS += ft_lstadd_back_bonus.c
FILE_BONUS += ft_lstdelone_bonus.c
FILE_BONUS += ft_lstclear_bonus.c
FILE_BONUS += ft_lstiter_bonus.c
FILE_BONUS += ft_lstmap_bonus.c

$(NAME): $(OBJ)
	@ar -rcs $@ $^

%.o: %.c
	$(COMPILE) -c $< -o $@
	
all: $(NAME)

bonus: $(OBJ) $(OBJ_BONUS)
	ar -rcs $(NAME) $(OBJ) $(OBJ_BONUS)
	
clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all bonus re clean fclean
