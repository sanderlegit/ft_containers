/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   main.cpp                                          e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: xxxx/xx/xx xx:xx:xx by dries             *8*   8   *8*          */
/*   Updated: 2021/03/15 15:24:06 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#include "list/list.hpp"
#include <list>
#include <iostream>

int		main(void) {

	for (int i = 2; i < 5000000; i = i << 2 ) {
		std::cout << "i: " << i << std::endl;
	}
	return 0;
}
