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


/*---------------------------------OPTIONS-------------------------------------*/

#define TESTING	true
#define TESTING_ON	true
#define VERBOSE	true
/* #define EQUALITY	true */
#define VVERBOSE	true

/*--------------------------------DO NOT TOUCH--------------------------------*/

#define WHITE "\033[37;01m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[m"

#ifndef TESTING
#define TESTING	false
#endif
#ifndef TESTING_ON
#define TESTING_ON	false
#endif
#ifndef VERBOSE
#define VERBOSE	false
#endif
#ifndef EQUALITY
#define EQUALITY	false
#endif
#ifndef VVERBOSE
#define VVERBOSE	false
#endif

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
	std::cout << BLUE << "		  +--------+-" << str << "-+--------+" << RESET << std::endl;
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


template<class K, class M>
void		test_equivalence(data<K, M> *d, std::map<K, M> *std, ft::map<K, M> *ft) {
	bool								r1;
	bool								r2;
	std::pair<K, M>						r3;
	std::pair<K, M>						r4;
	size_t								r5;
	size_t								r6;
	typename std::map<K, M>::iterator	stdi;
	typename ft::map<K, M>::iterator	fti;

	if (EQUALITY)
		std::cout << "  testing list equality" << std::endl;
	r1 = std->empty();
	r2 = ft->empty();
	eq_print_comp("empty()", r1, r2);
	comp(r1 == r2);
	r5 = std->size();
	r6 = ft->size();
	eq_print_comp("size()", r5, r6);
	comp(r5 == r6);

	/* if (!r1 && !r2) { */
		if (EQUALITY)
			std::cout << "  iterating through..." << std::endl;
		stdi = std->begin();
		fti = ft->begin();
		while (stdi != std->end() && fti != ft->end()) {//go over using iterators
			r3 = *stdi;
			r4 = *fti;
			if (VVERBOSE)
				eq_print_comp("*i.k", r3.first, r4.first);
			comp(r3.first == r4.first);
			if (VVERBOSE)
				eq_print_comp("*i.m", r3.second, r4.second);
			comp(r3.second == r4.second);
			++stdi;
			++fti;
		}
	/* } else if (!r1 && r2) { */
	/* 	if (EQUALITY) */
	/* 		std::cout << "  iterating through..." << std::endl; */
	/* 	while (0) {//go over using iterators */
	/* 		if (VVERBOSE) { */
	/* 			eq_print_comp_labels("*i", "std", "EMPTY!", r3, 0); */
	/* 		} */
	/* 	} */
	/* } else if (r1 && !r2) { */
	/* 	if (EQUALITY) */
	/* 		std::cout << "  iterating through..." << std::endl; */
	/* 	while (0) {//go over using iterators */
	/* 		if (VVERBOSE) */
	/* 			eq_print_comp_labels("*i", "EMPTY!", "ft", 0, r3); */
	/* 	} */
	/* } */
}
#define equal(A, B)	test_equivalence(d, A, B);

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
		key = rand() % size;
		val = randomize<M>();
		std->insert(std::pair<K, M>(key, val));
		ft->insert(std::pair<K, M>(key, val));
	}
	res.std = std;
	res.ft = ft;
	return res;
}

#define	create_map(A, B, empty)	{pair<K, M> tmp = create_map_internal(A, B, empty); A=tmp.std; B=tmp.ft;}

#define	create_map_size(A, B, size)	{pair<K, M> tmp = create_map_size_internal(A, B, size); A=tmp.std; B=tmp.ft;}

#define create_map_empty_size(A, B, empty, size) {if (!empty) { create_map_size(std, ft, size); } else { create_map(std, ft, 1); }}

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

	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		test_constructors(data<K, M> *d) {
	print_title("constructor [empty]");
	test_empty_constructor(d);
}

/*-----------------------------------ITERATOR CLASS TESTS-----------------------------------*/

