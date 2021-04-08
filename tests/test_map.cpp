/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   test_map.cpp                                      e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/31 17:28:30 by dries             *8*   8   *8*          */
/*   Updated: 2021/04/08 18:18:01 by dries               **ee8ee**            */
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

#include <map>
#include "map.hpp"

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
//#define EQUALITY	true
#define EQUALITY	false
//#define VVERBOSE	true
#define VVERBOSE	false

/*-----------------------------------UTIL-----------------------------------*/

template<class K, class M>
struct data {
	int				pass;
	int				fail;
	int				current_fail;
};

template<class K, class M>
data<K, M>		*init_data(void) {
	data<K, M>		*d = new data<K, M>;

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

template<class K, class M>
void		incr_score(data<K, M> *d) {
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

template<class K, class M>
void		check_pass(data<K, M> *d, bool score) {
	if (!score)
		d->current_fail++;
}
#define comp(A)		check_pass(d, A)
#define test(A, B, C)	{std::string tmp = A; print_comp(tmp, B, C); comp((B) == (C));}
#define test_labels(A, L1, L2, B, C)	{std::string tmp = A; print_comp_labels(tmp, L1, L2, B, C); comp((B) == (C));}

template<class T, class R>
void		eq_print_comp(std::string str, T t, R r) {
	if (EQUALITY) {
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
void		eq_print_comp_labels(std::string str, std::string l1, std::string l2, T t, R r) {
	if (EQUALITY) {
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


//template<class K, class M>
//void		test_equivalence(data *d, std::map<K, M> *std, ft::map<K, M> *ft, bool capacity) {
	//bool			r1;
	//bool			r2;
	//T				r3;
	//T				r4;
	//size_t			r5;
	//size_t			r6;

	//if (EQUALITY)
		//std::cout << "  testing list equality" << std::endl;
	//r1 = std->empty();
	//r2 = ft->empty();
	//eq_print_comp("empty()", r1, r2);
	//comp(r1 == r2);

	//if (capacity) {
		//r5 = std->capacity();
		//r6 = ft->capacity();
		//eq_print_comp("capacity()", r5, r6);
		//comp(r5 <= r6);
	//}

	//if (!r1 && !r2) {
		//if (EQUALITY)
			//std::cout << "  iterating through..." << std::endl;
		//while (0) {//go over using iterators
			////if (VVERBOSE)
				////eq_print_comp("*i", r3, r4);
		//}
	//} else if (!r1 && r2) {
		//if (EQUALITY)
			//std::cout << "  iterating through..." << std::endl;
		//while (0)) {//go over using iterators
			////if (VVERBOSE)
				////eq_print_comp_labels("*i", "std", "EMPTY!", r3, 0);
		//}
	//} else if (r1 && !r2) {
		//if (EQUALITY)
			//std::cout << "  iterating through..." << std::endl;
		//while (0) {//go over using iterators
			////if (VVERBOSE)
				////eq_print_comp_labels("*i", "EMPTY!", "ft", 0, r3);
		//}
	//}
//}
#define equal(A, B)	test_equivalence(d, A, B, 0);

template<class K, class M>
struct pair {
	std::map<K, M>	*std;
	ft::map<K, M>	*ft;
};

template<class K, class M>
pair<K, M>		create_map_internal(std::map<K, M> *std, ft::map<K, M> *ft, bool empty) {
	size_t		size;
	M			val;
	K			key;
	pair<K, M>	res;

	if (empty)
		size = 0;
	else
		size = ((rand() % 254) + 1);
	std = new std::map<K, M>();
	ft = new ft::map<K, M>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<M>();
		key = rand() % size;
		std->insert(std::pair<K, M>(key, val));
		ft->insert(std::pair<K, M>(key, val));
	}
	res.std = std;
	res.ft = ft;
	return res;
}

template<class K, class M>
pair<K, M>		create_map_size_internal(std::map<K, M> *std, ft::map<K, M> *ft, size_t size) {
	M			val;
	K			key;
	pair<K, M>	res;

	std = new std::map<K, M>();
	ft = new ft::map<K, M>();
	for (size_t i = 0; i < size; i++) {
		val = randomize<M>();
		key = rand() % size;
		std->insert(val);
		ft->insert(val);
	}
	res.std = std;
	res.ft = ft;
	return res;
}

#define	create_map(A, B, C)	{pair<T> tmp = create_map(A, B, C); A=tmp.std; B=tmp.ft;}

#define	create_map(A, B, C)	{pair<T> tmp = create_map(A, B, C); A=tmp.std; B=tmp.ft;}

#define testing(A)	{if (TESTING) std::cout << "  testing: " A << std::endl;}
#define testing_on(A)	{if (TESTING_ON) std::cout << "  testing on: " A << std::endl;}

/*-----------------------------------CONSTRUCTOR TESTS-----------------------------------*/

template<class K, class M>
void		test_empty_constructor(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;

	testing("m = new map()");
	std = new std::map<K, M>();
	ft = new ft::map<K, M>();

	//equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		test_constructors(data<K, M> *d) {
	test_empty_constructor(d);

}

/*-----------------------------------ITERATOR CLASS TESTS-----------------------------------*/
/*-----------------------------------REVERSE ITERATOR CLASS TESTS-----------------------------------*/
/*-----------------------------------ITERATOR FUNCS TESTS-----------------------------------*/
/*-----------------------------------CAPACITY TESTS-----------------------------------*/
/*-----------------------------------ELEMENT ACCESS TESTS-----------------------------------*/
/*-----------------------------------MODIFIERS TESTS-----------------------------------*/
/*-----------------------------------OBSERVERS TESTS-----------------------------------*/
/*-----------------------------------OPERATIONS TESTS-----------------------------------*/

/*-----------------------------------MAIN-----------------------------------*/

template<class K, class M>
void		do_tests(void) {
	data<K, M>		*d;

	d = init_data<K, M>();

	print_group_title("CONSTRUCTORS");
	test_constructors(d);
	//print_group_title("ITERATOR CLASS");
	//test_iterator_class(d);
	//print_group_title("REVERSE ITERATOR CLASS");
	//test_rev_iterator_class(d);
	//print_group_title("ITERATOR FUNCS");
	//test_iterator_funcs(d);
	//print_group_title("CAPACITY");
	//test_capacity(d);
	//print_group_title("ELEMENT ACCESS");
	//test_element_access(d);
	//print_group_title("MODIFIERS");
	//test_modifiers(d);
	//print_group_title("OBSERVERS");
	//test_observers(d);
	//print_group_title("OPERATIONS");
	//test_operations(d);

	std::cout << std::endl << GREEN << "pass: " << RESET << d->pass << RED << "\tfail:\t" << RESET << d->fail << std::endl;
	delete d;
}

int			main(void) {
	srand((int) time(0));
	do_tests<int, int>();
	//while(1)a
}

