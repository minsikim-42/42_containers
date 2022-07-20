NAME = 
CXXCC = clang++ -std=c++98
CXXFLAGS = -Wall -Wextra -Werror
CPP = 
OBJECT = $(CPP:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJECT)
	$(CXXCC) $(CXXFLAGS) -o $(NAME) $(OBJECT)

$(OBJECT) : $(CPP)
	$(CXXCC) $(CXXFLAGS) -c $(CPP)

clean :
	rm -f $(OBJECT)

fclean :
	rm -f $(NAME) $(OBJECT)

re : fclean all

.PHONY : all clean fclean