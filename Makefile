NAME = bistro.exec

SRC = 	bistro.cpp \
		add.cpp
		
HEADER = -I.

OBJDIR = 

all : $(NAME)

$(NAME) : 
	g++ -std=c++11 -ggdb3 -Wall -Wextra $(HEADER) -c $(SRC) 
	g++ -o $(NAME)   *.o 
	
	
clean : 
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all