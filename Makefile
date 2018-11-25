# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/19 20:49:31 by kbatz             #+#    #+#              #
#    Updated: 2018/11/20 15:50:39 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_display_file
SRCSDIR = srcs/
SRCS = $(patsubst $(SRCSDIR)%, %, $(wildcard $(SRCSDIR)*.c))
HDRSDIR = includes/
HDRS = $(wildcard $(HDRSDIR)*.h)
OBJSDIR = objs/
OBJS = $(SRCS:.c=.o)
ADDFLAGS = -I $(HDRSDIR)
FLAGS = -Wall -Wextra -Werror
TESTSDIR = tests/
TESTS = $(patsubst $(TESTSDIR)%, %, $(wildcard $(TESTSDIR)*.test))

vpath %.c $(SRCSDIR)
vpath %.o $(OBJSDIR)
vpath %.test $(TESTSDIR)

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJS) $(HDRS)
	echo $(TESTS)
	gcc $(addprefix $(OBJSDIR), $(OBJS)) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) $(ADDFLAGS) -c $< -o $(OBJSDIR)$@

clean:
	rm -Rf $(addprefix $(OBJSDIR), $(OBJS))
	rm -Rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(OBJSDIR):
	mkdir $(OBJSDIR)

norm:
	norminette $(HDDRSDIR) $(SRCSDIR)

ft_test: $(TESTS)
	echo $(TESTS)

$(TESTS):
	echo "||| ------- test start ------- |||"
	./$(NAME) $(TESTDIR)$(TESTS)
	echo "||| -------- test end -------- |||"

