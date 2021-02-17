/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 13:09:54 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/17 16:07:23 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list/list.hpp"
#include <iostream>

int		main(void) {
	ft::list<int>			*l = new ft::list<int>();
	ft::list<int>			*l2 = new ft::list<int>(static_cast<size_t>(5), 5);

	std::cout << "l" << std::endl;
	l->push_back(1);
	std::cout << "front " << l->front() << std::endl;
	std::cout << "back " << l->back() << " size " << l->size() << std::endl;
	l->push_back(2);
	std::cout << "back " << l->back() << " size " << l->size() << std::endl;
	l->push_back(3);
	std::cout << "back " << l->back() << " size " << l->size() << std::endl;
	l->push_back(4);
	std::cout << "back " << l->back() << " size " << l->size() << std::endl;
	l->pop_back();
	std::cout << "back " << l->back() << " size " << l->size() << std::endl;
	l->pop_back();
	std::cout << "back " << l->back() << " size " << l->size() << std::endl;
	l->pop_back();
	std::cout << "back " << l->back() << " size " << l->size() << std::endl;
	l->pop_back();

	std::cout << "l2" << std::endl;
	std::cout << "back " << l2->back() << " size " << l2->size() << std::endl;
	std::cout << "back " << l2->back() << " size " << l2->size() << std::endl;
	l2->push_front(10);
	std::cout << "front " << l2->front() << " size " << l2->size() << std::endl;
	l2->push_front(20);
	std::cout << "front " << l2->front() << " size " << l2->size() << std::endl;
	l2->pop_front();
	std::cout << "front " << l2->front() << " size " << l2->size() << std::endl;

	std::cout << "delete l" << std::endl;
	delete l;
	std::cout << "delete l2" << std::endl;
	delete l2;
	return 0;
}
