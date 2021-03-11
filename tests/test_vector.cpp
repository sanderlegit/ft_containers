/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   test_vector.cpp                                   e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/11 13:50:52 by dries             *8*   8   *8*          */
/*   Updated: 2021/03/11 14:31:22 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sstream>
#include <cstdio>

/*	stdlib		rand
 *	iostream	cout
 *	time		time
 *	string		memset
 *	sstream		string stream
 *	cstdio		printf
*/

#include <vector>
#include "vector.hpp"

#define WHITE "\033[37;01m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[m"
//#define VERBOSE	true
#define VERBOSE	false
//#define VVERBOSE	true
#define VVERBOSE	false
//#ifdef DISPLAY
	//#define VERBOSE	true
//#endif
//#ifndef DISPLAY
	//#define VERBOSE	false
//#endif

/*-----------------------------------UTIL-----------------------------------*/

template<class T>
struct data {
	int				pass;
	int				fail;
	int				current_fail;
};

template<class T>
data<T>		*init_data(void) {
	data<T>		*d = new data<T>;

	d->pass = 0;
	d->fail = 0;
	d->current_fail = 0;
	return d;
}

template<class T>
T			randomize(void) {
	T		val;
	void	*ptr;

	ptr = reinterpret_cast<void*>(&val);
	memset(ptr, (unsigned char)(rand() % 255), sizeof(T));
	return val;
}

/*-----------------------------------TEST TOOLS-----------------------------------*/

void		print_group_title(std::string str) {
	std::cout << BLUE << "\n##=====================#" << str << "#=====================##" << RESET << std::endl;
}

void		print_title(std::string str) {
	std::cout << BLUE << "          +--------+-" << str << "-+--------+" << RESET << std::endl;
}

template<class T, class R>
void		print_comp(std::string str, T t, R r) {
	if (VERBOSE) {
		printf("%-16s", str.c_str());
		std::cout << "std:";

		std::cout.width(16);
		std::cout.flags(std::ios::right);
		std::cout << t;
		std::cout.flags(std::ios::internal);
		std::cout.width(0);

		std::cout << "\tft:";

		std::cout.width(16);
		std::cout.flags(std::ios::right);
		std::cout << r << std::endl;
		std::cout.flags(std::ios::internal);
		std::cout.width(0);
	}
}

template<class T, class R>
void		print_comp_force(std::string str, T t, R r) {
	printf("%-16s", str.c_str());
	std::cout << "std:";

	std::cout.width(16);
	std::cout.flags(std::ios::right);
	std::cout << t;
	std::cout.flags(std::ios::internal);
	std::cout.width(0);

	std::cout << "\tft:";

	std::cout.width(16);
	std::cout.flags(std::ios::right);
	std::cout << r << std::endl;
	std::cout.flags(std::ios::internal);
	std::cout.width(0);
}

template<class T, class R>
void		print_comp_labels(std::string str, std::string l1, std::string l2, T t, R r) {
	if (VERBOSE) {
		printf("%-16s", str.c_str());
		l1.append(":");
		printf("%-4s", l1.c_str());
		//std::cout << l1 << ":";

		std::cout.width(16);
		std::cout.flags(std::ios::right);
		std::cout << t;
		std::cout.flags(std::ios::internal);
		std::cout.width(0);

		l2.append(":");
		printf("\t%-4s", l2.c_str());
		//std::cout << "\t" << l2 << ":";

		std::cout.width(15);
		std::cout.flags(std::ios::right);
		std::cout << r << std::endl;
		std::cout.flags(std::ios::internal);
		std::cout.width(0);
	}
}
template<class T, class R>
void		print_comp_force_labels(std::string str, std::string l1, std::string l2, T t, R r) {
	printf("%-16s", str.c_str());
	l1.append(":");
	printf("%-4s", l1.c_str());
	std::cout.width(16);
	std::cout.flags(std::ios::right);
	std::cout << t;
	std::cout.flags(std::ios::internal);
	std::cout.width(0);
	l2.append(":");
	printf("\t%-4s", l2.c_str());
	std::cout.width(15);
	std::cout.flags(std::ios::right);
	std::cout << r << std::endl;
	std::cout.flags(std::ios::internal);
	std::cout.width(0);
}

template<class T>
void		incr_score(data<T> *d) {
	std::cout << "  test:\t";
	if (d->current_fail == 0) {
		d->pass++;
		std::cout << GREEN << "pass" << RESET << std::endl << std::endl;
	} else {
		d->fail++;
		std::cout << RED << "fail" << RESET << std::endl << std::endl;
	}
	d->current_fail = 0;
}

