# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/19 20:49:31 by kbatz             #+#    #+#              #
#    Updated: 2018/11/27 12:55:07 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = run.exe
SRCSDIR = srcs/
SRCS = $(patsubst $(SRCSDIR)%, %, $(wildcard $(SRCSDIR)*.c))
HDRSDIR = includes/
HDRS = $(wildcard $(HDRSDIR)*.h)
OBJSDIR = .objs/
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
TESTSDIR = tests/
TESTS = $(patsubst $(TESTSDIR)%, %, $(wildcard $(TESTSDIR)*.test))

vpath %.c $(SRCSDIR)
vpath %.o $(OBJSDIR)
vpath %.t $(TESTSDIR)

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJS) $(HDRS)
	echo $(TESTS)
	gcc $(addprefix $(OBJSDIR), $(OBJS)) -o $(NAME)

$(OBJS): %.o: %.c
	gcc $(FLAGS) -I $(HDRSDIR) -c $< -o $(OBJSDIR)$@

clean:
	rm -Rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(OBJSDIR):
	mkdir $(OBJSDIR)

norm:
	norminette $(HDRSDIR) $(SRCSDIR)

t: $(TESTS)

$(TESTS): %.t:
	@echo ""
	@echo "||| >>>>>>> test start >>>>>>> |||"
	./$(NAME) $@
	@echo ""
	@echo "||| <<<<<<<< test end <<<<<<<< |||"

