NAME	=	ircserv
SRCS	=	$(wildcard srcs/*.cpp) \
			$(wildcard srcs/Server/*.cpp) \
			$(wildcard srcs/Client/*.cpp)

OBJS	=	$(SRCS:.cpp=.o)

CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address

all: $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	@$(RM)  $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re