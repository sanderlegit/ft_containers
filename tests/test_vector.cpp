/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   test_vector.cpp                                   e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/11 13:50:52 by dries             *8*   8   *8*          */
/*   Updated: 2021/03/16 15:09:42 by dries               **ee8ee**            */
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
#define TESTING	true
//#define TESTING	false
#define TESTING_ON	true
//#define TESTING_ON	false
#define VERBOSE	true
//#define VERBOSE	false
//#define VVERBOSE	true
#define VVERBOSE	false

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
		std::cout << GREEN << "pass" << RESET << std::endl;
	} else {
		d->fail++;
		std::cout << RED << "fail" << RESET << std::endl;
	}
	if (!(!VERBOSE && !VVERBOSE && !TESTING_ON))
		std::cout << std::endl;
	d->current_fail = 0;
}

template<class T>
void		check_pass(data<T> *d, bool score) {
	if (!score)
		d->current_fail++;
}
#define comp(A)		check_pass(d, A)
#define test(A, B, C)	{std::string tmp = A; print_comp(tmp, B, C); comp(B == C);}


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
		r5 = std->capacity();
		r6 = ft->capacity();
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
		r3 = std->front();
		r4 = ft->front();
		std->pop_back();
		ft->pop_back();
		print_comp("front()", r3, r4);
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
#define equal(A, B)	test_equivalence(d, A, B, 0);

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
		size = ((rand() % 254) + 1);
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

#define testing(A)	{if (TESTING) std::cout << "  testing: " A << std::endl;}
#define testing_on(A)	{if (TESTING_ON) std::cout << "  testing on: " A << std::endl;}

/*-----------------------------------CONSTRUCTOR TESTS-----------------------------------*/

