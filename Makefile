# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/25 21:10:51 by kbatz             #+#    #+#              #
#    Updated: 2019/01/17 20:15:31 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= project
LIB		= libft

# **************************************************************************** #

SRCDIR	= src/
OBJDIR	= .obj/
HDRDIR	= include/
TESTDIR	= test/

# **************************************************************************** #

LIBDIR	= $(addsuffix /,$(LIB))
LHD		= $(addsuffix $(HDRDIR),$(LIBDIR))
#LHD		= $(LIBDIR)
SRC		= $(patsubst $(SRCDIR)%,%,$(wildcard $(SRCDIR)*.c))
OBJ		= $(SRC:%.c=%.o)
HDR		= $(wildcard $(HDRDIR)*.h)
TEST	= $(patsubst $(TESTDIR),%,$(wildcard $(TESTDIR)*))
LFLAG	= $(addprefix -L,$(LIBDIR)) $(addprefix -,$(patsubst lib%,l%,$(LIB)))
IFLAG	= $(addprefix -I,$(HDRDIR)) $(addprefix -I,$(LHD))
CFLAG	= -Wall -Wextra -Werror

# **************************************************************************** #

vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

# **************************************************************************** #

all: $(addsuffix .all,$(LIB)) $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	gcc $(addprefix $(OBJDIR), $(OBJ)) -o $(NAME) $(IFLAG) $(LFLAG)

$(OBJ): %.o: %.c $(HDR)
	gcc $(CFLAG) $(IFLAG) -c $< -o $(OBJDIR)$@

$(OBJDIR):
	mkdir $(OBJDIR)

clean: $(addsuffix .fclean,$(LIB))
	rm -Rf $(OBJDIR)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

lib%:
	make -C $(subst .,/ ,$@)

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
