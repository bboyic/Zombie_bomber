NAME		=	bomber
CC			=	c++
SRC			=	src/
INCLUDES	=	includes/
H_FILES		=	main.h Unit.h Map.h
SRC_FILES	=	main.cpp Unit.cpp Map.cpp
HEADERS		=	$(addprefix $(INCLUDES), $(H_FILES))
CPP_FILES	=	$(addprefix $(SRC), $(SRC_FILES))
O_FILES		=	$(CPP_FILES:.cpp=.opp)

%.opp: %.cpp $(HEADERS)
	$(CC) -o $@ -c $< -I $(INCLUDES)

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) -o $(NAME) $(O_FILES) -I $(INCLUDES)

clean:
	rm -rf $(O_FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONE: all clean fclean re