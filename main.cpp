/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 13:09:54 by averheij      #+#    #+#                 */
/*   Updated: 2021/03/04 16:41:37 by dries            ###   ########.fr       */
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