template<class T>
void		check_pass(data<T> *d, bool score) {
	if (!score)
		d->current_fail++;
}
#define comp(A)		check_pass(d, A)

template<class T>
void		test_equivalence(data<T> *d, std::vector<T> *std, ft::vector<T> *ft, bool capacity) {
	bool			r1;
	bool			r2;
	T				r3;
	T				r4;
	size_t			r5;
	size_t			r6;


	if (VERBOSE)
		std::cout << "  testing list equality" << std::endl;
	r1 = std->empty();
	r2 = ft->empty();
	print_comp("empty()", r1, r2);
	comp(r1 == r2);

	if (capacity) {
		//r5 = std->capacity();
		//r6 = ft->capacity();
		print_comp("capacity()", r5, r6);
		comp(r5 == r6);
	}

	if (!r1 && !r2) {
		r3 = std->back();
		r4 = ft->back();
		r5 = std->size();
		r6 = ft->size();
		print_comp("back()", r3, r4);
		comp(r3 == r4);
		r3 = std->back();
		r4 = ft->back();
		std->pop_back();
		ft->pop_back();
		print_comp("back()", r3, r4);
		comp(r3 == r4);
		print_comp("size()", r5, r6);
		comp(r5 == r6);
		if (VERBOSE)
			std::cout << "  iterating through..." << std::endl;
		while (!std->empty() && !ft->empty()) {
			r1 = std->empty();
			r2 = ft->empty();
			r3 = std->back();
			r4 = ft->back();
			r5 = std->size();
			r6 = ft->size();
			std->pop_back();
			ft->pop_back();
			if (VVERBOSE)
				print_comp("back", r3, r4);
			if (VVERBOSE)
				print_comp("size", r5, r6);
			comp(r1 == r2);
			comp(r3 == r4);
			comp(r5 == r6);
		}
		r1 = std->empty();
		r2 = ft->empty();
		r5 = std->size();
		r6 = ft->size();
		print_comp("empty()", r1, r2);
		print_comp("size()", r5, r6);
	} else if (!r1 && r2) {
		r3 = std->back();
		r5 = std->size();
		print_comp_labels("back()", "std", "EMPTY!", r3, 0);
		r3 = std->back();
		std->pop_back();
		ft->pop_back();
		print_comp_labels("back()", "std", "EMPTY!", r3, 0);
		print_comp_labels("size()", "std", "EMPTY!", r5, 0);
		if (VERBOSE)
			std::cout << "  iterating through..." << std::endl;
		while (!std->empty()) {
			r1 = std->empty();
			r3 = std->back();
			r5 = std->size();
			std->pop_back();
			if (VVERBOSE)
				print_comp_labels("back", "std", "EMPTY!", r3, 0);
			if (VVERBOSE)
				print_comp_labels("size", "std", "EMPTY!", r5, 0);
		}
		r1 = std->empty();
		r5 = std->size();
		print_comp_labels("empty()", "std", "EMPTY!", r1, 0);
		print_comp_labels("size()", "std", "EMPTY!", r5, 0);
	} else if (r1 && !r2) {
		r3 = ft->back();
		r5 = ft->size();
		print_comp_labels("back()", "EMPTY!", "ft", 0, r3);
		r3 = ft->back();
		ft->pop_back();
		ft->pop_back();
		print_comp_labels("back()", "EMPTY!", "ft", 0, r3);
		print_comp_labels("size()", "EMPTY!", "ft", 0, r5);
		if (VERBOSE)
			std::cout << "  iterating through..." << std::endl;
		while (!ft->empty()) {
			r1 = ft->empty();
			r3 = ft->back();
			r5 = ft->size();
			ft->pop_back();
			if (VVERBOSE)
				print_comp_labels("back", "EMPTY!", "ft", 0, r3);
			if (VVERBOSE)
				print_comp_labels("size", "EMPTY!", "ft", 0, r5);
		}
		r1 = ft->empty();
		r5 = ft->size();
		print_comp_labels("empty()", "EMPTY!", "ft", 0, r1);
		print_comp_labels("size()", "EMPTY!", "ft", 0, r5);
	}

}
#define equal(A, B)	test_equivalence(d, A, B);

template<class T>
struct pair {
	std::vector<T>	*std;
	ft::vector<T>		*ft;
};

