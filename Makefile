# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 04:16:06 by kbatz             #+#    #+#              #
#    Updated: 2018/12/22 18:23:48 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRJNAME	= project
NAME	= $(PRJNAME)
LIB		= libft
SRCDIR	= ./src/
OBJDIR	= ./.obj/
HDRDIR	= ./include/
TESTDIR	= ./test/
LIBDIR	= ./$(LIB)/
SRC		= $(patsubst $(SRCDIR)%, %, $(wildcard $(SRCDIR)*.c))
OBJ		= $(SRC:%.c=%.o)
HDR		= $(wildcard $(HDRDIR)*.h)
TEST	= $(patsubst $(TESTDIR), %, $(wildcard $(TESTDIR)*))
LFLAG	= -I$(LIBDIR) -L$(LIBDIR) -$(subst lib, l, $(LIB)) # double -I
IFLAG	= -I$(HDRDIR)
CFLAG	= -Wall -Wextra -Werror
FLAGS	= $(CFLAG) $(IFLAG)

vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

all: $(NAME)

$(NAME): $(LIB)all $(OBJDIR) $(OBJ)
	echo $(SRC)
	gcc $(addprefix $(OBJDIR), $(OBJ)) -o $(NAME)

$(OBJ): %.o: %.c $(HDR)
	gcc $(FLAGS) -c $< -o $(OBJDIR)$@

$(OBJDIR):
	mkdir $(OBJDIR)

clean: $(LIB)fclean
	rm -Rf $(OBJDIR)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

$(LIB)%:
	make -C $(LIBDIR) $(patsubst $(LIB)%, %, $@)

norm:
	norminette $(addprefix $(SRCDIR), $(SRC))
	norminette $(addprefix $(HDRDIR), $(HDR))

t: all $(TEST)

$(TEST): %:
	@echo "--------------------------------------------------"
	@echo "| >>>>> TEST \""$@"\" START >>>>> |"
	@echo ""
	@./$(NAME) $(TESTDIR)$@
	@echo ""
	@echo "| <<<<< TEST \""$@"\" END <<<<< |"
	@echo "--------------------------------------------------"
