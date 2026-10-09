NAME = miniSnake
CXX = clang++
FLAGS = -Wall -Wextra
RM = rm -f


# Sources
SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	@$(CXX) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