template<class K, class M>
void		itest_constructors(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::iterator	*fti;
	typename std::map<K, M>::iterator	*stdi;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());

	testing("i = new iterator()");
	fti = new typename ft::map<K, M>::iterator();
	stdi = new typename std::map<K, M>::iterator();
	delete stdi;
	delete fti;
	incr_score(d);

	testing("i = new iterator(m.begin())");
	fti = new typename ft::map<K, M>::iterator(ft->begin());
	stdi = new typename std::map<K, M>::iterator(std->begin());
	print_comp("i->first", (*stdi)->first, (*fti)->first);
	comp((*stdi)->first == (*fti)->first);
	print_comp("i->second", (*stdi)->second, (*fti)->second);
	comp((*stdi)->second == (*fti)->second);
	delete stdi;
	delete fti;

	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		itest_copy_op(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::iterator	fti;
	typename std::map<K, M>::iterator	stdi;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing("i = m.begin()");
	fti = ft->begin();
	stdi = std->begin();
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		itest_comp_ops(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::iterator	fti;
	typename std::map<K, M>::iterator	stdi;
	typename ft::map<K, M>::iterator	fti2;
	typename std::map<K, M>::iterator	stdi2;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing_on("i = m.begin()");
	testing_on("i2 = m.begin()");
	fti = ft->begin();
	fti2 = ft->begin();
	stdi = std->begin();
	stdi2 = std->begin();
	print_comp("i==i2", stdi == stdi2, fti == fti2);
	comp((stdi == stdi2) == (fti == fti2));
	print_comp("i!=i2", stdi != stdi2, fti != fti2);
	comp((stdi != stdi2) == (fti != fti2));
	incr_score(d);
	testing_on("i2++");
	fti2++;
	stdi2++;
	print_comp("i==i2", stdi == stdi2, fti == fti2);
	comp((stdi == stdi2) == (fti == fti2));
	print_comp("i!=i2", stdi != stdi2, fti != fti2);
	comp((stdi != stdi2) == (fti != fti2));
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		itest_deref_ops(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::iterator	fti;
	typename std::map<K, M>::iterator	stdi;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing_on("i = m.begin()");
	fti = ft->begin();
	stdi = std->begin();
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("(*i).m", (*stdi).second, (*fti).second);
	comp((*stdi).second == (*fti).second);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		itest_val_assign(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::iterator	fti;
	typename std::map<K, M>::iterator	stdi;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing("i = m.begin()");
	fti = ft->begin();
	stdi = std->begin();
	testing("*i.m = 1");
	(*fti).second = 1;
	(*stdi).second = 1;
	
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		itest_incr_decr(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::value_type	*r1;
	typename std::map<K, M>::value_type	*r2;
	typename ft::map<K, M>::iterator	fti;
	typename std::map<K, M>::iterator	stdi;
	typename ft::map<K, M>::iterator	fti2;
	typename std::map<K, M>::iterator	stdi2;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing_on("i = m.begin()");
	fti = ft->begin();
	stdi = std->begin();
	testing("i2 = i++");
	fti2 = fti++;
	stdi2 = stdi++;
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("i2->k", stdi2->first, fti2->first);
	comp(stdi2->first == fti2->first);
	print_comp("i2->m", stdi2->second, fti2->second);
	comp(stdi2->second == fti2->second);
	incr_score(d);

	testing("i2 = ++i");
	fti2 = ++fti;
	stdi2 = ++stdi;
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("i2->k", stdi2->first, fti2->first);
	comp(stdi2->first == fti2->first);
	print_comp("i2->m", stdi2->second, fti2->second);
	comp(stdi2->second == fti2->second);
	incr_score(d);

	testing("i2 = i--");
	fti2 = fti--;
	stdi2 = stdi--;
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("i2->k", stdi2->first, fti2->first);
	comp(stdi2->first == fti2->first);
	print_comp("i2->m", stdi2->second, fti2->second);
	comp(stdi2->second == fti2->second);
	incr_score(d);

	testing("i2 = --i");
	fti2 = --fti;
	stdi2 = --stdi;
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("i2->k", stdi2->first, fti2->first);
	comp(stdi2->first == fti2->first);
	print_comp("i2->m", stdi2->second, fti2->second);
	comp(stdi2->second == fti2->second);
	incr_score(d);

	testing("r = *i++");
	r1 = new typename ft::map<K, M>::value_type(*fti++);
	r2 = new typename std::map<K, M>::value_type(*stdi++);
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("r->k", r2->first, r1->first);
	comp(r2->first == r1->first);
	print_comp("r->m", r2->second, r1->second);
	comp(r2->second == r1->second);
	incr_score(d);

	testing("r = *i--");
	r1 = new typename ft::map<K, M>::value_type(*fti--);
	r2 = new typename std::map<K, M>::value_type(*stdi--);
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("r->k", r2->first, r1->first);
	comp(r2->first == r1->first);
	print_comp("r->m", r2->second, r1->second);
	comp(r2->second == r1->second);
	incr_score(d);

	delete std;
	delete ft;
}

template<class K, class M>
void		test_iterator_class(data<K, M> *d) {
	print_title("constructors [default|copy]");
	itest_constructors(d);
	print_title("operator= ");
	itest_copy_op(d);
	print_title("operators==|!= ");
	itest_comp_ops(d);
	print_title("operators*|-> ");
	itest_deref_ops(d);
	print_title("value assigment");
	itest_val_assign(d);
	print_title("operator++|-- ");
	itest_incr_decr(d);
}
/*-----------------------------------REVERSE ITERATOR CLASS TESTS-----------------------------------*/

template<class K, class M>
void		irtest_constructors(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::reverse_iterator	*fti;
	typename std::map<K, M>::reverse_iterator	*stdi;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());

	testing("i = new reverse_iterator()");
	fti = new typename ft::map<K, M>::reverse_iterator();
	stdi = new typename std::map<K, M>::reverse_iterator();
	delete stdi;
	delete fti;
	incr_score(d);

	testing("i = new reverse_iterator(m.rbegin())");
	fti = new typename ft::map<K, M>::reverse_iterator(ft->rbegin());
	stdi = new typename std::map<K, M>::reverse_iterator(std->rbegin());
	print_comp("i->first", (*stdi)->first, (*fti)->first);
	comp((*stdi)->first == (*fti)->first);
	print_comp("i->second", (*stdi)->second, (*fti)->second);
	comp((*stdi)->second == (*fti)->second);
	delete stdi;
	delete fti;

	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		irtest_copy_op(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::reverse_iterator	fti;
	typename std::map<K, M>::reverse_iterator	stdi;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing("i = m.rbegin()");
	fti = ft->rbegin();
	stdi = std->rbegin();
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		irtest_comp_ops(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::reverse_iterator	fti;
	typename std::map<K, M>::reverse_iterator	stdi;
	typename ft::map<K, M>::reverse_iterator	fti2;
	typename std::map<K, M>::reverse_iterator	stdi2;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing_on("i = m.rbegin()");
	testing_on("i2 = m.rbegin()");
	fti = ft->rbegin();
	fti2 = ft->rbegin();
	stdi = std->rbegin();
	stdi2 = std->rbegin();
	print_comp("i==i2", stdi == stdi2, fti == fti2);
	comp((stdi == stdi2) == (fti == fti2));
	print_comp("i!=i2", stdi != stdi2, fti != fti2);
	comp((stdi != stdi2) == (fti != fti2));
	incr_score(d);
	testing_on("i2++");
	fti2++;
	stdi2++;
	print_comp("i==i2", stdi == stdi2, fti == fti2);
	comp((stdi == stdi2) == (fti == fti2));
	print_comp("i!=i2", stdi != stdi2, fti != fti2);
	comp((stdi != stdi2) == (fti != fti2));
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		irtest_deref_ops(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::reverse_iterator	fti;
	typename std::map<K, M>::reverse_iterator	stdi;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing_on("i = m.rbegin()");
	fti = ft->rbegin();
	stdi = std->rbegin();
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("(*i).m", (*stdi).second, (*fti).second);
	comp((*stdi).second == (*fti).second);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		irtest_val_assign(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::reverse_iterator	fti;
	typename std::map<K, M>::reverse_iterator	stdi;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing("i = m.rbegin()");
	fti = ft->rbegin();
	stdi = std->rbegin();
	testing("*i.m = 1");
	(*fti).second = 1;
	(*stdi).second = 1;
	
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		irtest_incr_decr(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::value_type	*r1;
	typename std::map<K, M>::value_type	*r2;
	typename ft::map<K, M>::reverse_iterator	fti;
	typename std::map<K, M>::reverse_iterator	stdi;
	typename ft::map<K, M>::reverse_iterator	fti2;
	typename std::map<K, M>::reverse_iterator	stdi2;

	create_map_empty_size(std, ft, 0, 5);
	testing_on("radom filled map size: " << std->size());
	testing_on("i = m.rbegin()");
	fti = ft->rbegin();
	stdi = std->rbegin();
	testing("i2 = i++");
	fti2 = fti++;
	stdi2 = stdi++;
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("i2->k", stdi2->first, fti2->first);
	comp(stdi2->first == fti2->first);
	print_comp("i2->m", stdi2->second, fti2->second);
	comp(stdi2->second == fti2->second);
	incr_score(d);

	testing("i2 = ++i");
	fti2 = ++fti;
	stdi2 = ++stdi;
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("i2->k", stdi2->first, fti2->first);
	comp(stdi2->first == fti2->first);
	print_comp("i2->m", stdi2->second, fti2->second);
	comp(stdi2->second == fti2->second);
	incr_score(d);

	testing("i2 = i--");
	fti2 = fti--;
	stdi2 = stdi--;
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("i2->k", stdi2->first, fti2->first);
	comp(stdi2->first == fti2->first);
	print_comp("i2->m", stdi2->second, fti2->second);
	comp(stdi2->second == fti2->second);
	incr_score(d);

	testing("i2 = --i");
	fti2 = --fti;
	stdi2 = --stdi;
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("i2->k", stdi2->first, fti2->first);
	comp(stdi2->first == fti2->first);
	print_comp("i2->m", stdi2->second, fti2->second);
	comp(stdi2->second == fti2->second);
	incr_score(d);

	testing("r = *i++");
	r1 = new typename ft::map<K, M>::value_type(*fti++);
	r2 = new typename std::map<K, M>::value_type(*stdi++);
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("r->k", r2->first, r1->first);
	comp(r2->first == r1->first);
	print_comp("r->m", r2->second, r1->second);
	comp(r2->second == r1->second);
	incr_score(d);

	testing("r = *i--");
	r1 = new typename ft::map<K, M>::value_type(*fti--);
	r2 = new typename std::map<K, M>::value_type(*stdi--);
	print_comp("i->k", stdi->first, fti->first);
	comp(stdi->first == fti->first);
	print_comp("i->m", stdi->second, fti->second);
	comp(stdi->second == fti->second);
	print_comp("r->k", r2->first, r1->first);
	comp(r2->first == r1->first);
	print_comp("r->m", r2->second, r1->second);
	comp(r2->second == r1->second);
	incr_score(d);

	delete std;
	delete ft;
}

template<class K, class M>
void		test_rev_iterator_class(data<K, M> *d) {
	print_title("constructors [default|copy]");
	irtest_constructors(d);
	print_title("operator= ");
	irtest_copy_op(d);
	print_title("operators==|!= ");
	irtest_comp_ops(d);
	print_title("operators*|-> ");
	irtest_deref_ops(d);
	print_title("value assigment");
	irtest_val_assign(d);
	print_title("operator++|-- ");
	irtest_incr_decr(d);
}
/*-----------------------------------ITERATOR ACCESS TESTS-----------------------------------*/

template<class K, class M>
void		test_begin_end(data<K, M> *d, bool empty) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::iterator	fti;
	typename std::map<K, M>::iterator	stdi;

	create_map_empty_size(std, ft, empty, 5);

	testing_on("radom filled map size: " << std->size());

	testing("for(i = m.begin(); i != m.end(); i++) *i;");
	stdi = std->begin();
	for (fti = ft->begin(); fti != ft->end(); fti++) {
		print_comp("i->first", stdi->first, fti->first);
		comp(stdi->first == fti->first);
		print_comp("i->second", stdi->second, fti->second);
		comp(stdi->second == fti->second);
		stdi++;
	}

	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}


template<class K, class M>
void		test_rbegin_rend(data<K, M> *d, bool empty) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename ft::map<K, M>::reverse_iterator	fti;
	typename std::map<K, M>::reverse_iterator	stdi;

	create_map_empty_size(std, ft, empty, 5);

	testing_on("radom filled map size: " << std->size());

	testing("for(i = m.rbegin(); i != m.rend(); i++) *i;");
	stdi = std->rbegin();
	for (fti = ft->rbegin(); fti != ft->rend(); fti++) {
		print_comp("i->first", stdi->first, fti->first);
		comp(stdi->first == fti->first);
		print_comp("i->second", stdi->second, fti->second);
		comp(stdi->second == fti->second);
		stdi++;
	}

	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}
	
template<class K, class M>
void		test_iterator_access(data<K, M> *d) {
	print_title("begin end");
	test_begin_end(d, 0);
	test_begin_end(d, 1);
	print_title("rbegin rend");
	test_rbegin_rend(d, 0);
	test_rbegin_rend(d, 1);
}

/*-----------------------------------CAPACITY TESTS-----------------------------------*/

template<class K, class M>
void		test_empty(data<K, M> *d, bool empty) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	bool				r1;
	bool				r2;

	create_map(std, ft, empty);
	testing_on("radom filled map size: " << std->size());

	r1 = std->empty();
	r2 = ft->empty();
	print_comp("empty()", r1, r2);
	comp(r1 == r2);

	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		test_size(data<K, M> *d, bool empty) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename std::map<K, M>::size_type		r1;
	typename ft::map<K, M>::size_type		r2;

	create_map(std, ft, empty);
	testing_on("radom filled map size: " << std->size());

	r1 = std->size();
	r2 = ft->size();
	print_comp("size()", r1, r2);
	comp(r1 == r2);


	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		test_max_size(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	typename std::map<K, M>::size_type		r1;
	typename ft::map<K, M>::size_type		r2;

	create_map(std, ft, 1);
	testing_on("radom filled map size: " << std->size());

	r1 = std->max_size();
	r2 = ft->max_size();
	print_comp("max_size()", r1, r2);
	comp(r1 == r2);


	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		test_capacity(data<K, M> *d) {
	print_title("empty");
	test_empty(d, 0);
	test_empty(d, 1);
	print_title("size");
	test_size(d, 0);
	test_size(d, 1);
	print_title("max_size");
	test_max_size(d);
	test_max_size(d);
}
/*-----------------------------------ELEMENT ACCESS TESTS-----------------------------------*/

template<class K, class M>
void		test_access_op(data<K, M> *d, bool empty) {
	std::map<K, M>						*std = NULL;
	ft::map<K, M>						*ft = NULL;
	typename std::map<K, M>::iterator	stdi;
	typename ft::map<K, M>::iterator	fti;
	int									test_size;


	create_map(std, ft, empty);
	testing_on("radom filled map size: " << std->size());

	test_size = 5;
	for (int i = 0; i < test_size; i++) {
		if (rand() % 2 && !ft->empty() && !std->empty()) {
			int											offset = rand() % std->size();
			testing("ret = m[(m.begin() + " << offset << ").k]");
			stdi = std->begin();
			fti = ft->begin();
			for (int i = 0; i < offset; i++) {
				stdi++;
				fti++;
			}
			typename std::map<K, M>::mapped_type&		r1 = (*std)[stdi->first];
			typename ft::map<K, M>::mapped_type&		r2 = (*ft)[fti->first];
			print_comp("ret", r1, r2);
			comp(r1 == r2);
		} else {
			K											key = randomize<K>();
			testing("ret = m[" << key << "]");
			typename std::map<K, M>::mapped_type&		r1 = (*std)[key];
			typename ft::map<K, M>::mapped_type&		r2 = (*ft)[key];
			print_comp("ret", r1, r2);
			comp(r1 == r2);
		}
	}

	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}

template<class K, class M>
void		test_element_access(data<K, M> *d) {
	print_title("operator[]");
	test_access_op(d, 0);
	test_access_op(d, 1);
}
/*-----------------------------------MODIFIERS TESTS-----------------------------------*/

template<class K, class M>
void		test_insert_single(data<K, M> *d, bool empty) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	M					val;
	K					key;
	int					size;
	typename std::pair<typename std::map<K, M>::iterator, bool>	r1;
	typename std::pair<typename ft::map<K, M>::iterator, bool>	r2;

	create_map(std, ft, empty);
	testing_on("radom filled map size: " << std->size());

	size = rand() % 5;
	for (int i = 0; i < size; i++) {
		key = rand() % 255;
		val = randomize<M>();
		testing("m.insert(pair(" << key << ", " << val << ")");
		r1 = std->insert(std::pair<K, M>(key, val));
		r2 = ft->insert(std::pair<K, M>(key, val));
		print_comp("(*ret.i).k", (*r1.first).first, (*r2.first).first);
		comp((*r1.first).first == (*r2.first).first);
		print_comp("(*ret.i).m", (*r1.first).second, (*r2.first).second);
		comp((*r1.first).second == (*r2.first).second);
		print_comp("*ret.b", r1.second, r2.second);
		comp(r1.second == r2.second);
		if (i % 2 == 0) {
			testing("m.insert(pair(" << key << ", " << val << ")");
			r1 = std->insert(std::pair<K, M>(key, val));
			r2 = ft->insert(std::pair<K, M>(key, val));
			print_comp("(*ret.i).k", (*r1.first).first, (*r2.first).first);
			comp((*r1.first).first == (*r2.first).first);
			print_comp("(*ret.i).m", (*r1.first).second, (*r2.first).second);
			comp((*r1.first).second == (*r2.first).second);
			print_comp("*ret.b", r1.second, r2.second);
			comp(r1.second == r2.second);
		}
	}

	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}


template<class K, class M>
void		test_insert_hint(data<K, M> *d) {
	std::map<K, M>		*std = NULL;
	ft::map<K, M>		*ft = NULL;
	M					val;
	K					key;
	int					size;
	int					offset;
	typename std::map<K, M>::iterator	stdi;
	typename ft::map<K, M>::iterator	fti;

	create_map(std, ft, 0);
	testing_on("radom filled map size: " << std->size());

	size = rand() % 5;
	for (int i = 0; i < size; i++) {
		key = rand() % 255;
		val = randomize<M>();
		offset = (i != 0) ? rand() % i : 0;
		stdi = std->begin();
		fti = ft->begin();
		for (int i2 = 0; i2 < offset; i2++) {
			++stdi;
			++fti;
		}
		testing("m.insert(begin + " << offset << ", pair(" << key << ", " << val << ")");
		stdi = std->insert(stdi, std::pair<K, M>(key, val));
		fti = ft->insert(fti, std::pair<K, M>(key, val));
		print_comp("i->k", stdi->first, fti->first);
		comp(stdi->first == fti->first);
		print_comp("i->m", stdi->second, fti->second);
		comp(stdi->second == fti->second);
		if (i % 2 == 0) {
			offset = (i != 0) ? rand() % i : 0;
			stdi = std->begin();
			fti = ft->begin();
			for (int i2 = 0; i2 < offset; i2++) {
				++stdi;
				++fti;
			}
			testing("m.insert(begin + " << offset << ", pair(" << key << ", " << val << ")");
			stdi = std->insert(stdi, std::pair<K, M>(key, val));
			fti = ft->insert(fti, std::pair<K, M>(key, val));
			print_comp("i->k", stdi->first, fti->first);
			comp(stdi->first == fti->first);
			print_comp("i->m", stdi->second, fti->second);
			comp(stdi->second == fti->second);
		}
	}

	equal(std, ft);
	incr_score(d);
	delete std;
	delete ft;
}



template<class K, class M>
void		test_modifiers(data<K, M> *d) {
	print_title("insert [single]");
	test_insert_single(d, 0);
	test_insert_single(d, 1);
	print_title("insert [hint]");
	test_insert_hint(d);
}
/*-----------------------------------OBSERVERS TESTS-----------------------------------*/
/*-----------------------------------OPERATIONS TESTS-----------------------------------*/

/*-----------------------------------MAIN-----------------------------------*/
template<class K, class M>
void		do_tests(void) {
	data<K, M>		*d;

	d = init_data<K, M>();

	print_group_title("CONSTRUCTORS");
	test_constructors(d);
	print_group_title("ITERATOR CLASS");
	test_iterator_class(d);
	print_group_title("REVERSE ITERATOR CLASS");
	test_rev_iterator_class(d);
	print_group_title("ITERATOR ACCESS");
	test_iterator_access(d);
	print_group_title("CAPACITY");
	test_capacity(d);
	print_group_title("ELEMENT ACCESS");
	test_element_access(d);
	print_group_title("MODIFIERS");
	test_modifiers(d);
	/* print_group_title("OBSERVERS"); */
	/* test_observers(d); */
	/* print_group_title("OPERATIONS"); */
	/* test_operations(d); */
	/* print_group_title("ITERATOR CLASS"); */
	/* test_iterator_class(d); */

	std::cout << std::endl << GREEN << "pass: " << RESET << d->pass << RED << "\tfail:\t" << RESET << d->fail << std::endl;
	delete d;
}

int			main(void) {
	srand((int) time(0));
	do_tests<int, int>();
	/* while(1); */
}

