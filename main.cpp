/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   main.cpp                                          e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: xxxx/xx/xx xx:xx:xx by dries             *8*   8   *8*          */
/*   Updated: 2021/03/25 12:43:40 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#include "list/list.hpp"
#include <list>
#include "vector/vector.hpp"
#include <vector>
#include <iostream>

int		main(void) {
	std::vector<int>	*vec = new std::vector<int>(10, 10);;

	for (std::vector<int>::iterator i = vec->begin(); i != vec->end(); i++) {
		std::cout << *i << ", ";
	}

	std::cout << std::endl;
	vec->assign(vec->begin() + 2, vec->end() - 1);
	for (std::vector<int>::iterator i = vec->begin(); i != vec->end(); i++) {
		std::cout << *i << ", ";
	}
	std::cout << std::endl;
	return 0;
}
