# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/06 17:27:48 by alejandj          #+#    #+#              #
#    Updated: 2025/09/28 21:09:34 by alejandj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directorios
OBJDIR = obj/

# Archivos
SRC =	src/philo.c				\
		src/philo_utils_1.c		\
		src/philo_utils_2.c		\
		src/actions.c			\
		src/threads.c			\

OBJECTS = $(SRC:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

# Compilar el ejecutable
$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "\033[0;34m✅ Philosophers compiled successfully!\033[0m"
	@echo "  _____ _     _ _                       _                   "
	@echo " | ___ \\ |   (_) |                     | |                  "
	@echo " | |_/ / |__  _| | ___  ___  ___  _ __ | |__   ___ _ __ ___ "
	@echo " |  __/| '_ \\| | |/ _ \\/ __|/ _ \\| '_ \\| '_ \\ / _ \\ '__/ __|"
	@echo " | |   | | | | | | (_) \\__ \\ (_) | |_) | | | |  __/ |  \\__ \\"
	@echo " \\_|   |_| |_|_|_|\\___/|___/\\___/| .__/|_| |_|\\___|_|  |___/"
	@echo "                                 | |                        "
	@echo "                                 |_|                        "

# Regla para crear los .o en el directorio obj
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@echo "🧹 \033[0;32mObject files removed successfully! 🗑️\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "🚀 \033[0;32mExecutable $(NAME) has been removed!\033[0m"

re: fclean all

.PHONY: all clean fclean re