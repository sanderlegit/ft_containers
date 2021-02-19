/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_list.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 12:04:31 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/19 13:49:28 by averheij      ########   odam.nl         */
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
	std::cout << "  ----" << str << "----" <<std::endl;
}

template<class T, class R>
void		print_comp(std::string str, T t, R r) {
	std::cout << str << "\tstd:";

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
//#define comp(A, B)		print_comp(r1, r2); comp(r1 == r2)


//template<class T, class Lstd, class Lft, class Fstd, class Fft, typename Rstd, typename Rft>
//void		full_comp(data<T> *d, Lstd *l1, Lft *ft, Fstd f1, Fft f2) {
	//Rstd 	r1 = l1->f1();
	//Rft		r2 = ft->f2();

	//print_comp(r1, r2);
	//incr_score(d, r1 == r2);
//}

//#define comp(A, B)		full_comp(d, std, ft, A, B)

template<class T>
void		test_equivalence(data<T> *d, std::list<T> *std, ft::list<T> *ft) {
	bool			r1;
	bool			r2;
	T				r3;
	T				r4;
	size_t			r5;
	size_t			r6;

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

		std::cout << "\titerating through..." << std::endl;
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

	//r1 = std->empty();
	//r2 = ft->empty();
	//print_comp("empty", r1, r2);
	//comp(r1 == r2);
	test_equivalence(d, std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_fill_constructor(data<T> *d) {
	unsigned char	size;
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	//bool			r1;
	//bool			r2;
	//T				r3;
	//T				r4;
	//size_t			r5;
	//size_t			r6;

	print_title("Fill Constructor");
	size = randomize<char>();
	val = randomize<T>();
	std = new std::list<T>(size, val);
	ft = new ft::list<T>(size, val);

	//r1 = std->empty();
	//r2 = ft->empty();
	//print_comp("empty", r1, r2);
	//comp(r1 == r2);

	//r3 = std->front();
	//r4 = ft->front();
	//r5 = std->size();
	//r6 = ft->size();
	//std->pop_front();
	//ft->pop_front();
	//print_comp("front", r3, r4);
	//comp(r3 == r4);
	//print_comp("size", r5, r6);
	//comp(r5 == r6);

	//while (!std->empty() && !ft->empty()) {
		//r3 = std->front();
		//r4 = ft->front();
		//r5 = std->size();
		//r6 = ft->size();
		//std->pop_front();
		//ft->pop_front();
		//comp(r3 == r4);
		//comp(r5 == r6);
	//}
	test_equivalence(d, std, ft);

	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_range_constructor(data<T> *d) {
	//TODO
	//test equality of size, head, tail, front; pop; through to check values
}

template<class T>
void		test_copy_constructor(data<T> *d) {
	//TODO
}

template<class T>
void		test_constructors(data<T> *d) {
	test_empty_constructor(d);
	test_fill_constructor(d);
	test_range_constructor(d);
	test_copy_constructor(d);
}

/*-----------------------------------CAPACITY TESTS-----------------------------------*/

template<class T>
void		test_empty(data<T> *d) {
	T				val;
	std::list<T> 	*std;
	ft::list<T> 	*ft;
	bool			r1;
	bool			r2;

	print_title("test empty");
	val = randomize<T>();
	std = new std::list<T>(5, val);
	ft = new ft::list<T>(5, val);

	r1 = std->empty();
	r2 = ft->empty();
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
	test_capacity(d);

	std::cout << "pass: " << d->pass << "\tfail:\t" << d->fail << std::endl;
	delete d;
}

int			main(void) {
	srand((int) time(0));
	do_tests<int>();
}