template<class T>
pair<T>		create_vector_internal(std::vector<T> *std, ft::vector<T> *ft, bool empty) {
	size_t	size;
	T		val;
	pair<T>	res;

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::vector<T>();
	ft = new ft::vector<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	res.std = std;
	res.ft = ft;
	return res;
}

template<class T>
pair<T>		create_vector_size_internal(std::vector<T> *std, ft::vector<T> *ft, size_t size) {
	T		val;
	pair<T>	res;

	std = new std::vector<T>();
	ft = new ft::vector<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	res.std = std;
	res.ft = ft;
	return res;
}

#define	create_vector(A, B, C)	{pair<T> tmp = create_vector_internal(A, B, C); A=tmp.std; B=tmp.ft;}

#define	create_vector_size(A, B, C)	{pair<T> tmp = create_vector_size_internal(A, B, C); A=tmp.std; B=tmp.ft;}

/*-----------------------------------CONSTRUCTOR TESTS-----------------------------------*/

template<class T>
void		test_constructors(data<T> *d) {
	print_title("constructor [default]");
	test_constructor_default(d);
	//print_title("constructor [fill]");
	//test_constructor_fill(d, 0);
	//test_constructor_fill(d, 1);
	//print_title("constructor [range]");
	//test_constructor_range(d, 0);
	//test_constructor_range(d, 1);
	//print_title("constructor [range]");
	//test_constructor_range(d, 0);
	//test_constructor_range(d, 1);
	//print_title("constructor [copy]");
	//test_constructor_copy(d, 0);
	//test_constructor_copy(d, 1);
}

/*-----------------------------------ITERATORS-----------------------------------*/

/*-----------------------------------CAPACITY-----------------------------------*/

template<class T>
void		test_capacity(data<T> *d) {
	(void)d;
	//print_title("operator[] [non-const]");
	//print_title("operator[] [const]");
	//print_title("at [non-const]");
	//test_at(d, 0);
	//test_at(d, 1);
	//print_title("at [const]");
	//print_title("at [const]");
	//test_at_const(d, 0);
	//test_at_const(d, 1);
	//print_title("front [non-const]");
	//print_title("front [const]");
	print_title("back [non-const]");
	print_title("back [const]");
}

/*-----------------------------------ELEMENT ACCESS TESTS-----------------------------------*/

template<class T>
void		test_element_access(data<T> *d) {
	(void)d;
	//print_title("operator[] [non-const]");
	//print_title("operator[] [const]");
	//print_title("at [non-const]");
	//test_at(d, 0);
	//test_at(d, 1);
	//print_title("at [const]");
	//print_title("at [const]");
	//test_at_const(d, 0);
	//test_at_const(d, 1);
	//print_title("front [non-const]");
	//print_title("front [const]");
	print_title("back [non-const]");
	print_title("back [const]");
}

/*-----------------------------------MODIFIERS TESTS-----------------------------------*/

template<class T>
void		test_modifiers(data<T> *d) {
	(void)d;
	//print_title("assign [range]");
	//print_title("assign [fill]");
	print_title("push_back");
	//test_push_back(d, 0);
	//test_push_back(d, 1);
	print_title("pop_back");
	//print_title("insert [single element]");
	//print_title("insert [fill]");
	//print_title("insert [range]");
	//print_title("erase [posotion]");
	//print_title("erase [range]");
	//print_title("swap");
	//print_title("clear");
}

/*-----------------------------------MAIN-----------------------------------*/

template<class T>
void		do_tests(void) {
	data<T>		*d;

	d = init_data<T>();

	print_group_title("CONSTRUCTORS");
	//test_constructors(d);
	//print_group_title("OPERATORS");
	//test_operators(d);
	//print_group_title("ITERATORS");
	//test_iterators(d);
	//print_group_title("CAPACITY");
	//test_capacity(d);
	//print_group_title("ELEMENT ACCESS");
	//test_element_access(d);
	//print_group_title("MODIFIERS");
	//test_modifiers(d);
	//print_group_title("OPERATIONS");
	//test_operations(d);
	//print_group_title("NON-MEMBER OVERLOADS");
	//test_non_member_overloads(d);

	std::cout << std::endl << GREEN << "pass: " << RESET << d->pass << RED << "\tfail:\t" << RESET << d->fail << std::endl;
	delete d;
}

int			main(void) {
	srand((int) time(0));
	do_tests<int>();
}

