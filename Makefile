# **************************************************************************** #
#							PROJECT'S DIRECTORY								   #
# **************************************************************************** #

NAME = Cl4ssB4ttle
INCL_DIR = includes/
SRC_DIR = src
UTILS_DIR = 

# **************************************************************************** #
#						COMPILATION AND LINK FLAGS							   #
# **************************************************************************** #

CC = g++-11
CFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
LIB_FLAGS = 

# **************************************************************************** #
#								SOURCE FILES								   #
# **************************************************************************** #

SRC = $(SRC_DIR)/main.cpp \
	$(SRC_DIR)/Character.cpp \
	$(SRC_DIR)/Shadow.cpp \
	$(SRC_DIR)/Berserk.cpp \
	$(SRC_DIR)/Guardian.cpp

OBJS = $(SRC:.cpp=.o)

# **************************************************************************** #
#								COLORS										   #
# **************************************************************************** #

BOLD = \033[1m
ITAL = \033[3m
UNDL = \033[4m
BLNK = \033[5m
REVR = \033[7m
GR = \033[32;1m
RE = \033[31;1m
YE = \033[33;1m
CY = \033[36;1m
RC = \033[0m

# **************************************************************************** #
#							MAKEFILE RULES									   #
# **************************************************************************** #

export NOW := $(shell date '+%F_%H:%M:%S')

all: ${NAME}

$(NAME): compile ${OBJS} c_done
	@printf "$(YE) Linking...$(RC)\n"
	@${CC} ${CFLAGS} ${OBJS} ${LIB_FLAGS} -o ${NAME}
	@printf "$(GR) => Success !$(RC)\n\n" 

.cpp.o:
	@${CC} ${CFLAGS} -o $@ -c $<
	@printf "$(GR)$(REVR) $(RC)"

compile:
	@echo "\n$(GR)[X] Compiling ${NAME}$(RC)\n"

c_done:
	@echo "$(GR) => 100%$(RC)\n"

clean:
	@printf "\n$(YE)Cleaning...\n"
	@rm -f ${OBJS}
	@printf "\n$(GR)=> Cleaning complete!$(RC)\n\n"

fclean: clean
	@printf "$(YE)Delete ${NAME}...\n"
	@rm -f ${NAME}
	@printf "\n$(GR)=> ${NAME} deleted!$(RC)\n\n"

git:
	git add .
	git commit -m "Upload by $(LOGNAME) $(NOW)"
	git push

launch: all
	./$(NAME)

re: fclean all

vg: all
	@valgrind --leak-check=full --track-origins=yes ./${NAME}

test: all
	./${NAME}

leaks: all
	leaks -atExit -- ./${NAME}

.PHONY: all bonus clean fclean launch re