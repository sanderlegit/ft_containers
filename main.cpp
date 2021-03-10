/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   main.cpp                                          e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: xxxx/xx/xx xx:xx:xx by dries             *8*   8   *8*          */
/*   Updated: 2021/03/10 17:39:17 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#include "list/list.hpp"
#include <list>
#include <iostream>

int		main(void) {
	std::list<int>			*l1 = new std::list<int>(5, 20);
	std::list<int>			*l3 = new std::list<int>();

	l1->splice(l1->begin(), *l3, l3->begin());
	while (l1->size()) {
		l1->pop_front();
	}

	l3->size();
	std::cout << l3->empty() << std::endl;

	delete l1;
	delete l3;
	return 0;
}
