NAME = bistro.exec

SRC = 	bistro.cpp \
		token.cpp \
		main.cpp \
		number.cpp \
		utility.cpp \
		operation.cpp 
		
HEADER = -I.

OBJDIR = ./objdir

all : $(NAME)

$(NAME) : 
	g++ -std=c++11 -ggdb3 -Wall -Wextra $(HEADER) -c $(SRC) 
	g++ -o $(NAME)   *.o 
	mv *.o $(OBJDIR)
	
clean : 
	rm -f $(OBJDIR)/*.o

fclean : clean
	rm -f $(NAME)

re : fclean all