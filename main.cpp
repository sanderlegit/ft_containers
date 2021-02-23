/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 13:09:54 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/23 14:19:33 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list/list.hpp"
#include <list>
#include <iostream>

int		main(void) {
	std::list<int>			*l1 = new std::list<int>();
	ft::list<int>			*l2 = new ft::list<int>(5, 5);

	delete l1;
	delete l2;
	return 0;
}
