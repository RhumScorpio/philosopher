# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:57:32 by clesaffr          #+#    #+#              #
#    Updated: 2023/01/18 03:09:24 by clesaffr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	gcc

CFLAGS		=  -g3 -Wall -Werror -Wextra

SRCS		=	philosophers.c\
				philo_parsing.c\
				fork_exchange.c\
				initialize_philo.c\
				launcher_philo.c\
				death_checker.c\
				death_philo.c\
				print_philo.c\
				utils_philo.c
				
PATH_OBJS	=	.objs/

F_OBJS		=	$(addprefix $(PATH_OBJS), $(OBJS))

OBJS		=	$(SRCS:.c=.o)

UNAME		:= $(shell uname)

all				: $(PATH_OBJS) $(NAME)

$(PATH_OBJS)	:	
					mkdir -p $(PATH_OBJS)

$(NAME)			:	$(F_OBJS)
					$(CC) $(CFLAGS) $(F_OBJS) -lpthread -o $(NAME)

$(PATH_OBJS)%.o	:	%.c
						$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean			:
					rm -rf $(F_OBJS) $(PATH_OBJS)

fclean			:	clean
					rm -f $(NAME)

re				:	fclean all

.PHONY: clean fclean all re