template<class T>
void		test_constructor_default(data<T> *d) {
	std::vector<T>		*std;
	ft::vector<T>		*ft;

	testing("vector = new vector()");
	ft = new ft::vector<T>();
	std = new std::vector<T>();
	equal(std, ft);
	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_constructor_fill(data<T> *d, bool empty) {
	std::vector<T>		*std;
	ft::vector<T>		*ft;
	T					val;
	size_t				size;

	val = randomize<T>();
	size = (empty) ? 0 : ((rand() % 254) + 1);
	testing("vector = new vector(" << size << ", " << val << ")");
	ft = new ft::vector<T>(size, val);
	std = new std::vector<T>(size, val);
	equal(std, ft);
	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_constructors(data<T> *d) {
	print_title("constructor [default]");
	test_constructor_default(d);
	print_title("constructor [fill]");
	test_constructor_fill(d, 0);
	test_constructor_fill(d, 1);
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
void		test_capacity_func(data<T> *d, bool empty) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	testing("capacity()");
	test("capacity()", std->capacity(), ft->capacity());
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class T>
void		test_empty(data<T> *d, bool empty) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	testing("empty()");
	test("empty()", std->empty(), ft->empty());
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class T>
void		test_size(data<T> *d, bool empty) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	testing("size()");
	test("size()", std->size(), ft->size());
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

/*	Resize tests:
 *	size to size2 (empty)
 *	size to size + 1 (empty)
 *	size to size (empty)
 *	size to zero (empty)
 *	0 to size (value initialized) (empty)
 *	size to size - 1
 *	size to size ^ 2	*/

template<class T>
void		test_resize(data<T> *d, bool empty) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;
	T					val;
	size_t				size;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = rand() % 512;
	val = randomize<T>();
	testing("resize(" << size << ", " << val << ")");
	std->resize(size, val);
	ft->resize(size, val);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = std->size() + 1;
	val = randomize<T>();
	testing("resize(" << size << ", " << val << ")");
	std->resize(size, val);
	ft->resize(size, val);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = std->size();
	val = randomize<T>();
	testing("resize(" << size << ", " << val << ")");
	std->resize(size, val);
	ft->resize(size, val);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = 0;
	val = randomize<T>();
	testing("resize(" << size << ", " << val << ")");
	std->resize(size, val);
	ft->resize(size, val);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	if (empty)
		return;

	create_vector(std, ft, 1);
	testing_on("random filled vector size " << std->size());
	size = (rand() % 256) + 1;
	testing("resize(" << size << ")");
	std->resize(size);
	ft->resize(size);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	size = std->size() - 1;
	testing("resize(" << size << ")");
	std->resize(size);
	ft->resize(size);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	size = std->size() * std->size();
	testing("resize(" << size << ")");
	std->resize(size);
	ft->resize(size);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class T>
void		test_max_size(data<T> *d) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	testing("max_size()");
	test("max_size()", std->max_size(), ft->max_size());
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

/*	Reserve tests:
 *	size to size2 (empty)
 *	size to size + 1 (empty)
 *	size to size (empty);
 *	size to size - 1
 *	size to zero	*/

template<class T>
void		test_reserve(data<T> *d, bool empty) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;
	size_t				size;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = (rand() % 512) + 1;
	testing("reserve(" << size << ")");
	test("max_size()", std->max_size(), ft->max_size());
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = std->size() + 1;
	testing("reserve(" << size << ")");
	test("max_size()", std->max_size(), ft->max_size());
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = std->size();
	testing("reserve(" << size << ")");
	test("max_size()", std->max_size(), ft->max_size());
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	if (empty)
		return;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	size = std->size() - 1;
	testing("reserve(" << size << ")");
	test("max_size()", std->max_size(), ft->max_size());
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	size = rand() % std->size();
	testing("reserve(" << size << ")");
	test("max_size()", std->max_size(), ft->max_size());
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	size = 0;
	testing("reserve(" << size << ")");
	test("max_size()", std->max_size(), ft->max_size());
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;
}

template<class T>
void		test_capacity(data<T> *d) {
	(void)d;
	print_title("size");
	test_size(d, 0);
	test_size(d, 1);
	print_title("max_size");
	test_max_size(d);
	print_title("resize");
	test_resize(d, 0);
	test_resize(d, 1);
	print_title("capacity");
	test_capacity_func(d, 0);
	test_capacity_func(d, 1);
	print_title("empty");
	test_empty(d, 0);
	test_empty(d, 1);
	print_title("reserve");
	test_reserve(d, 0);
	test_reserve(d, 1);
}

/*-----------------------------------ELEMENT ACCESS TESTS-----------------------------------*/

template<class T>
void		test_brackets_operator(data<T> *d) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;
	T					stdr1;
	T					ftr1;
	size_t				idx;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	idx = std->size() - 1;
	testing("vec[" << idx << "]");
	stdr1 = (*std)[idx];
	ftr1 = (*ft)[idx];
	print_comp("[]", stdr1, ftr1);
	comp(stdr1 == ftr1);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	idx = rand() % std->size();
	testing("[" << idx << "]");
	stdr1 = (*std)[idx];
	ftr1 = (*ft)[idx];
	print_comp("at()", stdr1, ftr1);
	comp(stdr1 == ftr1);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	idx = 0;
	testing("[" << idx << "]");
	stdr1 = (*std)[idx];
	ftr1 = (*ft)[idx];
	print_comp("at()", stdr1, ftr1);
	comp(stdr1 == ftr1);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	idx = 1;
	testing("[" << idx << "]");
	stdr1 = (*std)[idx];
	ftr1 = (*ft)[idx];
	print_comp("at()", stdr1, ftr1);
	comp(stdr1 == ftr1);
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

/*	At tests:
 *		do a bool check threw exception
 *		compare exception y/n, if n, compare return
 *	size 	at(size)	(empty)
 *	size	at(size - 1)	(empty)
 *	size	at(size + 1)	(empty)
 *	size	at(-1)	(empty)
 *	size	at(rand() % size)
 *	size	at(0)
 *	size	at(1)	*/

template<class T>
void		test_at(data<T> *d, bool empty) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;
	T					stdr1;
	T					ftr1;
	bool				std_threw;
	bool				ft_threw;
	size_t				idx;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	idx = std->size();
	testing("at(" << idx << ")");
	try {
		stdr1 = std->at(idx);
		std_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		ft_threw = 1;
	}
	print_comp("threw", std_threw, ft_threw);
	comp(std_threw == ft_threw);
	if (!std_threw) {
		print_comp("at()", stdr1, ftr1);
		comp(stdr1 == ftr1);
	}
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	idx = std->size() - 1;
	testing("at(" << idx << ")");
	try {
		stdr1 = std->at(idx);
		std_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		ft_threw = 1;
	}
	print_comp("threw", std_threw, ft_threw);
	comp(std_threw == ft_threw);
	if (!std_threw) {
		print_comp("at()", stdr1, ftr1);
		comp(stdr1 == ftr1);
	}
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	idx = std->size() + 1;
	testing("at(" << idx << ")");
	try {
		stdr1 = std->at(idx);
		std_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		ft_threw = 1;
	}
	print_comp("threw", std_threw, ft_threw);
	comp(std_threw == ft_threw);
	if (!std_threw) {
		print_comp("at()", stdr1, ftr1);
		comp(stdr1 == ftr1);
	}
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	idx = -1;
	testing("at(" << idx << ")");
	try {
		stdr1 = std->at(idx);
		std_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		ft_threw = 1;
	}
	print_comp("threw", std_threw, ft_threw);
	comp(std_threw == ft_threw);
	if (!std_threw) {
		print_comp("at()", stdr1, ftr1);
		comp(stdr1 == ftr1);
	}
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	if (empty)
		return;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	idx = rand() % std->size();
	testing("at(" << idx << ")");
	try {
		stdr1 = std->at(idx);
		std_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		ft_threw = 1;
	}
	print_comp("threw", std_threw, ft_threw);
	comp(std_threw == ft_threw);
	if (!std_threw) {
		print_comp("at()", stdr1, ftr1);
		comp(stdr1 == ftr1);
	}
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	idx = 0;
	testing("at(" << idx << ")");
	try {
		stdr1 = std->at(idx);
		std_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		ft_threw = 1;
	}
	print_comp("threw", std_threw, ft_threw);
	comp(std_threw == ft_threw);
	if (!std_threw) {
		print_comp("at()", stdr1, ftr1);
		comp(stdr1 == ftr1);
	}
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
	
	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	idx = 1;
	testing("at(" << idx << ")");
	try {
		stdr1 = std->at(idx);
		std_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		ft_threw = 1;
	}
	print_comp("threw", std_threw, ft_threw);
	comp(std_threw == ft_threw);
	if (!std_threw) {
		print_comp("at()", stdr1, ftr1);
		comp(stdr1 == ftr1);
	}
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class T>
void		test_front(data<T> *d) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	testing("front()");
	test("front()", std->front(), ft->front());
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector_size(std, ft, 1);
	testing_on("random filled vector size " << std->size());
	testing("front()");
	test("front()", std->front(), ft->front());
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class T>
void		test_back(data<T> *d) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	testing("back()");
	test("back()", std->back(), ft->back());
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;

	create_vector_size(std, ft, 1);
	testing_on("random filled vector size " << std->size());
	testing("back()");
	test("back()", std->back(), ft->back());
	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class T>
void		test_element_access(data<T> *d) {
	print_title("operator[] [non-const]");
	test_brackets_operator(d);
	//print_title("operator[] [const]");	//TODO maybe a good way to verify that something is const return is to try compile code that discrads qualifiers and checking the error return in bash
	print_title("at [non-const]");
	test_at(d, 0);
	test_at(d, 1);
	print_title("at [const]");
	//test_at_const(d, 0);
	//test_at_const(d, 1);
	print_title("front [non-const]");
	test_front(d);
	print_title("front [const]");
	print_title("back [non-const]");
	test_back(d);
	print_title("back [const]");
}

/*-----------------------------------MODIFIERS TESTS-----------------------------------*/

template<class T>
void		test_push_back(data<T> *d, bool empty) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;
	T					val;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	val = randomize<T>();
	testing("push_back(" << val << ")");
	std->push_back(val);
	ft->push_back(val);
	equal(std, ft);
	delete std;
	delete ft;
	incr_score(d);

	if (empty)
		return;

	create_vector_size(std, ft, 1);
	testing_on("random filled vector size " << std->size());
	val = randomize<T>();
	testing("push_back(" << val << ")");
	std->push_back(val);
	ft->push_back(val);
	equal(std, ft);
	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_pop_back(data<T> *d) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	testing("pop_back()");
	std->pop_back();
	ft->pop_back();
	equal(std, ft);
	delete std;
	delete ft;
	incr_score(d);

	create_vector_size(std, ft, 1);
	testing_on("random filled vector size " << std->size());
	testing("pop_back()");
	std->pop_back();
	ft->pop_back();
	equal(std, ft);
	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_modifiers(data<T> *d) {
	(void)d;
	//print_title("assign [range]");
	//print_title("assign [fill]");
	print_title("push_back");
	test_push_back(d, 0);
	test_push_back(d, 1);
	print_title("pop_back");
	test_pop_back(d);
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
	test_constructors(d);
	//print_group_title("OPERATORS");
	//test_operators(d);
	//print_group_title("ITERATORS");
	//test_iterators(d);
	print_group_title("CAPACITY");
	test_capacity(d);
	print_group_title("ELEMENT ACCESS");
	test_element_access(d);
	print_group_title("MODIFIERS");
	test_modifiers(d);
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

