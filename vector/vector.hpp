/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   vector.hpp                                        e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/10 16:43:21 by dries             *8*   8   *8*          */
/*   Updated: 2021/03/11 15:06:05 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iterator>
#include <memory>

/*	memory		allocator
 *	iterator	iterator_tag	*/

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class vector { //https://cplusplus.com/reference/vector/vector/
/*-------------------------------------------TYPEDEFS-------------------------------------------*/
		public:
/*	member type				definition			
 *					notes
 *	value_type				The first template parameter (T)	
 *	allocator_type			The second template parameter (Alloc)	allocator<value_type>
 *	reference				allocator_type::reference				value_type&
 *	const_reference			allocator_type::const_reference			const value_type&
 *	pointer					allocator_type::pointer					value_type*
 *	const_pointer			allocator_type::const_pointer			const value_type*
 *	difference_type			a signed integral type, identical to: 	usually ptrdiff_t
 *							iterator_traits<iterator>::difference_type	
 *	size_type				an unsigned integral type that can		usually size_t
 *							represent any non-negative value of difference_type		*/
			typedef	T										value_type;
			typedef	Alloc									allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef	value_type*								pointer;
			typedef	const value_type*						const_pointer;
			typedef	ptrdiff_t								difference_type;
			typedef size_t									size_type;
		private:

/*-------------------------------------------ITERATORS-------------------------------------------*/
			template<class value_t, class reference_t, class pointer_t>
			class VectorRandIterator { //https://en.cppreference.com/w/cpp/iterator/iterator
				public:
					typedef std::random_access_iterator_tag			iterator_category;
			};

			template<class value_t, class reference_t, class pointer_t>
			class ReverseVectorRandIterator { //https://en.cppreference.com/w/cpp/iterator/iterator
				public:
					typedef std::random_access_iterator_tag			iterator_category;
			};

/*	iterator				a random access iterator to value_type	convertible to const_iterator
 *	const_iterator			a random access iterator to const 
 *							value_type	
 *	reverse_iterator		reverse_iterator<iterator>	
 *	const_reverse_iterator	reverse_iterator<const_iterator>	*/

			typedef	VectorRandIterator<T, T&, T*>							iterator;
			typedef	VectorRandIterator<const T, const T&, const T*>			const_iterator;
			typedef	ReverseVectorRandIterator<T, T&, T*>					reverse_iterator;
			typedef	ReverseVectorRandIterator<const T, const T&, const T*>	const_reverse_iterator;

/*-------------------------------------------MEMBER VARIABLES-------------------------------------------*/
	private:
		size_type		_size;
		size_type		_capacity;
		pointer			_data;
		Alloc			_alloc;
/*-------------------------------------------CONSTRUCTORS-------------------------------------------*/
/*	(1) empty container constructor (default constructor)
 *		Constructs an empty container, with no elements.
 * 	(2) fill constructor
 *		Constructs a container with n elements. Each element is a copy of val.
 *	(3) range constructor
 * 		Constructs a container with as many elements as the range [first,last), with each element 
 * 		constructed from its corresponding element in that range, in the same order.
 * 	(4) copy constructor
 * 		Constructs a container with a copy of each of the elements in x, in the same order.	*/

		explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc) {

		}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) {

		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
						 const allocator_type& alloc = allocator_type()) {

		}

		vector (const vector& x) {

		}
	};
}

#endif
