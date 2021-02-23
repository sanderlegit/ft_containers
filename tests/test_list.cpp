/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_list.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 12:04:31 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/23 14:45:10 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sstream>

/*	stdlib		rand
 *	iostream	cout
 *	time		time
 *	string		memset
 *	sstream		string stream
*/

#include <list>
#include "list.hpp"

/*-----------------------------------UTIL-----------------------------------*/

template<class T>
struct data {
	//std::list<T>	*std;
	//ft::list<T>		*ft;
	int				pass = 0;
	int				fail = 0;
	int				current_fail = 0;
};

template<class T>
data<T>		*init_data(void) {
	data<T>		*d = new data<T>;
	return d;
}

template<class T>
T			randomize(void) {
	T		val;
	void	*ptr;

	ptr = reinterpret_cast<void*>(&val);
	memset(ptr, (unsigned char)(rand() % 256), sizeof(T));
	return val;
}

/*-----------------------------------TEST TOOLS-----------------------------------*/

void		print_title(std::string str) {
	std::cout << "\n  ----" << str << "----" <<std::endl;
}

template<class T, class R>
void		print_comp(std::string str, T t, R r) {
	std::cout << str << "()\tstd:";

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

template<class T>
void		incr_score(data<T> *d) {
	std::cout << "  test:\t";
	if (d->current_fail == 0) {
		d->pass++;
		std::cout << "pass" << std::endl;
	} else {
		d->fail++;
		std::cout << "fail" << std::endl;
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
void		test_equivalence(data<T> *d, std::list<T> *std, ft::list<T> *ft) {
	bool			r1;
	bool			r2;
	T				r3;
	T				r4;
	size_t			r5;
	size_t			r6;


	std::cout << "  testing list equality" << std::endl;
	r1 = std->empty();
	r2 = ft->empty();
	print_comp("empty", r1, r2);
	comp(r1 == r2);

	if (!r1 && !r2) {
		r3 = std->front();
		r4 = ft->front();
		r5 = std->size();
		r6 = ft->size();
		std->pop_front();
		ft->pop_front();
		print_comp("front", r3, r4);
		comp(r3 == r4);
		print_comp("size", r5, r6);
		comp(r5 == r6);

		std::cout << "  iterating through..." << std::endl;
		while (!std->empty() && !ft->empty()) {
			r3 = std->front();
			r4 = ft->front();
			r5 = std->size();
			r6 = ft->size();
			std->pop_front();
			ft->pop_front();
			comp(r3 == r4);
			comp(r5 == r6);
		}
		print_comp("front", r3, r4);
		print_comp("size", r5, r6);
	}
}
#define equal(A, B)	test_equivalence(d, A, B);

/*-----------------------------------CONSTRUCTOR TESTS-----------------------------------*/

template<class T>
void		test_empty_constructor(data<T> *d) {
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	bool			r1;
	bool			r2;

	print_title("Empty Constructor");
	std = new std::list<T>();
	ft = new ft::list<T>();

	std::cout << "testing:\tnew ft::list<T>()" << std::endl;
	equal(std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_fill_constructor(data<T> *d, bool empty) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;

	print_title("Fill Constructor");
	if (empty)
		size = 0;
	else
		size = randomize<char>();
	val = randomize<T>();
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	std::cout << "testing:\tnew ft::list<T>(" << (int)size << ", " << val << ")" << std::endl;
	equal(std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_range_constructor(data<T> *d, bool empty) {
	unsigned char	size;
	std::list<T> 	*src;
	std::list<T> 	*std;
	ft::list<T> 	*ft;

	print_title("Range Constructor");
	size = randomize<char>();
	src = new std::list<T>();
	if (!empty)
		for (size_t i = 0; i < size; i++)
			src->push_back(randomize<T>());

	std = new std::list<T>(src->begin(), src->end());
	ft = new ft::list<T>(src->begin(), src->end());

	std::cout << "testing:\tnew ft::list<T>(src->begin(), src->end())" << std::endl;
	equal(std, ft);

	delete std;
	delete ft;
	delete src;
	incr_score(d);
}

template<class T>
void		test_copy_constructor(data<T> *d, bool empty) {
	unsigned char	size;
	T				val;
	std::list<T> 	*stdsrc;
	std::list<T> 	*std;
	ft::list<T> 	*ftsrc;
	ft::list<T> 	*ft;

	print_title("Copy Constructor");
	size = randomize<char>();
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	if (!empty)
		for (size_t i = 0; i < size; i++) {
			val = randomize<T>();
			stdsrc->push_back(val);
			ftsrc->push_back(val);
		}

	std = new std::list<T>(*stdsrc);
	ft = new ft::list<T>(*ftsrc);

	std::cout << "testing:\tnew ft::list<T>(*src)" << std::endl;
	equal(std, ft);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_constructors(data<T> *d) {
	test_empty_constructor(d);
	test_fill_constructor(d, 0);
	test_fill_constructor(d, 1);
	test_range_constructor(d, 0);
	test_range_constructor(d, 1);
	test_copy_constructor(d, 0);
	test_copy_constructor(d, 1);
}

/*-----------------------------------OPERATOR TESTS-----------------------------------*/

template<class T>
void		test_equals_operator(data<T> *d, bool empty) {
	unsigned char	size;
	T				val;
	std::list<T> 	*stdsrc;
	std::list<T> 	std;
	ft::list<T> 	*ftsrc;
	ft::list<T> 	ft;

	print_title("Operator =");
	size = randomize<char>();
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	if (!empty)
		for (size_t i = 0; i < size; i++) {
			val = randomize<T>();
			stdsrc->push_back(val);
			ftsrc->push_back(val);
		}

	std = *stdsrc;
	ft = *ftsrc;

	std::cout << "testing:\tftlist = src;" << std::endl;
	equal(&std, &ft);

	delete stdsrc;
	delete ftsrc;
	incr_score(d);
}

template<class T>
void		test_operators(data<T> *d) {
	test_equals_operator(d, 0);
	test_equals_operator(d, 1);
}
/*-----------------------------------CAPACITY TESTS-----------------------------------*/

template<class T>
void		test_empty(data<T> *d) {
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	bool			r1;
	bool			r2;

	print_title("Empty");
	val = randomize<T>();
	std = new std::list<T>(5, val);
	ft = new ft::list<T>(5, val);

	r1 = std->empty();
	r2 = ft->empty();
	std::cout << "testing on:\tnew ft::list<T>(5, val);" << std::endl;
	print_comp("empty", r1, r2);
	comp(r1 == r2);

	for (int i = 0; i < 5; i++) {
		std->pop_front();
		ft->pop_front();
		r1 = std->empty();
		r2 = ft->empty();
		comp(r1 == r2);
	}
	r1 = std->empty();
	r2 = ft->empty();
	std::cout << "testing on:\tempty list" << std::endl;
	print_comp("empty", r1, r2);
	comp(r1 == r2);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_capacity(data<T> *d) {
	test_empty(d);
}

/*-----------------------------------MAIN-----------------------------------*/

template<class T>
void		do_tests(void) {
	data<T>		*d;

	d = init_data<T>();

	test_constructors(d);
	test_operators(d);
	test_capacity(d);

	std::cout << std::endl << "pass: " << d->pass << "\tfail:\t" << d->fail << std::endl;
	delete d;
}

int			main(void) {
	srand((int) time(0));
	do_tests<int>();
}
