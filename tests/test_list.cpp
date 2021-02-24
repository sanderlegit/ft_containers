/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_list.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 12:04:31 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/24 13:17:52 by averheij      ########   odam.nl         */
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

#include <list>
#include "list.hpp"

/*-----------------------------------UTIL-----------------------------------*/

template<class T>
struct data {
	//std::list<T>	*std;
	//ft::list<T>		*ft;
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
	memset(ptr, (unsigned char)(rand() % 256), sizeof(T));
	return val;
}

/*-----------------------------------TEST TOOLS-----------------------------------*/

void		print_group_title(std::string str) {
	std::cout << "\n  #=======" << str << "=======#" <<std::endl;
}

void		print_title(std::string str) {
	std::cout << "\n  ----" << str << "----" <<std::endl;
}

template<class T, class R>
void		print_comp(std::string str, T t, R r) {

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
	print_comp("empty()", r1, r2);
	comp(r1 == r2);

	if (!r1 && !r2) {
		r3 = std->front();
		r4 = ft->front();
		r5 = std->size();
		r6 = ft->size();
		std->pop_front();
		ft->pop_front();
		print_comp("front()", r3, r4);
		comp(r3 == r4);
		print_comp("size()", r5, r6);
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
		print_comp("front()", r3, r4);
		print_comp("size()", r5, r6);
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
		size = rand() % 256;
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
	if (empty)
		size = 0;
	else
		size = rand() % 256;
	src = new std::list<T>();
	for (size_t i = 0; i < size; i++)
		src->push_back(randomize<T>());

	std = new std::list<T>(src->begin(), src->end());
	ft = new ft::list<T>(src->begin(), src->end());

	std::cout << "testing:\tnew ft::list<T>(src->begin(), src->end())" << std::endl;
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
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
	if (empty)
		size = 0;
	else
		size = rand() % 256;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
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
	if (empty)
		size = 0;
	else
		size = rand() % 256;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}

	std = *stdsrc;
	ft = *ftsrc;

	std::cout << "testing:\tftlist = src;" << std::endl;
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
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

/*-----------------------------------ITERATOR TESTS-----------------------------------*/

template<class T>
void		test_begin(data<T> *d, bool empty) {
	size_t 													size;
	T														val;
	std::list<T> 											*std;
	ft::list<T> 											*ft;
	typename std::list<T, std::allocator<T> >::iterator		std_iter;
	typename ft::list<T, std::allocator<T> >::iterator		ft_iter;
	typename std::list<T, std::allocator<T> >::iterator		*std_iter_2;
	typename ft::list<T, std::allocator<T> >::iterator		*ft_iter_2;
	T														r1;
	T														r2;
	bool													r3;
	bool													r4;

	print_title("Begin");
	if (empty) {
		size = 0;
	} else {
		size = rand() % 256;
	}
	//val = randomize<T>();
	//std = new std::list<T>(size, val);
	//ft = new ft::list<T>(size, val);
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}

	std_iter = std->begin();
	ft_iter = ft->begin();
	//std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("*iter", r1, r2);
	comp(r1 == r2);

	//iter++
	r1 = *std_iter++;
	r2 = *ft_iter++;
	print_comp("iter++ old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("iter++ new", r1, r2);
	comp(r1 == r2);

	//++iter
	r1 = *++std_iter;
	r2 = *++ft_iter;
	print_comp("++iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("++iter new", r1, r2);
	comp(r1 == r2);

	//iter--
	r1 = *std_iter--;
	r2 = *ft_iter--;
	print_comp("iter-- old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("iter-- new", r1, r2);
	comp(r1 == r2);

	//--iter
	r1 = *--std_iter;
	r2 = *--ft_iter;
	print_comp("--iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("--iter new", r1, r2);
	comp(r1 == r2);

	//empty constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::iterator();
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::iterator();

	//operator=
	*std_iter_2 = std_iter;
	*ft_iter_2 = ft_iter;
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_labels("std_iter = iter", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_labels("ft_iter = iter", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	delete std_iter_2;
	delete ft_iter_2;

	//copy constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::iterator(std_iter);
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::iterator(ft_iter);
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_labels("ft_iter(iter)", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_labels("std_iter(iter)", "lhs", "rhs", r1, r2);
	comp(r1 == r2);

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp("iter == iter_2", r3, r4);
	comp(r3 == r4);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp("iter != iter_2", r3, r4);
	comp(r3 == r4);

	ft_iter++;
	std_iter++;
	std::cout << "  iter++" << std::endl;

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp("iter == iter_2", r3, r4);
	comp(r3 == r4);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp("iter != iter_2", r3, r4);
	comp(r3 == r4);

	//iter->		//only testable with classes?
	//convert of const to non const

	delete std_iter_2;
	delete ft_iter_2;
	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_rbegin(data<T> *d, bool empty) {
	size_t 													size;
	T														val;
	std::list<T> 											*std;
	ft::list<T> 											*ft;
	typename std::list<T, std::allocator<T> >::reverse_iterator		std_iter;
	typename ft::list<T, std::allocator<T> >::reverse_iterator		ft_iter;
	typename std::list<T, std::allocator<T> >::reverse_iterator		*std_iter_2;
	typename ft::list<T, std::allocator<T> >::reverse_iterator		*ft_iter_2;
	T														r1;
	T														r2;
	bool													r3;
	bool													r4;

	print_title("Begin");
	if (empty) {
		size = 0;
	} else {
		size = rand() % 256;
	}
	//val = randomize<T>();
	//std = new std::list<T>(size, val);
	//ft = new ft::list<T>(size, val);
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}

	std_iter = std->rbegin();
	ft_iter = ft->rbegin();
	//std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("*iter", r1, r2);
	comp(r1 == r2);

	//iter++
	r1 = *std_iter++;
	r2 = *ft_iter++;
	print_comp("iter++ old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("iter++ new", r1, r2);
	comp(r1 == r2);

	//++iter
	r1 = *++std_iter;
	r2 = *++ft_iter;
	print_comp("++iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("++iter new", r1, r2);
	comp(r1 == r2);

	//iter--
	r1 = *std_iter--;
	r2 = *ft_iter--;
	print_comp("iter-- old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("iter-- new", r1, r2);
	comp(r1 == r2);

	//--iter
	r1 = *--std_iter;
	r2 = *--ft_iter;
	print_comp("--iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp("--iter new", r1, r2);
	comp(r1 == r2);

	//empty constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::reverse_iterator();
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::reverse_iterator();

	//operator=
	*std_iter_2 = std_iter;
	*ft_iter_2 = ft_iter;
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_labels("std_iter = iter", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_labels("ft_iter = iter", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	delete std_iter_2;
	delete ft_iter_2;

	//copy constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::reverse_iterator(std_iter);
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::reverse_iterator(ft_iter);
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_labels("ft_iter(iter)", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_labels("std_iter(iter)", "lhs", "rhs", r1, r2);
	comp(r1 == r2);

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp("iter == iter", r3, r4);
	comp(r3 == r4);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp("iter != iter", r3, r4);
	comp(r3 == r4);

	ft_iter++;
	std_iter++;
	std::cout << "  iter++" << std::endl;

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp("iter == iter", r3, r4);
	comp(r3 == r4);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp("iter != iter", r3, r4);
	comp(r3 == r4);

	//iter->		//only testable with classes?

	delete std_iter_2;
	delete ft_iter_2;
	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_iterators(data<T> *d) {
	test_begin(d, 0);
	//test_begin_const(d, 0);
	//test_end(d);
	test_rbegin(d, 0);
	//test_rend(d);
	//test_iterator_class
}

/*-----------------------------------CAPACITY TESTS-----------------------------------*/

template<class T>
void		test_empty(data<T> *d, bool empty) {
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	bool			r1;
	bool			r2;

	print_title("Empty");
	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = rand() % 256;
	}
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	r1 = std->empty();
	r2 = ft->empty();
	std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	print_comp("empty()", r1, r2);
	comp(r1 == r2);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_size(data<T> *d, bool empty) {
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	size_t			r1;
	size_t			r2;

	print_title("Size");
	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = rand() % 256;
	}
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	r1 = std->size();
	r2 = ft->size();
	std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	print_comp("size()", r1, r2);
	comp(r1 == r2);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_max_size(data<T> *d) {
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	size_t			r1;
	size_t			r2;

	print_title("Max Size");
	val = randomize<T>();
	size = 0;
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	r1 = std->max_size();
	r2 = ft->max_size();
	std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	print_comp("max_size()", r1, r2);
	comp(r1 == r2);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_capacity(data<T> *d) {
	test_empty(d, 0);
	test_empty(d, 1);
	test_size(d, 0);
	test_size(d, 1);
	test_max_size(d);
}

/*-----------------------------------ELEMENT ACCESS-----------------------------------*/

template<class T>
void		test_front(data<T> *d, bool empty) {
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	T				r1;
	T				r2;

	print_title("Front");
	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = rand() % 256;
	}
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	r1 = std->front();
	r2 = ft->front();
	std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	print_comp("front()", r1, r2);
	comp(r1 == r2);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_back(data<T> *d, bool empty) {
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	T				r1;
	T				r2;

	print_title("Back");
	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = rand() % 256;
	}
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	r1 = std->back();
	r2 = ft->back();
	std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	print_comp("back()", r1, r2);
	comp(r1 == r2);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_front_const(data<T> *d, bool empty) {
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	T				r1;
	T				r2;

	print_title("Const Front");
	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = rand() % 256;
	}
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	const ft::list<T>& ft_const = *ft;
	const std::list<T>& std_const = *std;

	r1 = std_const.front();
	r2 = ft_const.front();
	std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	print_comp("front()", r1, r2);
	comp(r1 == r2);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_back_const(data<T> *d, bool empty) {
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	T				r1;
	T				r2;

	print_title("Const Back");
	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = rand() % 256;
	}
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	const ft::list<T>& ft_const = *ft;
	const std::list<T>& std_const = *std;

	r1 = std_const.back();
	r2 = ft_const.back();
	std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	print_comp("back()", r1, r2);
	comp(r1 == r2);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_element_access(data<T> *d) {
	test_front(d, 0);
	test_front_const(d, 0);
	test_back(d, 0);
	test_back_const(d, 0);
}

/*-----------------------------------MAIN-----------------------------------*/

template<class T>
void		do_tests(void) {
	data<T>		*d;

	d = init_data<T>();

	print_group_title("CONSTRUCTORS");
	test_constructors(d);
	print_group_title("OPERATORS");
	test_operators(d);
	print_group_title("ITERATORS");
	test_iterators(d);
	print_group_title("CAPACITY");
	test_capacity(d);
	print_group_title("ELEMENT ACCESS");
	test_element_access(d);

	std::cout << std::endl << "pass: " << d->pass << "\tfail:\t" << d->fail << std::endl;
	delete d;
}

int			main(void) {
	srand((int) time(0));
	do_tests<int>();
}
