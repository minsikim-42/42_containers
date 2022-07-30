NAME = container
CXXCC = clang++ -std=c++98
CXXFLAGS = -Wall -Wextra -Werror
# -g
MAIN = main.cpp

OBJ = $(MAIN:.cpp=.o)

all : $(NAME)

$(NAME) :
	$(CXXCC) $(CXXFLAGS) -o $(NAME) $(MAIN)

clean :
	rm -f $(OBJ)

fclean :
	rm -f $(NAME) $(OBJ)

re : fclean all

.PHONY : all clean fclean