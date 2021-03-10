# **************************************************************************** #
#                                                                              #
#                                                        ..eeeee..             #
#    Makefile                                          e8'   8   '8e           #
#                                                     d8     8     8b          #
#    By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8          #
#                                                     Y8 .e* 8 *e. 8P          #
#    Created: xxxx/xx/xx xx:xx:xx by dries             *8*   8   *8*           #
#    Updated: 2021/03/10 17:39:34 by dries               **ee8ee**             #
#                                                                              #
# **************************************************************************** #

#CONTAINERS 	=	list vector stack queue
CONTAINERS 	=	list
INCL		=	$(CONTAINERS:%=-I%)

TESTFILES 	=	$(CONTAINERS:%=tests/test_%.o)
OFILES		=	$(TESTFILES:%.cpp=%.o)

DFLAGS		=
ifeq ($(F), 1)
	DFLAGS += -fsanitize=address
endif
ifeq ($(G), 1)
	DFLAGS += -g
endif
#ifeq ($(VERBOSE), 1)¬
	#DLAGS += -D DISPLAY
#endif
FTFLAGS		=	-Wall -Wextra -Werror
CFLAGS		=	-pedantic -std=c++98 $(DFLAGS)
CXX			=	clang++


all: $(CONTAINERS)

#test_%.o: test_%.cpp
	#$(CXX) $(CFLAGS) -c $< -o $@ $(INCL)

%.o: %.cpp
ifeq ($(NO_FT), 1)
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCL)
else
	$(CXX) $(FTFLAGS) $(CFLAGS) -c $< -o $@ $(INCL)
endif


$(CONTAINERS): $(OFILES)
ifeq ($(MAIN), 1)
	$(CXX) $(CFLAGS) main.cpp -o test_$@ $(INCL)
else
	$(CXX) $(FTFLAGS) $(CFLAGS) tests/test_$@.o -o test_$@ $(INCL)
endif

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(CONTAINERS:%=test_%) test_map

re: fclean all

.PHONY: $(CONTAINERS) map
