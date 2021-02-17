/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 13:09:54 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/17 14:31:01 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list/list.hpp"
#include <iostream>

int		main(void) {
	ft::list<int>			*l = new ft::list<int>();
	ft::list<int>			*l2 = new ft::list<int>(static_cast<size_t>(5), 5);

	l->push_back(1);
	std::cout << l->front() << std::endl;
	std::cout << l->back() << std::endl;
	l->push_back(2);
	std::cout << l->back() << std::endl;
	l->push_back(3);
	std::cout << l->back() << std::endl;
	l->push_back(4);
	std::cout << l->back() << std::endl;
	std::cout << l2->front() << std::endl;
	std::cout << l2->back() << std::endl;

	delete l;
	delete l2;
	return 0;
}
