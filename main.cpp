/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 13:09:54 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/24 15:14:08 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list/list.hpp"
#include <list>
#include <iostream>

//int		main(void) {
	//char str[] = "hello";

	//ft::list<char>  list(str, str + sizeof(str));

	//while (list.size()) {
		//std::cout << list.front() << std::endl;
		//list.pop_front();
	//}
//}

int		main(void) {
	std::list<int>			*l1 = new std::list<int>();
	std::list<int>::reverse_iterator	std_iter;
	std::list<int>::iterator			std_iter2;

	ft::list<int>			*l2 = new ft::list<int>();
	ft::list<int>::reverse_iterator	ft_iter;
	ft::list<int>::iterator			ft_iter2;

	std::cout << "std_list: " << std::endl << "  ";
	for (int i=1; i<=4; ++i) {
		std::cout << i << ", ";
		l1->push_back(i);
	}
	std::cout << std::endl;

	std::cout << "ft_list: " << std::endl << "  ";
	for (int i=1; i<=4; ++i) {
		std::cout << i << ", ";
		l2->push_back(i);
	}
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "for ( iter = begin(); iter != end(); iter++ )" << std::endl;
	std::cout << "  std:" << std::endl << "    ";
	for (std_iter2 = l1->begin(); std_iter2 != l1->end(); ++std_iter2) {
		std::cout << *std_iter2 << ", ";
	}
	std::cout << std::endl;

	std::cout << "  ft:" << std::endl << "    ";
	for (ft_iter2 = l2->begin(); ft_iter2 != l2->end(); ++ft_iter2) {
		std::cout << *ft_iter2 << ", ";
	}
	std::cout << std::endl;

	std::cout << "for ( iter = rbegin(); iter != rend(); iter++ )" << std::endl;
	std::cout << "  std:" << std::endl << "    ";
	for (std_iter = l1->rbegin(); std_iter != l1->rend(); ++std_iter) {
		std::cout << *std_iter << ", ";
	}
	std::cout << std::endl;

	std::cout << "  ft:" << std::endl << "    ";
	for (ft_iter = l2->rbegin(); ft_iter != l2->rend(); ++ft_iter) {
		std::cout << *ft_iter << ", ";
	}
	std::cout << std::endl;

	std_iter2 = l1->end();


	//create for loops that iterate from end to begin
	//	add a default node that is pointed at by head->prev and end->next (and vice versa) as a start point for end and rend



	//std::cout << "std\tbegin(); loop ++" << std::endl;
	//std_iter2 = l1->begin();
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *std_iter2 << ", ";
		//if (i != 3)
			//std_iter2++;
	//}
	//std::cout << std::endl;

	//std::cout << "ft\tbegin(); loop ++" << std::endl;
	//ft_iter2 = l2->begin();
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *ft_iter2 << ", ";
		//if (i != 3)
			//ft_iter2++;
	//}
	//std::cout << std::endl;


	//std::cout << "std\tbegin(); loop --" << std::endl;
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *std_iter2 << ", ";
		//if (i != 3)
			//std_iter2--;
	//}
	//std::cout << std::endl;

	//std::cout << "ft\tbegin(); loop --" << std::endl;
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *ft_iter2 << ", ";
		//if (i != 3)
			//ft_iter2--;
	//}
	//std::cout << std::endl;



	//std::cout << "std\tend(); loop --" << std::endl;
	//std_iter2 = l1->end();
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *std_iter2 << ", ";
		//std_iter2--;
	//}
	//std::cout << std::endl;

	//std::cout << "ft\tend(); loop --" << std::endl;
	//ft_iter2 = l2->end();
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *ft_iter2 << ", ";
		//ft_iter2--;
	//}
	//std::cout << std::endl;


	//std::cout << "std\tend(); loop ++" << std::endl;
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *std_iter2 << ", ";
		//std_iter2++;
	//}
	//std::cout << std::endl;

	//std::cout << "ft\tend(); loop ++" << std::endl;
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *ft_iter2 << ", ";
		//ft_iter2++;
	//}
	//std::cout << std::endl;



	//std::cout << "std\trbegin(); loop ++" << std::endl;
	//std_iter = l1->rbegin();
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *std_iter << ", ";
		//std_iter++;
	//}
	//std::cout << std::endl;

	//std::cout << "ft\trbegin(); loop ++" << std::endl;
	//ft_iter = l2->rbegin();
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *ft_iter << ", ";
		//ft_iter++;
	//}
	//std::cout << std::endl;


	//std::cout << "std\trbegin(); loop --" << std::endl;
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *std_iter << ", ";
		//std_iter--;
	//}
	//std::cout << std::endl;

	//std::cout << "ft\trbegin(); loop --" << std::endl;
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *ft_iter << ", ";
		//ft_iter--;
	//}
	//std::cout << std::endl;



	//std::cout << "std\trend(); loop ++" << std::endl;
	//std_iter = l1->rend();
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *std_iter << ", ";
		//std_iter++;
	//}
	//std::cout << std::endl;

	//std::cout << "ft\trend(); loop ++" << std::endl;
	//ft_iter = l2->rend();
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *ft_iter << ", ";
		//ft_iter++;
	//}
	//std::cout << std::endl;

	//std::cout << "std\trend(); loop --" << std::endl;
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *std_iter << ", ";
		//std_iter--;
	//}
	//std::cout << std::endl;

	//std::cout << "ft\trend(); loop --" << std::endl;
	//for (int i = 0; i < 4; ++i) {
		//std::cout << *ft_iter << ", ";
		//ft_iter--;
	//}
	//std::cout << std::endl;

	delete l1;
	delete l2;
	return 0;
}
