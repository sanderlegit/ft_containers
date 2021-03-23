/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   test_vector.cpp                                   e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/11 13:50:52 by dries             *8*   8   *8*          */
/*   Updated: 2021/03/23 15:16:59 by dries               **ee8ee**            */
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
//#define EQUALITY	true
#define EQUALITY	false
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


template<class T>
void		test_equivalence(data<T> *d, std::vector<T> *std, ft::vector<T> *ft, bool capacity) {
	bool			r1;
	bool			r2;
	T				r3;
	T				r4;
	size_t			r5;
	size_t			r6;


	if (EQUALITY)
		std::cout << "  testing list equality" << std::endl;
	r1 = std->empty();
	r2 = ft->empty();
	eq_print_comp("empty()", r1, r2);
	comp(r1 == r2);

	if (capacity) {
		r5 = std->capacity();
		r6 = ft->capacity();
		eq_print_comp("capacity()", r5, r6);
		comp(r5 <= r6);
	}

	if (!r1 && !r2) {
		r3 = std->back();
		r4 = ft->back();
		r5 = std->size();
		r6 = ft->size();
		eq_print_comp("back()", r3, r4);
		comp(r3 == r4);
		r3 = std->front();
		r4 = ft->front();
		std->pop_back();
		ft->pop_back();
		eq_print_comp("front()", r3, r4);
		comp(r3 == r4);
		eq_print_comp("size()", r5, r6);
		comp(r5 == r6);
		if (EQUALITY)
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
				eq_print_comp("back", r3, r4);
			if (VVERBOSE)
				eq_print_comp("size", r5, r6);
			comp(r1 == r2);
			comp(r3 == r4);
			comp(r5 == r6);
		}
		r1 = std->empty();
		r2 = ft->empty();
		r5 = std->size();
		r6 = ft->size();
		eq_print_comp("empty()", r1, r2);
		eq_print_comp("size()", r5, r6);
	} else if (!r1 && r2) {
		r3 = std->back();
		r5 = std->size();
		eq_print_comp_labels("back()", "std", "EMPTY!", r3, 0);
		r3 = std->back();
		std->pop_back();
		ft->pop_back();
		eq_print_comp_labels("back()", "std", "EMPTY!", r3, 0);
		eq_print_comp_labels("size()", "std", "EMPTY!", r5, 0);
		if (EQUALITY)
			std::cout << "  iterating through..." << std::endl;
		while (!std->empty()) {
			r1 = std->empty();
			r3 = std->back();
			r5 = std->size();
			std->pop_back();
			if (VVERBOSE)
				eq_print_comp_labels("back", "std", "EMPTY!", r3, 0);
			if (VVERBOSE)
				eq_print_comp_labels("size", "std", "EMPTY!", r5, 0);
		}
		r1 = std->empty();
		r5 = std->size();
		eq_print_comp_labels("empty()", "std", "EMPTY!", r1, 0);
		eq_print_comp_labels("size()", "std", "EMPTY!", r5, 0);
	} else if (r1 && !r2) {
		r3 = ft->back();
		r5 = ft->size();
		eq_print_comp_labels("back()", "EMPTY!", "ft", 0, r3);
		r3 = ft->back();
		ft->pop_back();
		ft->pop_back();
		eq_print_comp_labels("back()", "EMPTY!", "ft", 0, r3);
		eq_print_comp_labels("size()", "EMPTY!", "ft", 0, r5);
		if (EQUALITY)
			std::cout << "  iterating through..." << std::endl;
		while (!ft->empty()) {
			r1 = ft->empty();
			r3 = ft->back();
			r5 = ft->size();
			ft->pop_back();
			if (VVERBOSE)
				eq_print_comp_labels("back", "EMPTY!", "ft", 0, r3);
			if (VVERBOSE)
				eq_print_comp_labels("size", "EMPTY!", "ft", 0, r5);
		}
		r1 = ft->empty();
		r5 = ft->size();
		eq_print_comp_labels("empty()", "EMPTY!", "ft", 0, r1);
		eq_print_comp_labels("size()", "EMPTY!", "ft", 0, r5);
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

/*	Copy Constructor Tests:
 *	size to size	(emptya, emptyb)
 *	size to unininitialzed	(emptysrc)
 */

template<class T>
void		test_constructor_copy(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("dest: random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("src: random filled vector size " << stdb->size());
	testing("dest = new vector(src)");
	stda = new std::vector<T>(*stdb);
	fta = new ft::vector<T>(*ftb);
	equal(stda, fta);
	equal(stdb, ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	stda = NULL;
	fta = NULL;
	incr_score(d);

	if (emptyb)
		return;

	create_vector(stdb, ftb, emptyb);
	testing_on("src: random filled vector size " << stdb->size());
	testing_on("dest: unininitialzed");
	testing("dest = new vector(src)");
	stda = new std::vector<T>(*stdb);
	fta = new ft::vector<T>(*ftb);
	equal(stda, fta);
	equal(stdb, ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}

template<class T>
void		test_operator_equals(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("dest: random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("src: random filled vector size " << stdb->size());
	testing("dest = src");
	*stda = *stdb;
	*fta = *ftb;
	equal(stda, fta);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	stda = NULL;
	fta = NULL;
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
	print_title("constructor [copy]");
	test_constructor_copy(d, 0, 0);
	test_constructor_copy(d, 0, 1);
	test_constructor_copy(d, 1, 0);
	test_constructor_copy(d, 1, 1);
	print_title("operator= ");
	test_operator_equals(d, 0, 0);
	test_operator_equals(d, 0, 1);
	test_operator_equals(d, 1, 0);
	test_operator_equals(d, 1, 1);
}

/*-----------------------------------ITERATORS-----------------------------------*/


template<class T>
void		test_it_constructors(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>	*stdv = NULL;
	ft::vector<T>	*ftv = NULL;
	stditer			stdi;
	stditer			stdi2;
	ftiter			fti = NULL;
	ftiter			fti2 = NULL;

	testing("i1 = new iterator()");
	stdi = stditer();
	fti = ftiter();
	comp(1 == 1);
	incr_score(d);

	create_vector(stdv, ftv, 0);
	testing_on("random filled vector size " << stdv->size());
	testing_on("i1 = vector->begin()");
	stdi = stdv->begin();
	fti = ftv->begin();
	testing("i2 = new iterator(i1)");
	stdi2 = stditer(stdi);
	fti2 = ftiter(fti);
	test("*i2 == *i1", *stdi2 == *stdi, *fti2 == *fti);
	test("*i", *stdi2, *fti2);
	incr_score(d);

	testing("i2 = i1");
	stdi2 = stdi;
	fti2 = fti;
	test("*i2 == *i1", *stdi2 == *stdi, *fti2 == *fti);
	test("*i", *stdi2, *fti2);
	incr_score(d);

	testing("destruction");
	comp(1 == 1);
	incr_score(d);
}

template<class T>
void		test_eq_neq(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>	*stdv = NULL;
	ft::vector<T>	*ftv = NULL;
	stditer			stdi;
	stditer			stdi2;
	ftiter			fti = NULL;
	ftiter			fti2 = NULL;

	create_vector(stdv, ftv, 0);
	testing_on("random filled vector size " << stdv->size());
	testing_on("i1 = vector->begin(); i2 = i1;");
	stdi = stdv->begin();
	fti = ftv->begin();
	stdi2 = stditer(stdi);
	fti2 = ftiter(fti);
	test("i2 == i1", stdi2 == stdi, fti2 == fti);
	test("i2 != i1", stdi2 != stdi, fti2 != fti);
	test("*i", *stdi2, *fti2);
	incr_score(d);

	testing_on("i1++");
	stdi++;
	fti++;
	test("i2 == i1", stdi2 == stdi, fti2 == fti);
	test("i2 != i1", stdi2 != stdi, fti2 != fti);
	incr_score(d);
}

template<class T>
void		test_dereference(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>		*stdv = NULL;
	ft::vector<T>		*ftv = NULL;
	stditer				stdi;
	ftiter				fti = NULL;

	create_vector(stdv, ftv, 0);
	testing_on("random filled vector size " << stdv->size());
	stdi = stdv->begin();
	fti = ftv->begin();
	test("*i", *stdi, *fti);
	incr_score(d);
}

struct	potato {
	potato(std::string s) : ego_sum(s) {}

	std::string ego_sum;
};

template<class T>
void		test_detaterence(data<T> *d) {
	std::vector<potato>				std_votato;
	ft::vector<potato>				ft_votato;
	std::vector<potato>::iterator	std_pitato;
	ft::vector<potato>::iterator	ft_pitato;

	testing_on("i = potato_vector.begin()");
	std_votato.push_back(potato("when i sleep, i dream of potato"));
	ft_votato.push_back(potato("when i sleep, i dream of potato"));
	std_pitato = std_votato.begin();
	ft_pitato = ft_votato.begin();
	test("i->var", std_pitato->ego_sum, std_pitato->ego_sum);
	incr_score(d);

	testing("i->var = val");
	std_pitato->ego_sum = "potato blood runs through my veins";
	ft_pitato->ego_sum = "potato blood runs through my veins";
	test("i->var", std_pitato->ego_sum, std_pitato->ego_sum);
	incr_score(d);
}

template<class T>
void		test_assignment(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>		*stdv = NULL;
	ft::vector<T>		*ftv = NULL;
	stditer				stdi;
	ftiter				fti;
	T					val;

	create_vector(stdv, ftv, 0);
	testing_on("random filled vector size " << stdv->size());
	stdi = stdv->begin();
	fti = ftv->begin();
	val = randomize<T>();
	testing("*i = " << val);
	*stdi = val;
	*fti = val;
	test("*i", *stdi, *fti);
	incr_score(d);
}

template<class T>
void		test_incr_decr(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>		*stdv = NULL;
	ft::vector<T>		*ftv = NULL;
	stditer				stdi;
	stditer				stdir;
	ftiter				fti;
	ftiter				ftir;
	T					ftr;
	T					stdr;

	create_vector_size(stdv, ftv, 10);
	testing_on("random filled vector size " << stdv->size());
	testing_on("i = vector->begin()");
	stdi = stdv->begin();
	fti = ftv->begin();

	testing("ret = i++");
	stdir = stdi++;
	ftir = fti++;
	test("*i", *stdi, *fti);
	test("*ret", *stdir, *ftir);
	incr_score(d);

	testing("ret = ++i");
	stdir = ++stdi;
	ftir = ++fti;
	test("*i", *stdi, *fti);
	test("*ret", *stdir, *ftir);
	incr_score(d);

	testing("ret = *i++");
	stdr = *stdi++;
	ftr = *fti++;
	test("*i", *stdi, *fti);
	test("ret", stdr, ftr);
	incr_score(d);

	testing("ret = i--");
	stdir = stdi--;
	ftir = fti--;
	test("*i", *stdi, *fti);
	test("*ret", *stdir, *ftir);
	incr_score(d);

	testing("ret = --i");
	stdir = --stdi;
	ftir = --fti;
	test("*i", *stdi, *fti);
	test("*ret", *stdir, *ftir);
	incr_score(d);

	testing("ret = *i--");
	stdr = *stdi--;
	ftr = *fti--;
	test("*i", *stdi, *fti);
	test("ret", stdr, ftr);
	incr_score(d);
}

template<class T>
void		test_add_sub(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>		*stdv = NULL;
	ft::vector<T>		*ftv = NULL;
	stditer				stdi;
	stditer				stdir;
	ftiter				fti;
	ftiter				ftir;
	int					offset;
	typename stditer::difference_type	stdr;
	typename ftiter::difference_type	ftr;

	create_vector_size(stdv, ftv, 50);
	testing_on("random filled vector size " << stdv->size());
	testing_on("i = vector->begin()");
	stdi = stdv->begin();
	fti = ftv->begin();

	offset = (rand() % 5) + 1;
	testing("ret = i + " << offset);
	stdir = stdi + offset;
	ftir = fti + offset;
	test("*i", *stdi, *fti);
	test("*ret", *stdir, *ftir);
	incr_score(d);

	offset = (rand() % 5) + 1;
	testing("ret = " << offset << " + i");
	stdir = offset + stdi;
	ftir = offset + fti;
	test("*i", *stdi, *fti);
	test("*ret", *stdir, *ftir);
	incr_score(d);

	testing_on("i = vector->begin(); for (1->10) i++");
	stdi = stdv->begin();
	fti = ftv->begin();
	for (int i = 0; i < 10; i++) {
		++stdi;
		++fti;
	}

	offset = (rand() % 5) + 1;
	testing("ret = i - " << offset);
	stdir = stdi - offset;
	ftir = fti - offset;
	test("*i", *stdi, *fti);
	test("*ret", *stdir, *ftir);
	incr_score(d);

	testing("ret = i1 - i2");
	stdr = stdi - stdir;
	ftr = fti - ftir;
	test("*i", *stdi, *fti);
	test("*i2", *stdir, *ftir);
	test("ret", stdr, ftr);
	incr_score(d);

	testing("ret = i2 - i1");
	stdr = stdir - stdi;
	ftr = ftir - fti;
	test("*i", *stdi, *fti);
	test("*i2", *stdir, *ftir);
	test("ret", stdr, ftr);
	incr_score(d);
}

template<class T>
void		test_gt_lt_eqgt_eqlt(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>		*stdv = NULL;
	ft::vector<T>		*ftv = NULL;
	stditer				stdi;
	stditer				stdi2;
	ftiter				fti;
	ftiter				fti2;
	int					offset;

	create_vector_size(stdv, ftv, 50);
	testing_on("random filled vector size " << stdv->size());
	testing_on("i1/2 = vector->begin()");
	stdi = stdv->begin();
	stdi2 = stdv->begin();
	fti = ftv->begin();
	fti2 = ftv->begin();

	test("*i1", *stdi, *fti);
	test("*i2", *stdi2, *fti2);
	test("i1 < i2", stdi < stdi2, fti < fti2);
	incr_score(d);
	test("i1 > i2", stdi > stdi2, fti > fti2);
	test("i2 > i1", stdi2 > stdi, fti2 > fti);
	incr_score(d);
	test("i1 <= i2", stdi <= stdi2, fti <= fti2);
	test("i2 <= i1", stdi2 <= stdi, fti2 <= fti);
	incr_score(d);
	test("i1 >= i2", stdi >= stdi2, fti >= fti2);
	incr_score(d);

	offset = (rand() % 5) + 1;
	testing_on("i2 += " << offset);
	for (int i = 0; i < offset; i++) {
		stdi2++;
		fti2++;
	}
	test("*i1", *stdi, *fti);
	test("*i2", *stdi2, *fti2);
	test("i1 < i2", stdi < stdi2, fti < fti2);
	incr_score(d);
	test("i1 > i2", stdi > stdi2, fti > fti2);
	test("i2 > i1", stdi2 > stdi, fti2 > fti);
	incr_score(d);
	test("i1 <= i2", stdi <= stdi2, fti <= fti2);
	test("i2 <= i1", stdi2 <= stdi, fti2 <= fti);
	incr_score(d);
	test("i1 >= i2", stdi >= stdi2, fti >= fti2);
	incr_score(d);
}

template<class T>
void		test_plus_eq_minus_eq(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>		*stdv = NULL;
	ft::vector<T>		*ftv = NULL;
	stditer				stdi;
	ftiter				fti;
	int					offset;

	create_vector_size(stdv, ftv, 50);
	testing_on("random filled vector size " << stdv->size());
	testing_on("i1/2 = vector->begin() + 25");
	stdi = stdv->begin() + 25;
	fti = ftv->begin() + 25;

	offset = (rand() % 5) + 1;
	testing("i += " << offset);
	stdi += offset;
	fti += offset;
	test("*i1", *stdi, *fti);
	incr_score(d);

	testing("i -= " << offset);
	stdi -= offset;
	fti -= offset;
	test("*i1", *stdi, *fti);
	incr_score(d);

	offset *= -1;
	testing("i += " << offset);
	stdi += offset;
	fti += offset;
	test("*i1", *stdi, *fti);
	incr_score(d);

	testing("i -= " << offset);
	stdi -= offset;
	fti -= offset;
	test("*i1", *stdi, *fti);
	incr_score(d);
}

template<class T>
void		test_offset_operator(data<T> *d) {
	typedef typename std::vector<T>::iterator	stditer;
	typedef typename ft::vector<T>::iterator	ftiter;

	std::vector<T>		*stdv = NULL;
	ft::vector<T>		*ftv = NULL;
	stditer				stdi;
	ftiter				fti;
	int					offset;

	create_vector_size(stdv, ftv, 50);
	testing_on("random filled vector size " << stdv->size());
	testing_on("i1/2 = vector->begin()");
	stdi = stdv->begin();
	fti = ftv->begin();

	offset = (rand() % 50);
	testing("offset = " << offset);
	test("i[offset]", stdi[offset], fti[offset]);
	incr_score(d);

	offset = 0;
	testing("offset = " << offset);
	test("i[offset]", stdi[offset], fti[offset]);
	incr_score(d);
}


template<class T>
void		test_iterators(data<T> *d) {
	test_it_constructors(d);
	test_eq_neq(d);
	test_dereference(d);
	test_detaterence(d);
	test_assignment(d);
	test_incr_decr(d);
	test_add_sub(d);
	test_gt_lt_eqgt_eqlt(d);
	test_plus_eq_minus_eq(d);
	test_offset_operator(d);
}

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
	std->reserve(size);
	ft->reserve(size);
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = std->size() + 1;
	testing("reserve(" << size << ")");
	std->reserve(size);
	ft->reserve(size);
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	size = std->size();
	testing("reserve(" << size << ")");
	std->reserve(size);
	ft->reserve(size);
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
	std->reserve(size);
	ft->reserve(size);
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	size = rand() % std->size();
	testing("reserve(" << size << ")");
	std->reserve(size);
	ft->reserve(size);
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;

	create_vector(std, ft, 0);
	testing_on("random filled vector size " << std->size());
	size = 0;
	testing("reserve(" << size << ")");
	std->reserve(size);
	ft->reserve(size);
	test_equivalence(d, std, ft, 1);
	incr_score(d);
	delete std;
	delete ft;
}

template<class T>
void		test_capacity(data<T> *d) {
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
	std->push_back(1);
	ft->push_back(1);
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
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
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
		std_threw = 1;
	}
	try {
		ftr1 = ft->at(idx);
		ft_threw = 0;
	} catch (std::exception& e) {
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

/*	Swap tests:
 *	swap empty with empty
 *	swap empty with full
 *	swap full with empty
 *	swap full with full
 *	swap size 1 with size 1	*/

template<class T>
void		test_swap(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("from random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("to random filled vector size " << stdb->size());
	testing("a.swap(b)");
	stda->swap(*stdb);
	fta->swap(*ftb);
	equal(stda, fta);
	equal(stdb, ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	if (emptya || emptyb)
		return;

	create_vector_size(stda, fta, 1);
	testing_on("from random filled vector size " << stda->size());
	create_vector_size(stdb, ftb, 1);
	testing_on("to random filled vector size " << stdb->size());
	testing("a.swap(b)");
	stda->swap(*stdb);
	fta->swap(*ftb);
	equal(stda, fta);
	equal(stdb, ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}

template<class T>
void		test_clear(data<T> *d, bool empty) {
	std::vector<T>		*std = NULL;
	ft::vector<T>		*ft = NULL;

	create_vector(std, ft, empty);
	testing_on("random filled vector size " << std->size());
	testing("clear()");
	std->clear();
	ft->clear();
	equal(std, ft);
	delete std;
	delete ft;
	incr_score(d);

	if (empty)
		return;

	create_vector_size(std, ft, 1);
	testing_on("random filled vector size " << std->size());
	testing("clear()");
	std->clear();
	ft->clear();
	equal(std, ft);
	delete std;
	delete ft;
	incr_score(d);
}

template<class T>
void		test_modifiers(data<T> *d) {
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
	print_title("swap");		//TODO check iterator validity
	test_swap(d, 0, 0);
	test_swap(d, 0, 1);
	test_swap(d, 1, 0);
	test_swap(d, 1, 1);
	print_title("clear");
	test_clear(d, 0);
	test_clear(d, 1);
}

/*-----------------------------------NON-MEMBER OVERLOADS-----------------------------------*/


template<class T>
void		test_swap_nm(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("from random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("to random filled vector size " << stdb->size());
	testing("swap(a, b)");
	std::swap(*stda, *stdb);
	ft::swap(*fta, *ftb);
	equal(stda, fta);
	equal(stdb, ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	if (emptya || emptyb)
		return;

	create_vector_size(stda, fta, 1);
	testing_on("from random filled vector size " << stda->size());
	create_vector_size(stdb, ftb, 1);
	testing_on("to random filled vector size " << stdb->size());
	testing("swap(a, b)");
	std::swap(*stda, *stdb);
	ft::swap(*fta, *ftb);
	equal(stda, fta);
	equal(stdb, ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}

template<class T>
void		test_eq_comp(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("b: random filled vector size " << stdb->size());
	test("a == b", *stda == *stdb, *fta == *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	if (emptya || emptyb)
		return;

	create_vector(stda, fta, 0);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, 1);
	*stdb = *stda;
	*ftb = *fta;
	testing_on("b: copy of a");
	test("a == b", *stda == *stdb, *fta == *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	create_vector_size(stda, fta, 1);
	testing_on("a: random filled vector size " << stda->size());
	create_vector_size(stdb, ftb, 1);
	testing_on("b: random filled vector size " << stdb->size());
	test("a == b", *stda == *stdb, *fta == *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}

template<class T>
void		test_neq_comp(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("b: random filled vector size " << stdb->size());
	test("a != b", *stda != *stdb, *fta != *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	if (emptya || emptyb)
		return;

	create_vector(stda, fta, 0);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, 1);
	*stdb = *stda;
	*ftb = *fta;
	testing_on("b: copy of a");
	test("a != b", *stda != *stdb, *fta != *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	create_vector_size(stda, fta, 1);
	testing_on("a: random filled vector size " << stda->size());
	create_vector_size(stdb, ftb, 1);
	testing_on("b: random filled vector size " << stdb->size());
	test("a != b", *stda != *stdb, *fta != *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}

template<class T>
void		test_lt_comp(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("b: random filled vector size " << stdb->size());
	test("a < b", *stda < *stdb, *fta < *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	if (emptya || emptyb)
		return;

	create_vector(stda, fta, 0);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, 1);
	*stdb = *stda;
	*ftb = *fta;
	testing_on("b: copy of a");
	test("a < b", *stda < *stdb, *fta < *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	create_vector_size(stda, fta, 1);
	testing_on("a: random filled vector size " << stda->size());
	create_vector_size(stdb, ftb, 1);
	testing_on("b: random filled vector size " << stdb->size());
	test("a < b", *stda < *stdb, *fta < *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}

template<class T>
void		test_lte_comp(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("b: random filled vector size " << stdb->size());
	test("a <= b", *stda <= *stdb, *fta <= *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	if (emptya || emptyb)
		return;

	create_vector(stda, fta, 0);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, 1);
	*stdb = *stda;
	*ftb = *fta;
	testing_on("b: copy of a");
	test("a <= b", *stda <= *stdb, *fta <= *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	create_vector_size(stda, fta, 1);
	testing_on("a: random filled vector size " << stda->size());
	create_vector_size(stdb, ftb, 1);
	testing_on("b: random filled vector size " << stdb->size());
	test("a <= b", *stda <= *stdb, *fta <= *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}

template<class T>
void		test_gt_comp(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("b: random filled vector size " << stdb->size());
	test("a > b", *stda > *stdb, *fta > *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	if (emptya || emptyb)
		return;

	create_vector(stda, fta, 0);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, 1);
	*stdb = *stda;
	*ftb = *fta;
	testing_on("b: copy of a");
	test("a > b", *stda > *stdb, *fta > *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	create_vector_size(stda, fta, 1);
	testing_on("a: random filled vector size " << stda->size());
	create_vector_size(stdb, ftb, 1);
	testing_on("b: random filled vector size " << stdb->size());
	test("a > b", *stda > *stdb, *fta > *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}


template<class T>
void		test_gte_comp(data<T> *d, bool emptya, bool emptyb) {
	std::vector<T>		*stda = NULL;
	ft::vector<T>		*fta = NULL;
	std::vector<T>		*stdb = NULL;
	ft::vector<T>		*ftb = NULL;

	create_vector(stda, fta, emptya);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, emptyb);
	testing_on("b: random filled vector size " << stdb->size());
	test("a >= b", *stda >= *stdb, *fta >= *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	if (emptya || emptyb)
		return;

	create_vector(stda, fta, 0);
	testing_on("a: random filled vector size " << stda->size());
	create_vector(stdb, ftb, 1);
	*stdb = *stda;
	*ftb = *fta;
	testing_on("b: copy of a");
	test("a >= b", *stda >= *stdb, *fta >= *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);

	create_vector_size(stda, fta, 1);
	testing_on("a: random filled vector size " << stda->size());
	create_vector_size(stdb, ftb, 1);
	testing_on("b: random filled vector size " << stdb->size());
	test("a >= b", *stda >= *stdb, *fta >= *ftb);
	delete stda;
	delete fta;
	delete stdb;
	delete ftb;
	incr_score(d);
}


template<class T>
void		test_non_member_overloads(data<T> *d) {
	print_title("swap (non-member)");		//TODO check iterator validity
	test_swap_nm(d, 0, 0);
	test_swap_nm(d, 0, 1);
	test_swap_nm(d, 1, 0);
	test_swap_nm(d, 1, 1);
	print_title("operator== ");
	test_eq_comp(d, 0, 0);
	test_eq_comp(d, 0, 1);
	test_eq_comp(d, 1, 0);
	test_eq_comp(d, 1, 1);
	print_title("operator!= ");
	test_neq_comp(d, 0, 0);
	test_neq_comp(d, 0, 1);
	test_neq_comp(d, 1, 0);
	test_neq_comp(d, 1, 1);
	print_title("operator< ");
	test_lt_comp(d, 0, 0);
	test_lt_comp(d, 0, 1);
	test_lt_comp(d, 1, 0);
	test_lt_comp(d, 1, 1);
	print_title("operator<= ");
	test_lte_comp(d, 0, 0);
	test_lte_comp(d, 0, 1);
	test_lte_comp(d, 1, 0);
	test_lte_comp(d, 1, 1);
	print_title("operator> ");
	test_gt_comp(d, 0, 0);
	test_gt_comp(d, 0, 1);
	test_gt_comp(d, 1, 0);
	test_gt_comp(d, 1, 1);
	print_title("operator>= ");
	test_gte_comp(d, 0, 0);
	test_gte_comp(d, 0, 1);
	test_gte_comp(d, 1, 0);
	test_gte_comp(d, 1, 1);
}

/*-----------------------------------MAIN-----------------------------------*/

template<class T>
void		do_tests(void) {
	data<T>		*d;

	d = init_data<T>();

	print_group_title("CONSTRUCTORS");
	test_constructors(d);
	//print_group_title("ITERATORS");
	//test_iterators(d);
	print_group_title("CAPACITY");
	test_capacity(d);
	print_group_title("ELEMENT ACCESS");
	test_element_access(d);
	print_group_title("MODIFIERS");
	test_modifiers(d);
	print_group_title("NON-MEMBER OVERLOADS");
	test_non_member_overloads(d);

	print_group_title("ITERATORS");
	test_iterators(d);

	std::cout << std::endl << GREEN << "pass: " << RESET << d->pass << RED << "\tfail:\t" << RESET << d->fail << std::endl;
	delete d;
}

int			main(void) {
	srand((int) time(0));
	do_tests<int>();
}

