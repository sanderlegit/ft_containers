/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   test_list.cpp                                     e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/02/18 12:04:31 by dries             *8*   8   *8*          */
/*   Updated: 2021/03/31 16:26:28 by dries               **ee8ee**            */
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
void		print_comp_iter(std::string str, T t, R r) {
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
void		print_comp_iter_labels(std::string str, std::string l1, std::string l2, T t, R r) {
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
void		test_equivalence(data<T> *d, std::list<T> *std, ft::list<T> *ft) {
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

	if (!r1 && !r2) {
		r3 = std->front();
		r4 = ft->front();
		r5 = std->size();
		r6 = ft->size();
		print_comp("front()", r3, r4);
		comp(r3 == r4);
		r3 = std->back();
		r4 = ft->back();
		std->pop_front();
		ft->pop_front();
		print_comp("back()", r3, r4);
		comp(r3 == r4);
		print_comp("size()", r5, r6);
		comp(r5 == r6);
		if (VERBOSE)
			std::cout << "  iterating through..." << std::endl;
		while (!std->empty() && !ft->empty()) {
			r1 = std->empty();
			r2 = ft->empty();
			r3 = std->front();
			r4 = ft->front();
			r5 = std->size();
			r6 = ft->size();
			std->pop_front();
			ft->pop_front();
			if (VVERBOSE)
				print_comp("front", r3, r4);
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
		r3 = std->front();
		r5 = std->size();
		print_comp_labels("front()", "std", "EMPTY!", r3, 0);
		r3 = std->back();
		std->pop_front();
		ft->pop_front();
		print_comp_labels("back()", "std", "EMPTY!", r3, 0);
		print_comp_labels("size()", "std", "EMPTY!", r5, 0);
		if (VERBOSE)
			std::cout << "  iterating through..." << std::endl;
		while (!std->empty()) {
			r1 = std->empty();
			r3 = std->front();
			r5 = std->size();
			std->pop_front();
			if (VVERBOSE)
				print_comp_labels("front", "std", "EMPTY!", r3, 0);
			if (VVERBOSE)
				print_comp_labels("size", "std", "EMPTY!", r5, 0);
		}
		r1 = std->empty();
		r5 = std->size();
		print_comp_labels("empty()", "std", "EMPTY!", r1, 0);
		print_comp_labels("size()", "std", "EMPTY!", r5, 0);
	} else if (r1 && !r2) {
		r3 = ft->front();
		r5 = ft->size();
		print_comp_labels("front()", "EMPTY!", "ft", 0, r3);
		r3 = ft->back();
		ft->pop_front();
		ft->pop_front();
		print_comp_labels("back()", "EMPTY!", "ft", 0, r3);
		print_comp_labels("size()", "EMPTY!", "ft", 0, r5);
		if (VERBOSE)
			std::cout << "  iterating through..." << std::endl;
		while (!ft->empty()) {
			r1 = ft->empty();
			r3 = ft->front();
			r5 = ft->size();
			ft->pop_front();
			if (VVERBOSE)
				print_comp_labels("front", "EMPTY!", "ft", 0, r3);
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
	std::list<T>	*std;
	ft::list<T>		*ft;
};

template<class T>
pair<T>		create_list_internal(std::list<T> *std, ft::list<T> *ft, bool empty) {
	size_t	size;
	T		val;
	pair<T>	res;

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
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
pair<T>		create_list_size_internal(std::list<T> *std, ft::list<T> *ft, size_t size) {
	T		val;
	pair<T>	res;

	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	res.std = std;
	res.ft = ft;
	return res;
}

#define	create_list(A, B, C)	{pair<T> tmp = create_list_internal(A, B, C); A=tmp.std; B=tmp.ft;}

#define	create_list_size(A, B, C)	{pair<T> tmp = create_list_size_internal(A, B, C); A=tmp.std; B=tmp.ft;}

/*-----------------------------------CONSTRUCTOR TESTS-----------------------------------*/

template<class T>
void		test_empty_constructor(data<T> *d) {
	std::list<T> 	*std;
	ft::list<T> 	*ft;

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

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
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

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
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

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
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
	print_title("Empty Constructor");
	test_empty_constructor(d);
	print_title("Fill Constructor");
	test_fill_constructor(d, 0);
	test_fill_constructor(d, 1);
	print_title("Range Constructor");
	test_range_constructor(d, 0);
	test_range_constructor(d, 1);
	print_title("Copy Constructor");
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

	print_title("operator=");
	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
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

	print_title("begin");
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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
	print_comp_iter("*iter", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter++
	r1 = *std_iter++;
	r2 = *ft_iter++;
	print_comp_iter("iter++ old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("iter++ new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//++iter
	r1 = *++std_iter;
	r2 = *++ft_iter;
	print_comp_iter("++iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("++iter new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter--
	r1 = *std_iter--;
	r2 = *ft_iter--;
	print_comp_iter("iter-- old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("iter-- new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//--iter
	r1 = *--std_iter;
	r2 = *--ft_iter;
	print_comp_iter("--iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("--iter new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//empty constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::iterator();
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::iterator();

	//operator=
	*std_iter_2 = std_iter;
	*ft_iter_2 = ft_iter;
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_iter_labels("std_iter = iter", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_iter_labels("ft_iter = iter", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	incr_score(d);
	delete std_iter_2;
	delete ft_iter_2;

	//copy constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::iterator(std_iter);
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::iterator(ft_iter);
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_iter_labels("ft_iter(iter)", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_iter_labels("std_iter(iter)", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp_iter("iter == iter_2", r3, r4);
	comp(r3 == r4);
	incr_score(d);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp_iter("iter != iter_2", r3, r4);
	comp(r3 == r4);
	incr_score(d);

	ft_iter++;
	std_iter++;
	std::cout << "  iter++" << std::endl;

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp_iter("iter == iter_2", r3, r4);
	comp(r3 == r4);
	incr_score(d);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp_iter("iter != iter_2", r3, r4);
	comp(r3 == r4);
	incr_score(d);

	//iter->		//only testable with classes?
	//convert of const to non const

	delete std_iter_2;
	delete ft_iter_2;
	delete std;
	delete ft;
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

	print_title("rbegin");
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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
	print_comp_iter("*iter", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter++
	r1 = *std_iter++;
	r2 = *ft_iter++;
	print_comp_iter("iter++ old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("iter++ new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//++iter
	r1 = *++std_iter;
	r2 = *++ft_iter;
	print_comp_iter("++iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("++iter new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter--
	r1 = *std_iter--;
	r2 = *ft_iter--;
	print_comp_iter("iter-- old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("iter-- new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//--iter
	r1 = *--std_iter;
	r2 = *--ft_iter;
	print_comp_iter("--iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("--iter new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//empty constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::reverse_iterator();
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::reverse_iterator();

	//operator=
	*std_iter_2 = std_iter;
	*ft_iter_2 = ft_iter;
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_iter_labels("std_iter = iter", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_iter_labels("ft_iter = iter", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	incr_score(d);
	delete std_iter_2;
	delete ft_iter_2;

	//copy constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::reverse_iterator(std_iter);
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::reverse_iterator(ft_iter);
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_iter_labels("ft_iter(iter)", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_iter_labels("std_iter(iter)", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp_iter("iter == iter", r3, r4);
	comp(r3 == r4);
	incr_score(d);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp_iter("iter != iter", r3, r4);
	comp(r3 == r4);
	incr_score(d);

	ft_iter++;
	std_iter++;
	std::cout << "  iter++" << std::endl;

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp_iter("iter == iter", r3, r4);
	comp(r3 == r4);
	incr_score(d);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp_iter("iter != iter", r3, r4);
	comp(r3 == r4);
	incr_score(d);

	//iter->		//only testable with classes?

	delete std_iter_2;
	delete ft_iter_2;
	delete std;
	delete ft;
}

template<class T>
void		test_end(data<T> *d, bool empty) {
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

	print_title("end");
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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

	std_iter = std->end();
	ft_iter = ft->end();
	//std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	ft_iter--;
	std_iter--;
	std::cout << "  iter--" << std::endl;

	//iter--
	r1 = *std_iter--;
	r2 = *ft_iter--;
	print_comp_iter("iter-- old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("iter-- new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//--iter
	r1 = *--std_iter;
	r2 = *--ft_iter;
	print_comp_iter("--iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("--iter new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("*iter", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter++
	r1 = *std_iter++;
	r2 = *ft_iter++;
	print_comp_iter("iter++ old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("iter++ new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//++iter
	r1 = *++std_iter;
	r2 = *++ft_iter;
	print_comp_iter("++iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("++iter new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//empty constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::iterator();
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::iterator();

	//operator=
	*std_iter_2 = std_iter;
	*ft_iter_2 = ft_iter;
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_iter_labels("std_iter = iter", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_iter_labels("ft_iter = iter", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	incr_score(d);
	delete std_iter_2;
	delete ft_iter_2;

	//copy constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::iterator(std_iter);
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::iterator(ft_iter);
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_iter_labels("ft_iter(iter)", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_iter_labels("std_iter(iter)", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp_iter("iter == iter_2", r3, r4);
	comp(r3 == r4);
	incr_score(d);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp_iter("iter != iter_2", r3, r4);
	comp(r3 == r4);
	incr_score(d);

	ft_iter--;
	std_iter--;
	std::cout << "  iter--" << std::endl;

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp_iter("iter == iter_2", r3, r4);
	comp(r3 == r4);
	incr_score(d);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp_iter("iter != iter_2", r3, r4);
	comp(r3 == r4);
	incr_score(d);

	//iter->		//only testable with classes?
	//convert of const to non const

	delete std_iter_2;
	delete ft_iter_2;
	delete std;
	delete ft;
}

template<class T>
void		test_rend(data<T> *d, bool empty) {
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

	print_title("rend");
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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

	std_iter = std->rend();
	ft_iter = ft->rend();
	//std::cout << "testing on:\tnew ft::list<T>(" << size << ", " << val << ");" << std::endl;
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	ft_iter--;
	std_iter--;
	std::cout << "  iter--" << std::endl;

	//iter--
	r1 = *std_iter--;
	r2 = *ft_iter--;
	print_comp_iter("iter-- old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("iter-- new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//--iter
	r1 = *--std_iter;
	r2 = *--ft_iter;
	print_comp_iter("--iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("--iter new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("*iter", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter++
	r1 = *std_iter++;
	r2 = *ft_iter++;
	print_comp_iter("iter++ old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("iter++ new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//++iter
	r1 = *++std_iter;
	r2 = *++ft_iter;
	print_comp_iter("++iter old", r1, r2);
	comp(r1 == r2);
	r1 = *std_iter;
	r2 = *ft_iter;
	print_comp_iter("++iter new", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//empty constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::reverse_iterator();
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::reverse_iterator();

	//operator=
	*std_iter_2 = std_iter;
	*ft_iter_2 = ft_iter;
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_iter_labels("std_iter = iter", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_iter_labels("ft_iter = iter", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	incr_score(d);
	delete std_iter_2;
	delete ft_iter_2;

	//copy constructor
	std_iter_2 = new typename std::list<T, std::allocator<T> >::reverse_iterator(std_iter);
	ft_iter_2 = new typename ft::list<T, std::allocator<T> >::reverse_iterator(ft_iter);
	r1 = **std_iter_2;
	r2 = *std_iter;
	print_comp_iter_labels("ft_iter(iter)", "lhs", "rhs", r1, r2);
	r1 = **ft_iter_2;
	r2 = *ft_iter;
	print_comp_iter_labels("std_iter(iter)", "lhs", "rhs", r1, r2);
	comp(r1 == r2);
	incr_score(d);

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp_iter("iter == iter", r3, r4);
	comp(r3 == r4);
	incr_score(d);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp_iter("iter != iter", r3, r4);
	comp(r3 == r4);
	incr_score(d);

	ft_iter--;
	std_iter--;
	std::cout << "  iter--" << std::endl;

	//iter == iter
	r3 = (ft_iter == *ft_iter_2);
	r4 = (std_iter == *std_iter_2);
	print_comp_iter("iter == iter", r3, r4);
	comp(r3 == r4);
	incr_score(d);
	//iter != iter
	r3 = (ft_iter != *ft_iter_2);
	r4 = (std_iter != *std_iter_2);
	print_comp_iter("iter != iter", r3, r4);
	comp(r3 == r4);
	incr_score(d);

	//iter->		//only testable with classes?

	delete std_iter_2;
	delete ft_iter_2;
	delete std;
	delete ft;
}

template<class T>
void		test_iterators(data<T> *d) {
	test_begin(d, 0);
	//test_begin_const(d, 0);
	test_end(d, 0);
	test_rbegin(d, 0);
	test_rend(d, 0);
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

	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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

	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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
	print_title("empty");
	test_empty(d, 0);
	test_empty(d, 1);
	print_title("size");
	test_size(d, 0);
	test_size(d, 1);
	print_title("max_size");
	test_max_size(d);
}

/*-----------------------------------ELEMENT ACCESS TESTS-----------------------------------*/

template<class T>
void		test_front(data<T> *d, bool empty) {
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	T				r1;
	T				r2;

	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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

	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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

	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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

	val = randomize<T>();
	if (empty) {
		size = 0;
	} else {
		size = (rand() % 253) + 3;
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
	print_title("front");
	test_front(d, 0);
	print_title("const front");
	test_front_const(d, 0);
	print_title("back");
	test_back(d, 0);
	print_title("const back");
	test_back_const(d, 0);
}

/*-----------------------------------MODIFIER TESTS-----------------------------------*/

template<class T>
void		test_push_front(data<T> *d) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	bool			r1;
	bool			r2;
	T				r3;
	T				r4;
	size_t			r5;
	size_t			r6;

	//if (empty)
		//size = 0;
	//else
	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	std::cout << "testing on:\tempty list" << std::endl;
	std::cout << "  push_front " << (int)size << " elements e.g." << std::endl;
	val = randomize<T>();
	std->push_front(val);
	ft->push_front(val);
	r1 = std->empty();
	r2 = ft->empty();
	r3 = std->front();
	r4 = ft->front();
	r5 = std->size();
	r6 = ft->size();
	print_comp("empty()", r3, r4);
	comp(r1 == r2);
	print_comp("front()", r3, r4);
	comp(r3 == r4);
	print_comp("size()", r5, r6);
	comp(r5 == r6);

	std::cout << "  finshing the other " << (int)size - 1 << " elements..." << std::endl;
	for (size_t i = 1; i < size; i++) {
		val = randomize<T>();
		std->push_front(val);
		ft->push_front(val);
		r1 = std->empty();
		r2 = ft->empty();
		r3 = std->front();
		r4 = ft->front();
		r5 = std->size();
		r6 = ft->size();
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

	equal(std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_push_back(data<T> *d) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	bool			r1;
	bool			r2;
	T				r3;
	T				r4;
	size_t			r5;
	size_t			r6;

	//if (empty)
		//size = 0;
	//else
	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	std::cout << "testing on:\tempty list" << std::endl;
	std::cout << "  push_back " << (int)size << " elements e.g." << std::endl;
	val = randomize<T>();
	std->push_back(val);
	ft->push_back(val);
	r1 = std->empty();
	r2 = ft->empty();
	r3 = std->back();
	r4 = ft->back();
	r5 = std->size();
	r6 = ft->size();
	print_comp("empty()", r3, r4);
	comp(r1 == r2);
	print_comp("back()", r3, r4);
	comp(r3 == r4);
	print_comp("size()", r5, r6);
	comp(r5 == r6);

	std::cout << "  finshing the other " << (int)size - 1 << " elements..." << std::endl;
	for (size_t i = 1; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
		r1 = std->empty();
		r2 = ft->empty();
		r3 = std->back();
		r4 = ft->back();
		r5 = std->size();
		r6 = ft->size();
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

	equal(std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_pop_front(data<T> *d, bool empty) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	bool			r1;
	bool			r2;
	T				r3;
	T				r4;
	size_t			r5;
	size_t			r6;

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_front(val);
		ft->push_front(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;

	std::cout << "  clearing list using pop_front()" << std::endl;
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
			r1 = std->empty();
			r2 = ft->empty();
			r3 = std->front();
			r4 = ft->front();
			r5 = std->size();
			r6 = ft->size();
			std->pop_front();
			ft->pop_front();
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
	}

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_pop_back(data<T> *d, bool empty) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	bool			r1;
	bool			r2;
	T				r3;
	T				r4;
	size_t			r5;
	size_t			r6;

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;

	std::cout << "  clearing list using pop_back()" << std::endl;
	r1 = std->empty();
	r2 = ft->empty();
	print_comp("empty()", r1, r2);
	comp(r1 == r2);
	if (!r1 && !r2) {
		r3 = std->back();
		r4 = ft->back();
		r5 = std->size();
		r6 = ft->size();
		std->pop_back();
		ft->pop_back();
		print_comp("back()", r3, r4);
		comp(r3 == r4);
		print_comp("size()", r5, r6);
		comp(r5 == r6);
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
	}

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_assign_fill(data<T> *d, bool empty) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	val = randomize<T>();
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);
	std::cout << "testing on:\tnew ft::list<T>(" << (int)size << ", " << val << ")" << std::endl;

	size = (rand() % 253) + 3;
	val = randomize<T>();
	std::cout << "  list.assign(" << (int)size << ", " << val << ")" << std::endl;
	std->assign(size, val);
	ft->assign(size, val);
	equal(std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_assign_range(data<T> *d, bool empty) {
	unsigned char	size;
	std::list<T> 	*src;
	std::list<T> 	*std;
	ft::list<T> 	*ft;

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	src = new std::list<T>();
	for (size_t i = 0; i < size; i++)
		src->push_back(randomize<T>());

	std = new std::list<T>(src->begin(), src->end());
	ft = new ft::list<T>(src->begin(), src->end());

	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.assign(src.begin(), src.end())" << std::endl;
	std->assign(src->begin(), src->end());
	ft->assign(src->begin(), src->end());
	equal(std, ft);

	delete std;
	delete ft;
	delete src;
	incr_score(d);
}

template<class T>
void		test_insert_single(data<T> *d) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	typename std::list<T>::iterator	r1;
	typename ft::list<T>::iterator	r2;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	std::cout << "  list.insert(list->begin(), " << val << ")" << std::endl;
	r1 = std->insert(std->begin(), val);
	r2 = ft->insert(ft->begin(), val);
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	std::cout << "  list.insert(++list->begin(), " << val << ")" << std::endl;
	r1 = std->insert(++std->begin(), val);
	r2 = ft->insert(++ft->begin(), val);
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	std::cout << "  list.insert(--list->end(), " << val << ")" << std::endl;
	r1 = std->insert(--std->end(), val);
	r2 = ft->insert(--ft->end(), val);
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	std::cout << "  list.insert(list->end(), " << val << ")" << std::endl;
	r1 = std->insert(std->end(), val);
	r2 = ft->insert(ft->end(), val);
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);

	size = 0;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	std::cout << "  list.insert(list->end(), " << val << ")" << std::endl;
	r1 = std->insert(std->end(), val);
	r2 = ft->insert(ft->end(), val);
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	size = 0;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	std::cout << "  list.insert(list->begin(), " << val << ")" << std::endl;
	r1 = std->insert(std->begin(), val);
	r2 = ft->insert(ft->begin(), val);
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_insert_fill(data<T> *d) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	val = randomize<T>();
	std::cout << "  list.insert(list->begin(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(std->begin(), size, val);
	ft->insert(ft->begin(), size, val);
	equal(std, ft);
	incr_score(d);

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	val = randomize<T>();
	std::cout << "  list.insert(++list->begin(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(++std->begin(), size, val);
	ft->insert(++ft->begin(), size, val);
	equal(std, ft);
	incr_score(d);

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	val = randomize<T>();
	std::cout << "  list.insert(--list->end(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(--std->end(), size, val);
	ft->insert(--ft->end(), size, val);
	equal(std, ft);
	incr_score(d);

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	val = randomize<T>();
	std::cout << "  list.insert(list->end(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(std->end(), size, val);
	ft->insert(ft->end(), size, val);
	equal(std, ft);
	incr_score(d);

	size = 0;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	val = randomize<T>();
	std::cout << "  list.insert(list->end(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(std->end(), size, val);
	ft->insert(ft->end(), size, val);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;

	size = 0;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	val = randomize<T>();
	std::cout << "  list.insert(list->begin(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(std->begin(), size, val);
	ft->insert(ft->begin(), size, val);
	equal(std, ft);
	incr_score(d);

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = 0;
	val = randomize<T>();
	std::cout << "  list.insert(list->end(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(std->end(), size, val);
	ft->insert(ft->end(), size, val);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = 0;
	val = randomize<T>();
	std::cout << "  list.insert(list->begin(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(std->begin(), size, val);
	ft->insert(ft->begin(), size, val);
	equal(std, ft);
	incr_score(d);

	size = 0;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = 0;
	val = randomize<T>();
	std::cout << "  list.insert(list->end(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(std->end(), size, val);
	ft->insert(ft->end(), size, val);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;

	size = 0;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = 0;
	val = randomize<T>();
	std::cout << "  list.insert(list->begin(), " << (int)size << ", " << val << ")" << std::endl;
	std->insert(std->begin(), size, val);
	ft->insert(ft->begin(), size, val);
	equal(std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_insert_range(data<T> *d) {
	unsigned char	size;
	T				val;
	std::list<T> 	*stdsrc;
	ft::list<T> 	*ftsrc;
	std::list<T> 	*std;
	ft::list<T> 	*ft;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "inserting from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.insert(list->begin(), src->begin(), src->end())" << std::endl;
	std->insert(std->begin(), stdsrc->begin(), stdsrc->end());
	ft->insert(ft->begin(), ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "inserting from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.insert(++list->begin(), src->begin(), src->end())" << std::endl;
	std->insert(++std->begin(), stdsrc->begin(), stdsrc->end());
	ft->insert(++ft->begin(), ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "inserting from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.insert(--list->end(), src->begin(), src->end())" << std::endl;
	std->insert(--std->end(), stdsrc->begin(), stdsrc->end());
	ft->insert(--ft->end(), ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;

	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "inserting from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.insert(list->end(), src->begin(), src->end())" << std::endl;
	std->insert(std->end(), stdsrc->begin(), stdsrc->end());
	ft->insert(ft->end(), ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;

	size = 0;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "inserting from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.insert(list->end(), src->begin(), src->end())" << std::endl;
	std->insert(std->end(), stdsrc->begin(), stdsrc->end());
	ft->insert(ft->end(), ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;

	delete std;
	delete ft;

	size = 0;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "inserting from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.insert(list->begin(), src->begin(), src->end())" << std::endl;
	std->insert(std->begin(), stdsrc->begin(), stdsrc->end());
	ft->insert(ft->begin(), ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;

	size = 0;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = 0;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "inserting from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.insert(list->end(), src->begin(), src->end())" << std::endl;
	std->insert(std->end(), stdsrc->begin(), stdsrc->end());
	ft->insert(ft->end(), ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;

	delete std;
	delete ft;

	size = 0;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = 0;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "inserting from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.insert(list->begin(), src->begin(), src->end())" << std::endl;
	std->insert(std->begin(), stdsrc->begin(), stdsrc->end());
	ft->insert(ft->begin(), ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	delete stdsrc;
	delete ftsrc;

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_erase_single(data<T> *d) {
	
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	typename std::list<T>::iterator	r1;
	typename ft::list<T>::iterator	r2;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.erase(list->begin())" << std::endl;
	r1 = std->erase(std->begin());
	r2 = ft->erase(ft->begin());
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.erase(++list->begin())" << std::endl;
	r1 = std->erase(++std->begin());
	r2 = ft->erase(++ft->begin());
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.erase(--list->end())" << std::endl;
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}

template<class T>
void		test_erase_range(data<T> *d) {
	
	int		size;
	int		offset;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	typename std::list<T>::iterator	r1;
	typename ft::list<T>::iterator	r2;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (int i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.erase(list->begin(), list->end())" << std::endl;
	r1 = std->erase(std->begin(), std->end());
	r2 = ft->erase(ft->begin(), ft->end());
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (int i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	offset = (rand() % (size / 2));
	std::cout << "offset: " << offset << std::endl;
	if (offset == 0) offset = 1;
	std::cout << "offset: " << offset << std::endl;
	offset++;
	std::cout << "offset: " << offset << std::endl;
	r1 = std->end();
	r2 = ft->end();
	for (int i = 0; i < offset; ++i) {
		--r1;
		--r2;
	}
	std::cout << "  list.erase(++list->begin(), list->end() - " << (int)offset << ")" << std::endl;
	r1 = std->erase(++std->begin(), r1);
	r2 = ft->erase(++ft->begin(), r2);
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (int i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.erase(list->begin(), list->begin())" << std::endl;
	r1 = std->erase(std->begin(), std->begin());
	r2 = ft->erase(ft->begin(), ft->begin());
	print_comp("ret:", *r1, *r2);
	comp(*r1 == *r2);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;

	size = (rand() % 253) + 10;
	if (size == 0) size += 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (int i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	offset = (rand() % (size / 2));
	if (offset == 0) offset += 1;
	offset++;
	r1 = std->begin();
	r2 = ft->begin();
	for (int i = 0; i < offset; ++i) {
		++r1;
		++r2;
	}
	std::cout << "  list.erase(list->begin() + " << (int)offset << ", list->end())" << std::endl;
	r1 = std->erase(r1, std->end());
	r2 = ft->erase(r2, ft->end());
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}

template<class T>
void		test_swap(data<T> *d)  {
	unsigned char	size;
	T				val;
	std::list<T> 	*stdsrc;
	ft::list<T> 	*ftsrc;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	typename ft::list<T>::iterator	fti;
	typename std::list<T>::iterator	stdi;

	size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "  storing iterator: i = ++list->begin()" << std::endl;
	stdi = ++stdsrc->begin();
	fti = ++ftsrc->begin();
	std::cout << "swapping with:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "  list.swap(list2)" << std::endl;
	std->swap(*stdsrc);
	ft->swap(*ftsrc);
	std::cout << "  checking iterator still valid" << std::endl;
	print_comp("*i", *stdi, *fti);
	comp(*stdi == *fti);
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;
	delete std;
	delete ft;

	std = new std::list<T>();
	ft = new ft::list<T>();
	std::cout << "testing on:\tempty list" << std::endl;
	val = randomize<T>();
	stdsrc = new std::list<T>(1, val);
	ftsrc = new ft::list<T>(1, val);
	std::cout << "  storing iterator: i = ++list->begin()" << std::endl;
	stdi = stdsrc->begin();
	fti = ftsrc->begin();
	std::cout << "swapping with:\trandom filled list size:" << (int)1 << "" << std::endl;
	std::cout << "  list.swap(list2)" << std::endl;
	std->swap(*stdsrc);
	ft->swap(*ftsrc);
	std::cout << "  checking iterator still valid" << std::endl;
	print_comp("*i", *stdi, *fti);
	comp(*stdi == *fti);
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;
	delete std;
	delete ft;

	std = new std::list<T>();
	ft = new ft::list<T>();
	std::cout << "testing on:\tempty list" << std::endl;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	std::cout << "swapping with:\tempty list" << std::endl;
	std::cout << "  list.swap(list2)" << std::endl;
	std->swap(*stdsrc);
	ft->swap(*ftsrc);
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;
	delete std;
	delete ft;
}

template<class T>
void		test_resize(data<T> *d, bool empty) {
	
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;

	std = new std::list<T>();
	ft = new ft::list<T>();
	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	std::cout << "  list.resize(" << (int)size << ", " << val << ")" << std::endl;
	std->resize(size, val);
	ft->resize(size, val);
	equal(std, ft);
	incr_score(d);
	if (empty) {
		delete ft;
		delete std;
		return;
	}

	delete std;
	delete ft;

	std = new std::list<T>();
	ft = new ft::list<T>();
	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	size -= rand() % (size / 2);
	if (size < 0)
		size = 0;
	std::cout << "  list.resize(" << (int)size << ", " << val << ")" << std::endl;
	std->resize(size, val);
	ft->resize(size, val);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	std = new std::list<T>();
	ft = new ft::list<T>();
	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	size += rand() % (size / 2);
	std::cout << "  list.resize(" << (int)size << ", " << val << ")" << std::endl;
	std->resize(size, val);
	ft->resize(size, val);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	std = new std::list<T>();
	ft = new ft::list<T>();
	size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	size = 0;
	std::cout << "  list.resize(" << (int)size << ", " << val << ")" << std::endl;
	std->resize(size, val);
	ft->resize(size, val);
	equal(std, ft);
	incr_score(d);

	delete ft;
	delete std;
}

template<class T>
void		test_clear(data<T> *d, bool empty) {
	
	size_t 			size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;

	std = new std::list<T>();
	ft = new ft::list<T>();
	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	val = randomize<T>();
	std::cout << "  list.clear()" << std::endl;
	std->clear();
	ft->clear();
	equal(std, ft);
	incr_score(d);

	delete ft;
	delete std;
}

template<class T>
void		test_modifiers(data<T> *d) {

	print_title("push_front");
	test_push_front(d);
	print_title("push_back");
	test_push_back(d);
	print_title("pop_front");
	test_pop_front(d, 0);
	print_title("pop_back");
	test_pop_back(d, 0);
	print_title("assign [fill]");
	test_assign_fill(d, 0);
	test_assign_fill(d, 1);
	print_title("assign [range]");
	test_assign_range(d, 0);
	test_assign_range(d, 1);
	print_title("insert [single]");
	test_insert_single(d);
	print_title("insert [fill]");
	test_insert_fill(d);
	print_title("insert [range]");
	test_insert_range(d);
	print_title("erase [single]");
	test_erase_single(d);
	print_title("erase [range]");
	test_erase_range(d);
	print_title("swap");
	test_swap(d);
	print_title("resize");
	test_resize(d, 0);
	test_resize(d, 1);
	print_title("clear");
	test_clear(d, 0);
	test_clear(d, 1);
}

/*-----------------------------------OPERATIONS-----------------------------------*/

template<class T>
void		test_slice_entire(data<T> *d, bool emptydest, bool emptysrc) {
	unsigned char	size;
	T				val;
	std::list<T> 	*stdsrc;
	std::list<T> 	*std;
	ft::list<T> 	*ftsrc;
	ft::list<T> 	*ft;

	if (emptydest)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	if (emptysrc)
		size = 0;
	else
		size = (rand() % 253) + 3;
	val = randomize<T>();
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "slice from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2)" << std::endl;
	std->splice(std->begin(), *stdsrc);
	ft->splice(ft->begin(), *ftsrc);
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	if (emptydest)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	if (emptysrc)
		size = 0;
	else
		size = (rand() % 253) + 3;
	val = randomize<T>();
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "slice from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.end(), list2)" << std::endl;
	std->splice(std->end(), *stdsrc);
	ft->splice(ft->end(), *ftsrc);
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	if (emptydest) {
		delete stdsrc;
		delete std;
		delete ftsrc;
		delete ft;
		return;
	}

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	if (emptydest)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = (rand() % 253) + 3;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "slice from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "testing:\tlist.slice(++list.begin(), list2)" << std::endl;
	std->splice(++std->begin(), *stdsrc);
	ft->splice(++ft->begin(), *ftsrc);
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	if (emptydest)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		std->push_back(val);
		ft->push_back(val);
	}
	std::cout << "testing on:\trandom filled list size:" << (int)size << "" << std::endl;
	size = 1;
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<T>();
		stdsrc->push_back(val);
		ftsrc->push_back(val);
	}
	std::cout << "slice from:\trandom filled list size:" << (int)size << "" << std::endl;
	std::cout << "testing:\tlist.slice(--list.end(), list2)" << std::endl;
	std->splice(--std->end(), *stdsrc);
	ft->splice(--ft->end(), *ftsrc);
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;
}
template<class T>
void		test_splice_single(data<T> *d, bool emptydest) {
	std::list<T> 	*stdsrc = NULL;
	std::list<T> 	*std = NULL;
	ft::list<T> 	*ftsrc = NULL;
	ft::list<T> 	*ft = NULL;

	create_list(std, ft, emptydest);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, 0);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2, list2.begin())" << std::endl;
	std->splice(std->begin(), *stdsrc, stdsrc->begin());
	ft->splice(ft->begin(), *ftsrc, ftsrc->begin());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	create_list(std, ft, emptydest);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, 0);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.end(), list2, list2.begin())" << std::endl;
	std->splice(std->end(), *stdsrc, stdsrc->begin());
	ft->splice(ft->end(), *ftsrc, ftsrc->begin());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	if (emptydest) {
		delete stdsrc;
		delete std;
		delete ftsrc;
		delete ft;
		return;
	}

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	create_list(std, ft, 0);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list_size(stdsrc, ftsrc, 1);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2, list2.begin())" << std::endl;
	std->splice(std->begin(), *stdsrc, stdsrc->begin());
	ft->splice(ft->begin(), *ftsrc, ftsrc->begin());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, 0);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2, list2.begin())" << std::endl;
	std->splice(std->begin(), *stdsrc, stdsrc->begin());
	ft->splice(ft->begin(), *ftsrc, ftsrc->begin());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, 0);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.end(), list2, list2.begin())" << std::endl;
	std->splice(std->end(), *stdsrc, stdsrc->begin());
	ft->splice(ft->end(), *ftsrc, ftsrc->begin());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	create_list(std, ft, 0);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, 0);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2, ++list2.begin())" << std::endl;
	std->splice(std->begin(), *stdsrc, ++stdsrc->begin());
	ft->splice(ft->begin(), *ftsrc, ++ftsrc->begin());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	create_list(std, ft, 0);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, 0);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2, --list2.end())" << std::endl;
	std->splice(std->begin(), *stdsrc, --stdsrc->end());
	ft->splice(ft->begin(), *ftsrc, --ftsrc->end());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);

	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;
}

template<class T>
void		test_splice_range(data<T> *d, bool empty) {
	std::list<T> 	*stdsrc = NULL;
	std::list<T> 	*std = NULL;
	ft::list<T> 	*ftsrc = NULL;
	ft::list<T> 	*ft = NULL;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, 0);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2, list2.begin(), list2.end())" << std::endl;
	std->splice(std->begin(), *stdsrc, stdsrc->begin(), stdsrc->end());
	ft->splice(ft->begin(), *ftsrc, ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list_size(stdsrc, ftsrc, 1);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2, list2.begin(), list2.end())" << std::endl;
	std->splice(std->begin(), *stdsrc, stdsrc->begin(), stdsrc->end());
	ft->splice(ft->begin(), *ftsrc, ftsrc->begin(), ftsrc->end());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, 0);
	std::cout << "slice from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.slice(list.begin(), list2, ++list2.begin(), --list2.end())" << std::endl;
	std->splice(std->begin(), *stdsrc, ++stdsrc->begin(), --stdsrc->end());
	ft->splice(ft->begin(), *ftsrc, ++ftsrc->begin(), --ftsrc->end());
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete std;
	delete ftsrc;
	delete ft;
}

template<class T>
void		test_remove(data<T> *d, bool empty, bool noadd) {
	std::list<T> 	*std = NULL;
	ft::list<T> 	*ft = NULL;
	typename std::list<T>::iterator	stdi;
	typename ft::list<T>::iterator	fti;
	T				val;
	int				i;
	int				cnt;
	int				tmp;

	create_list(std, ft, empty);
	val = randomize<T>();
	if (!noadd) {
		i = 0;
		cnt = 10;
		tmp = cnt;
		while (tmp > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
			} else {
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				std->insert(stdi, val);
				ft->insert(fti, val);
			}
			--tmp;
		}
		std::cout << "  inserting " << val << "  " << cnt << " times" << std::endl;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.remove(" << val << ")" << std::endl;
	std->remove(val);
	ft->remove(val);
	equal(std, ft);
	incr_score(d);

	if (empty && noadd) {
		delete std;
		delete ft;
		return;
	}
	delete std;
	delete ft;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	val = randomize<T>();
	if (!noadd) {
		i = 0;
		cnt = 10;
		tmp = cnt;
		while (tmp > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
			} else {
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				std->insert(stdi, val);
				ft->insert(fti, val);
			}
			--tmp;
		}
		std->push_front(val);
		std->push_back(val);
		ft->push_front(val);
		ft->push_back(val);
		cnt+=2;
		std::cout << "  inserting " << val << "  " << cnt << " times (incl front/back)" << std::endl;
	}
	std::cout << "testing:\tlist.remove(" << val << ")" << std::endl;
	std->remove(val);
	ft->remove(val);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}

template<class T>
bool single_digit (const T& value) { return (value<50000); }

template<class T>
struct is_odd {
  bool operator() (const T& value) { return (value % 2) == 1; }
};

template<class T>
void		test_remove_if(data<T> *d, bool empty, bool noadd) {
	std::list<T> 	*std = NULL;
	ft::list<T> 	*ft = NULL;
	typename std::list<T>::iterator	stdi;
	typename ft::list<T>::iterator	fti;
	T				val;
	int				i;
	int				cnt;
	int				tmp;

	create_list(std, ft, empty);
	val = 50001;
	while (val >=50000)
		val = randomize<T>();
	if (!noadd) {
		i = 0;
		cnt = 10;
		tmp = cnt;
		while (tmp > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
			} else {
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				std->insert(stdi, val);
				ft->insert(fti, val);
			}
			--tmp;
		}
		std::cout << "  inserting " << val << "  " << cnt << " times" << std::endl;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.remove_if(single_digit)" << std::endl;
	std->remove_if(single_digit<T>);
	ft->remove_if(single_digit<T>);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_list(std, ft, empty);
	val = 0;
	while (val % 2 != 1)
		val = randomize<T>();
	if (!noadd) {
		i = 0;
		cnt = 10;
		tmp = cnt;
		while (tmp > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
			} else {
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				std->insert(stdi, val);
				ft->insert(fti, val);
			}
			--tmp;
		}
		std::cout << "  inserting " << val << "  " << cnt << " times" << std::endl;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.remove_if(is_odd())" << std::endl;
	std->remove_if(is_odd<T>());
	ft->remove_if(is_odd<T>());
	equal(std, ft);
	incr_score(d);

	if (empty && noadd) {
		delete std;
		delete ft;
		return;
	}
	delete std;
	delete ft;

	create_list(std, ft, empty);
	val = 50001;
	while (val >=50000)
		val = randomize<T>();
	if (!noadd) {
		i = 0;
		cnt = 10;
		tmp = cnt;
		while (tmp > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
			} else {
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				std->insert(stdi, val);
				ft->insert(fti, val);
			}
			--tmp;
		}
		std->push_front(val);
		std->push_back(val);
		ft->push_front(val);
		ft->push_back(val);
		cnt+=2;
		std::cout << "  inserting " << val << "  " << cnt << " times (incl front/back)" << std::endl;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.remove_if(single_digit)" << std::endl;
	std->remove_if(single_digit<T>);
	ft->remove_if(single_digit<T>);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	val = 0;
	while (val % 2 != 1)
		val = randomize<T>();
	if (!noadd) {
		i = 0;
		cnt = 10;
		tmp = cnt;
		while (tmp > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
			} else {
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				std->insert(stdi, val);
				ft->insert(fti, val);
			}
			--tmp;
		}
		std->push_front(val);
		std->push_back(val);
		ft->push_front(val);
		ft->push_back(val);
		cnt+=2;
		std::cout << "  inserting " << val << "  " << cnt << " times (incl front/back)" << std::endl;
	}
	std::cout << "testing:\tlist.remove_if(is_odd())" << std::endl;
	std->remove_if(is_odd<T>());
	ft->remove_if(is_odd<T>());
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}

template<class T>
void		test_unique(data<T> *d, bool empty, bool noadd) {
	std::list<T> 	*std = NULL;
	ft::list<T> 	*ft = NULL;
	typename std::list<T>::iterator	stdi;
	typename ft::list<T>::iterator	fti;
	T				val;
	int				cnt;
	int				i;
	int				instances;
	int				instance_length;

	create_list(std, ft, empty);
	if (!noadd) {
		cnt = 0;
		instances = 10;
		val = randomize<T>();
		while (instances > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
				++cnt;
			} else {
				val = randomize<T>();
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				instance_length = rand() % 10;
				while (instance_length > 0) {
					--instance_length;
					++cnt;
					std->insert(stdi, val);
					ft->insert(fti, val);
				}
			}
			--instances;
		}
		std::cout << "  inserting " << val << "  " << cnt << " times" << std::endl;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.unique()" << std::endl;
	std->unique();
	ft->unique();
	equal(std, ft);
	incr_score(d);

	if (empty) {
		delete std;
		delete ft;
		return;
	}
	delete std;
	delete ft;

	create_list(std, ft, empty);
	if (!noadd) {
		cnt = 0;
		instances = 10;
		while (instances > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
				++cnt;
			} else {
				val = randomize<T>();
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				instance_length = rand() % 10;
				while (instance_length > 0) {
					--instance_length;
					++cnt;
					std->insert(stdi, val);
					ft->insert(fti, val);
				}
			}
			--instances;
		}
		std->push_front(val);
		std->push_front(val);
		std->push_back(val);
		std->push_back(val);
		ft->push_front(val);
		ft->push_front(val);
		ft->push_back(val);
		ft->push_back(val);
		cnt+=5;
		std::cout << "  inserting " << val << "  " << cnt << " times (incl 2x front/back)" << std::endl;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.unique()" << std::endl;
	std->unique();
	ft->unique();
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}

template<class T>
struct is_equal {
  bool operator() ( T first, T second)
  { return (first == second); }
};

template<class T>
void		test_unique_pred(data<T> *d, bool empty, bool noadd) {
	std::list<T> 	*std = NULL;
	ft::list<T> 	*ft = NULL;
	typename std::list<T>::iterator	stdi;
	typename ft::list<T>::iterator	fti;
	T				val;
	int				cnt;
	int				i;
	int				instances;
	int				instance_length;

	create_list(std, ft, empty);
	if (!noadd) {
		cnt = 0;
		instances = 10;
		val = randomize<T>();
		while (instances > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
				++cnt;
			} else {
				val = randomize<T>();
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				instance_length = rand() % 10;
				while (instance_length > 0) {
					--instance_length;
					++cnt;
					std->insert(stdi, val);
					ft->insert(fti, val);
				}
			}
			--instances;
		}
		std::cout << "  inserting " << val << "  " << cnt << " times" << std::endl;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.unique(is_equal())" << std::endl;
	std->unique(is_equal<T>());
	ft->unique(is_equal<T>());
	equal(std, ft);
	incr_score(d);

	if (empty) {
		delete std;
		delete ft;
		return;
	}
	delete std;
	delete ft;

	create_list(std, ft, empty);
	if (!noadd) {
		cnt = 0;
		instances = 10;
		while (instances > 0) {
			if (empty) {
				std->push_front(val);
				ft->push_front(val);
				++cnt;
			} else {
				val = randomize<T>();
				stdi = std->begin();
				fti = ft->begin();
				i = rand() % std->size();
				while (i > 0) {
					stdi++;
					fti++;
					--i;
				}
				instance_length = rand() % 10;
				while (instance_length > 0) {
					--instance_length;
					++cnt;
					std->insert(stdi, val);
					ft->insert(fti, val);
				}
			}
			--instances;
		}
		std->push_front(val);
		std->push_front(val);
		std->push_back(val);
		std->push_back(val);
		ft->push_front(val);
		ft->push_front(val);
		ft->push_back(val);
		ft->push_back(val);
		cnt+=4;
		std::cout << "  inserting " << val << "  " << cnt << " times (incl 2x front/back)" << std::endl;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.unique(is_equal())" << std::endl;
	std->unique(is_equal<T>());
	ft->unique(is_equal<T>());
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}

template<class T>
void		test_sort(data<T> *d, bool empty) {
	std::list<T>	*std = NULL;
	ft::list<T>		*ft = NULL;

	//create_list_size(std, ft, 5);
	create_list(std, ft, empty);
	//std = new std::list<T>();
	//ft = new ft::list<T>();
	//for (int i = 0; i < 5; ++i) {
		//std->push_front(i);
		//ft->push_front(i);
	//}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.sort()" << std::endl;
	std->sort();
	ft->sort();
	equal(std, ft);
	incr_score(d);

	if (empty) {
		delete std;
		delete ft;
		return;
	}
	delete std;
	delete ft;

	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.sort()" << std::endl;
	std->sort();
	ft->sort();
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}

template<class T>
bool		compare_func ( const T& first, const T& second ) {
  return ( first < second );
}

template<class T>
void		test_sort_compare(data<T> *d, bool empty) {
	std::list<T>	*std = NULL;
	ft::list<T>		*ft = NULL;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.sort(compare)" << std::endl;
	std->sort(compare_func<T>);
	ft->sort(compare_func<T>);
	equal(std, ft);
	incr_score(d);

	if (empty) {
		delete std;
		delete ft;
		return;
	}
	delete std;
	delete ft;

	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.sort()" << std::endl;
	std->sort(compare_func<T>);
	ft->sort(compare_func<T>);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}

template<class T>
void		test_merge(data<T> *d, bool empty) {
	std::list<T>	*std = NULL;
	ft::list<T>		*ft = NULL;
	std::list<T>	*stdsrc = NULL;
	ft::list<T>		*ftsrc = NULL;
	size_t			size;

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size;) {
		if (rand() % 2) {
			std->push_back(i);
			ft->push_back(i);
		} else {
			stdsrc->push_back(i);
			ftsrc->push_back(i);
		}
		if (rand() % 3)
			++i;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "merging from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.merge(list2)" << std::endl;
	std->merge(*stdsrc);
	ft->merge(*ftsrc);
	equal(std, ft);
	incr_score(d);

	if (empty) {
		delete std;
		delete ft;
		delete stdsrc;
		delete ftsrc;
		return;
	}
	delete std;
	delete ft;
	delete stdsrc;
	delete ftsrc;

	create_list_size(stdsrc, ftsrc, 1);
	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "merging from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.merge(list2)" << std::endl;
	std->merge(*stdsrc);
	ft->merge(*ftsrc);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
	delete stdsrc;
	delete ftsrc;

	create_list_size(stdsrc, ftsrc, 0);
	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "merging from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.merge(list2)" << std::endl;
	std->merge(*stdsrc);
	ft->merge(*ftsrc);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
	delete stdsrc;
	delete ftsrc;

	create_list_size(stdsrc, ftsrc, 1);
	create_list_size(std, ft, 0);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "merging from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.merge(list2)" << std::endl;
	std->merge(*stdsrc);
	ft->merge(*ftsrc);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
	delete stdsrc;
	delete ftsrc;
}

template<class T>
void		test_merge_compare(data<T> *d, bool empty) {
	std::list<T>	*std = NULL;
	ft::list<T>		*ft = NULL;
	std::list<T>	*stdsrc = NULL;
	ft::list<T>		*ftsrc = NULL;
	size_t			size;

	if (empty)
		size = 0;
	else
		size = (rand() % 253) + 3;
	std = new std::list<T>();
	ft = new ft::list<T>();
	stdsrc = new std::list<T>();
	ftsrc = new ft::list<T>();
	for (size_t i = 0; i < size;) {
		if (rand() % 2) {
			std->push_back(i);
			ft->push_back(i);
		} else {
			stdsrc->push_back(i);
			ftsrc->push_back(i);
		}
		if (rand() % 3)
			++i;
	}
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "merging from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.merge(list2, compare_func)" << std::endl;
	std->merge(*stdsrc, compare_func<T>);
	ft->merge(*ftsrc, compare_func<T>);
	equal(std, ft);
	incr_score(d);

	if (empty) {
		delete std;
		delete ft;
		delete stdsrc;
		delete ftsrc;
		return;
	}
	delete std;
	delete ft;
	delete stdsrc;
	delete ftsrc;

	create_list_size(stdsrc, ftsrc, 1);
	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "merging from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.merge(list2, compare_func)" << std::endl;
	std->merge(*stdsrc, compare_func<T>);
	ft->merge(*ftsrc, compare_func<T>);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
	delete stdsrc;
	delete ftsrc;

	create_list_size(stdsrc, ftsrc, 0);
	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "merging from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.merge(list2, compare_func)" << std::endl;
	std->merge(*stdsrc, compare_func<T>);
	ft->merge(*ftsrc, compare_func<T>);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
	delete stdsrc;
	delete ftsrc;

	create_list_size(stdsrc, ftsrc, 1);
	create_list_size(std, ft, 0);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "merging from:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "testing:\tlist.merge(list2, compare_func)" << std::endl;
	std->merge(*stdsrc, compare_func<T>);
	ft->merge(*ftsrc, compare_func<T>);
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
	delete stdsrc;
	delete ftsrc;
}

template<class T>
void		test_reverse(data<T> *d, bool empty) {
	std::list<T>	*std = NULL;
	ft::list<T>		*ft = NULL;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.reverse()" << std::endl;
	std->reverse();
	ft->reverse();
	equal(std, ft);
	incr_score(d);

	if (empty) {
		delete std;
		delete ft;
		return;
	}
	delete std;
	delete ft;

	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	std::cout << "testing:\tlist.reverse()" << std::endl;
	std->reverse();
	ft->reverse();
	equal(std, ft);
	incr_score(d);

	delete std;
	delete ft;
}


template<class T>
void		test_operations(data<T> *d) {
	print_title("slice [entire list]");
	test_slice_entire(d, 0, 0);
	test_slice_entire(d, 0, 1);
	test_slice_entire(d, 1, 0);
	test_slice_entire(d, 1, 1);
	print_title("slice [single]");
	test_splice_single(d, 0);
	test_splice_single(d, 1);
	print_title("slice [range]");
	test_splice_range(d, 0);
	test_splice_range(d, 1);
	print_title("remove");
	test_remove(d, 0, 0);
	test_remove(d, 0, 1);
	test_remove(d, 1, 0);
	test_remove(d, 1, 1);
	print_title("remove_if");
	test_remove_if(d, 0, 0);
	test_remove_if(d, 0, 1);
	test_remove_if(d, 1, 0);
	test_remove_if(d, 1, 1);
	print_title("unique [void]");
	test_unique(d, 0, 0);
	test_unique(d, 0, 1);
	test_unique(d, 1, 0);
	test_unique(d, 1, 1);
	print_title("unique [pred]");
	test_unique_pred(d, 0, 0);
	test_unique_pred(d, 0, 1);
	test_unique_pred(d, 1, 0);
	test_unique_pred(d, 1, 1);
	print_title("merge [void]");
	test_merge(d, 0);
	test_merge(d, 1);
	print_title("merge [comp]");
	test_merge_compare(d, 0);
	test_merge_compare(d, 1);
	print_title("sort [void]");		//TODO does not check sort stability
	test_sort(d, 0);
	test_sort(d, 1);
	print_title("sort [comp]");
	test_sort_compare(d, 0);
	test_sort_compare(d, 1);
	print_title("reverse");
	test_reverse(d, 0);
	test_reverse(d, 1);
}

/*-----------------------------------NON-MEMBER OVERLOADS-----------------------------------*/


template<class T>
void		test_swap_overload(data<T> *d, bool empty, bool emptysrc)  {
	std::list<T> 	*stdsrc = NULL;
	ft::list<T> 	*ftsrc = NULL;
	std::list<T> 	*std = NULL;
	ft::list<T> 	*ft = NULL;
	typename ft::list<T>::iterator	fti;
	typename std::list<T>::iterator	stdi;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, emptysrc);
	std::cout << "swapping with:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	if (!empty && !emptysrc) {
		std::cout << "  storing iterator: i = ++list->begin()" << std::endl;
		stdi = ++stdsrc->begin();
		fti = ++ftsrc->begin();
	}
	std::cout << "  swap(list, list2)" << std::endl;
	std::swap(*std, *stdsrc);
	ft::swap(*ft, *ftsrc);
	if (!empty && !emptysrc) {
		std::cout << "  checking iterator still valid" << std::endl;
		print_comp("*i", *stdi, *fti);
		comp(*stdi == *fti);
	}
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;
	delete std;
	delete ft;

	create_list(std, ft, empty);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list_size(stdsrc, ftsrc, 1);
	std::cout << "swapping with:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	if (!empty && !emptysrc) {
		std::cout << "  storing iterator: i = list->begin()" << std::endl;
		stdi = stdsrc->begin();
		fti = ftsrc->begin();
	}
	std::cout << "  swap(list, list2)" << std::endl;
	std::swap(*std, *stdsrc);
	ft::swap(*ft, *ftsrc);
	if (!empty && !emptysrc) {
		std::cout << "  checking iterator still valid" << std::endl;
		print_comp("*i", *stdi, *fti);
		comp(*stdi == *fti);
	}
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;
	delete std;
	delete ft;

	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list(stdsrc, ftsrc, emptysrc);
	std::cout << "swapping with:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	if (!empty && !emptysrc) {
		std::cout << "  storing iterator: i = list->begin()" << std::endl;
		stdi = stdsrc->begin();
		fti = ftsrc->begin();
	}
	std::cout << "  swap(list, list2)" << std::endl;
	std::swap(*std, *stdsrc);
	ft::swap(*ft, *ftsrc);
	if (!empty && !emptysrc) {
		std::cout << "  checking iterator still valid" << std::endl;
		print_comp("*i", *stdi, *fti);
		comp(*stdi == *fti);
	}
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;
	delete std;
	delete ft;

	if (empty || emptysrc)
		return;

	create_list_size(std, ft, 1);
	std::cout << "testing on:\trandom filled list size:" << std->size() << "" << std::endl;
	create_list_size(stdsrc, ftsrc, 1);
	std::cout << "swapping with:\trandom filled list size:" << stdsrc->size() << "" << std::endl;
	std::cout << "  swap(list, list2)" << std::endl;
	std::swap(*std, *stdsrc);
	ft::swap(*ft, *ftsrc);
	equal(std, ft);
	equal(stdsrc, ftsrc);
	incr_score(d);
	delete stdsrc;
	delete ftsrc;
	delete std;
	delete ft;
}

template<class T>
void		test_equals_comparison(data<T> *d, bool emptya, bool emptyb) {
	std::list<T> 	*stda = NULL;
	ft::list<T> 	*fta = NULL;
	std::list<T> 	*stdb = NULL;
	ft::list<T> 	*ftb = NULL;
	bool			stdret;
	bool			ftret;

	create_list(stda, fta, emptya);
	create_list(stdb, ftb, emptyb);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda == *stdb);
	ftret = (*fta == *ftb);
	print_comp_iter("==", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stdb;
	delete ftb;
	stdb = stda;
	ftb = fta;
	std::cout << "  copying first list to second" << std::endl;
	stdret = (*stda == *stdb);
	ftret = (*fta == *ftb);
	print_comp_iter("==", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete fta;
	if (emptya || emptyb) {
		return;
	}

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 0);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda == *stdb);
	ftret = (*fta == *ftb);
	print_comp_iter("==", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 0);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda == *stdb);
	ftret = (*fta == *ftb);
	print_comp_iter("==", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda == *stdb);
	ftret = (*fta == *ftb);
	print_comp_iter("==", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;
}

template<class T>
void		test_not_equals_comparison(data<T> *d, bool emptya, bool emptyb) {
	std::list<T> 	*stda = NULL;
	ft::list<T> 	*fta = NULL;
	std::list<T> 	*stdb = NULL;
	ft::list<T> 	*ftb = NULL;
	bool			stdret;
	bool			ftret;

	create_list(stda, fta, emptya);
	create_list(stdb, ftb, emptyb);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda != *stdb);
	ftret = (*fta != *ftb);
	print_comp_iter("!=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);
	delete stdb;
	delete ftb;

	stdb = stda;
	ftb = fta;
	std::cout << "  copying first list to second" << std::endl;
	stdret = (*stda != *stdb);
	ftret = (*fta != *ftb);
	print_comp_iter("!=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete fta;
	if (emptya || emptyb) {
		return;
	}

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 0);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda != *stdb);
	ftret = (*fta != *ftb);
	print_comp_iter("!=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 0);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda != *stdb);
	ftret = (*fta != *ftb);
	print_comp_iter("!=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda != *stdb);
	ftret = (*fta != *ftb);
	print_comp_iter("!=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;
}

template<class T>
void		test_less_comparison(data<T> *d, bool emptya, bool emptyb) {
	std::list<T> 	*stda = NULL;
	ft::list<T> 	*fta = NULL;
	std::list<T> 	*stdb = NULL;
	ft::list<T> 	*ftb = NULL;
	bool			stdret;
	bool			ftret;

	create_list(stda, fta, emptya);
	create_list(stdb, ftb, emptyb);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda < *stdb);
	ftret = (*fta < *ftb);
	print_comp_iter("<", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);
	delete stdb;
	delete ftb;

	stdb = stda;
	ftb = fta;
	std::cout << "  copying first list to second" << std::endl;
	stdret = (*stda < *stdb);
	ftret = (*fta < *ftb);
	print_comp_iter("<", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete fta;
	if (emptya || emptyb) {
		return;
	}

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 0);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda < *stdb);
	ftret = (*fta < *ftb);
	print_comp_iter("<", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 0);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda < *stdb);
	ftret = (*fta < *ftb);
	print_comp_iter("<", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda < *stdb);
	ftret = (*fta < *ftb);
	print_comp_iter("<", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;
}

template<class T>
void		test_less_eq_comparison(data<T> *d, bool emptya, bool emptyb) {
	std::list<T> 	*stda = NULL;
	ft::list<T> 	*fta = NULL;
	std::list<T> 	*stdb = NULL;
	ft::list<T> 	*ftb = NULL;
	bool			stdret;
	bool			ftret;

	create_list(stda, fta, emptya);
	create_list(stdb, ftb, emptyb);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda <= *stdb);
	ftret = (*fta <= *ftb);
	print_comp_iter("<=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);
	delete stdb;
	delete ftb;

	stdb = stda;
	ftb = fta;
	std::cout << "  copying first list to second" << std::endl;
	stdret = (*stda <= *stdb);
	ftret = (*fta <= *ftb);
	print_comp_iter("<=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete fta;
	if (emptya || emptyb) {
		return;
	}

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 0);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda <= *stdb);
	ftret = (*fta <= *ftb);
	print_comp_iter("<=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 0);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda <= *stdb);
	ftret = (*fta <= *ftb);
	print_comp_iter("<=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda <= *stdb);
	ftret = (*fta <= *ftb);
	print_comp_iter("<=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;
}

template<class T>
void		test_greater_comparison(data<T> *d, bool emptya, bool emptyb) {
	std::list<T> 	*stda = NULL;
	ft::list<T> 	*fta = NULL;
	std::list<T> 	*stdb = NULL;
	ft::list<T> 	*ftb = NULL;
	bool			stdret;
	bool			ftret;

	create_list(stda, fta, emptya);
	create_list(stdb, ftb, emptyb);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda > *stdb);
	ftret = (*fta > *ftb);
	print_comp_iter(">", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);
	delete stdb;
	delete ftb;

	stdb = stda;
	ftb = fta;
	std::cout << "  copying first list to second" << std::endl;
	stdret = (*stda > *stdb);
	ftret = (*fta > *ftb);
	print_comp_iter(">", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete fta;
	if (emptya || emptyb) {
		return;
	}

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 0);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda > *stdb);
	ftret = (*fta > *ftb);
	print_comp_iter(">", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 0);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda > *stdb);
	ftret = (*fta > *ftb);
	print_comp_iter(">", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda > *stdb);
	ftret = (*fta > *ftb);
	print_comp_iter(">", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;
}

template<class T>
void		test_greater_eq_comparison(data<T> *d, bool emptya, bool emptyb) {
	std::list<T> 	*stda = NULL;
	ft::list<T> 	*fta = NULL;
	std::list<T> 	*stdb = NULL;
	ft::list<T> 	*ftb = NULL;
	bool			stdret;
	bool			ftret;

	create_list(stda, fta, emptya);
	create_list(stdb, ftb, emptyb);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda >= *stdb);
	ftret = (*fta >= *ftb);
	print_comp_iter(">=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);
	delete stdb;
	delete ftb;

	stdb = stda;
	ftb = fta;
	std::cout << "  copying first list to second" << std::endl;
	stdret = (*stda >= *stdb);
	ftret = (*fta >= *ftb);
	print_comp_iter(">=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete fta;
	if (emptya || emptyb) {
		return;
	}

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 0);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda >= *stdb);
	ftret = (*fta >= *ftb);
	print_comp_iter(">=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 0);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda >= *stdb);
	ftret = (*fta >= *ftb);
	print_comp_iter(">=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;

	create_list_size(stda, fta, 1);
	create_list_size(stdb, ftb, 1);
	std::cout << "testing on:\trandom filled list size:" << stda->size() << "" << std::endl;
	std::cout << "and:       \trandom filled list size:" << stdb->size() << "" << std::endl;
	stdret = (*stda >= *stdb);
	ftret = (*fta >= *ftb);
	print_comp_iter(">=", stdret, ftret);
	comp(stdret == ftret);
	incr_score(d);

	delete stda;
	delete stdb;
	delete fta;
	delete ftb;
}

template<class T>
void		test_non_member_overloads(data<T> *d) {
	print_title("swap");
	test_swap_overload(d, 0, 0);
	test_swap_overload(d, 0, 1);
	test_swap_overload(d, 1, 0);
	test_swap_overload(d, 1, 1);
	print_title("operator==");
	test_equals_comparison(d, 0, 0);
	test_equals_comparison(d, 0, 1);
	test_equals_comparison(d, 1, 0);
	test_equals_comparison(d, 1, 1);
	print_title("operator!=");
	test_not_equals_comparison(d, 0, 0);
	test_not_equals_comparison(d, 0, 1);
	test_not_equals_comparison(d, 1, 0);
	test_not_equals_comparison(d, 1, 1);
	print_title("operator<");
	test_less_comparison(d, 0, 0);
	test_less_comparison(d, 0, 1);
	test_less_comparison(d, 1, 0);
	test_less_comparison(d, 1, 1);
	print_title("operator<=");
	test_less_eq_comparison(d, 0, 0);
	test_less_eq_comparison(d, 0, 1);
	test_less_eq_comparison(d, 1, 0);
	test_less_eq_comparison(d, 1, 1);
	print_title("operator>");
	test_greater_comparison(d, 0, 0);
	test_greater_comparison(d, 0, 1);
	test_greater_comparison(d, 1, 0);
	test_greater_comparison(d, 1, 1);
	print_title("operator>=");
	test_greater_eq_comparison(d, 0, 0);
	test_greater_eq_comparison(d, 0, 1);
	test_greater_eq_comparison(d, 1, 0);
	test_greater_eq_comparison(d, 1, 1);
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
	print_group_title("MODIFIERS");
	test_modifiers(d);
	print_group_title("OPERATIONS");
	test_operations(d);
	print_group_title("NON-MEMBER OVERLOADS");
	test_non_member_overloads(d);

	std::cout << std::endl << GREEN << "pass: " << RESET << d->pass << RED << "\tfail:\t" << RESET << d->fail << std::endl;
	delete d;
}

int			main(void) {
	srand((int) time(0));
	do_tests<int>();
	//while(1);
}
