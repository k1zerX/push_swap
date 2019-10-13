# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/25 21:10:51 by kbatz             #+#    #+#              #
#    Updated: 2019/10/13 21:39:24 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1	= push_swap
NAME2	= checker
LIB		= libft

# **************************************************************************** #

SRCDIR	= src/
OBJDIR	= .obj/
HDRDIR	= include/
TESTDIR	= test/

# **************************************************************************** #

LIBDIR	= $(addsuffix /,$(LIB))
LHD		= $(addsuffix $(HDRDIR),$(LIBDIR))
SRC		= $(patsubst $(SRCDIR)%,%,$(wildcard $(SRCDIR)*.c))
OBJ		= $(SRC:%.c=%.o)
HDR		= $(wildcard $(HDRDIR)*.h)
TEST	= $(patsubst $(TESTDIR),%,$(wildcard $(TESTDIR)*))
LFLAG	= $(addprefix -L,$(LIBDIR)) $(addprefix -,$(patsubst lib%,l%,$(LIB)))
IFLAG	= $(addprefix -I,$(HDRDIR)) $(addprefix -I,$(LIBDIR))
CFLAG	= #-Wall -Wextra -Werror

# **************************************************************************** #

vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

# **************************************************************************** #

all: lib.all $(NAME1) $(NAME2)

$(NAME1): $(OBJDIR) $(filter-out $(NAME2).o,$(OBJ))
	gcc $(addprefix $(OBJDIR), $(filter-out $(NAME2).o,$(OBJ))) -o $(NAME1) $(IFLAG) $(LFLAG)

$(NAME2): $(OBJDIR) $(filter-out $(NAME1).o,$(OBJ))
	gcc $(addprefix $(OBJDIR), $(filter-out $(NAME1).o,$(OBJ))) -o $(NAME2) $(IFLAG) $(LFLAG)

$(OBJ): %.o: %.c $(HDR)
	gcc $(CFLAG) $(IFLAG) -c $< -o $(OBJDIR)$@

$(OBJDIR):
	mkdir $(OBJDIR)

clean: lib.fclean
	rm -Rf $(OBJDIR)

fclean: clean
	rm -Rf $(NAME1)
	rm -Rf checker

re: fclean all

lib%:
	$(foreach C, $(LIBDIR), \
		make -C $(C) $(patsubst lib.%,%,$@) \
	)

norm:
	norminette $(addprefix $(SRCDIR), $(SRC))
	norminette $(addprefix $(HDRDIR), $(HDR))

g: $(OBJDIR) $(OBJ)
	gcc -g $(addprefix $(SRCDIR), $(SRC)) -o debug_$(NAME1) $(IFLAG) $(LFLAG)

gclean:
	rm -Rf debug_$(NAME1)
	rm -Rf debug_$(NAME1).dSYM

t: all $(TEST)

$(TEST): %:
	@echo "--------------------------------------------------"
	@echo "| >>>>> TEST \""$@"\" START >>>>> |"
	@echo ""
	@./$(NAME1) $(TESTDIR)$@
	@echo ""
	@echo "| <<<<< TEST \""$@"\" END <<<<< |"
	@echo "--------------------------------------------------"
