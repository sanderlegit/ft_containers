# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: averheij <averheij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/15 16:29:54 by averheij      #+#    #+#                  #
#    Updated: 2021/02/18 12:33:59 by averheij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#CONTAINERS 	=	list vector stack queue
CONTAINERS 	=	list
INCL		=	$(CONTAINERS:%=-I%)

TESTFILES 	=	$(CONTAINERS:%=tests/test_%.o)
OFILES		=	$(TESTFILES:%.cpp=%.o)

CFLAGS		=	-Wall -Wextra -Werror -pedantic -std=c++98
CXX			=	g++

ifeq ($(DEBUG), 1)
	CFLAGS += -g -fsanitize=address
endif

all: $(CONTAINERS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(INCL)

#tests/test_%.o: tests/test_%.cpp
	#$(CXX) -c $< -o $@ $(INCL)

$(CONTAINERS): $(OFILES)
ifeq ($(MAIN), 1)
	#$(CXX) $(CFLAGS) main.cpp -o test_$@ $(INCL)
else
	#$(CXX) $(CFLAGS) tests/test_$@.cpp -o test_$@ $(INCL)
	$(CXX) $(CFLAGS) tests/test_$@.o -o test_$@ $(INCL)
endif

#map:
	#$(CXX) $(CFLAGS) -I ./map test_$@.cpp ./map/Map.cpp -o test_$@ -I . -I $(ITER_INC) -I $(UTIL_INC) -I $(MISC_INC) $(INCL) -D FT=$(FT)

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(CONTAINERS:%=test_%) test_map

re: fclean all

.PHONY: $(CONTAINERS) map
