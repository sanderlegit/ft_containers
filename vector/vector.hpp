/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   vector.hpp                                        e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/10 16:43:21 by dries             *8*   8   *8*          */
/*   Updated: 2021/03/10 17:52:08 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class vector { //https://cplusplus.com/reference/vector/vector/
		public:
/*	member type				definition			
 *					notes
 *	value_type				The first template parameter (T)	
 *	allocator_type			The second template parameter (Alloc)	allocator<value_type>
 *	reference				allocator_type::reference				value_type&
 *	const_reference			allocator_type::const_reference			const value_type&
 *	pointer					allocator_type::pointer					value_type*
 *	const_pointer			allocator_type::const_pointer			const value_type*
 *	iterator				a random access iterator to value_type	convertible to const_iterator
 *	const_iterator			a random access iterator to const 
 *							value_type	
 *	reverse_iterator		reverse_iterator<iterator>	
 *	const_reverse_iterator	reverse_iterator<const_iterator>	
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
			class VectorRandIterator {
			//typedef		iterator;
			//typedef		const_iterator;
			//typedef		reverse_iterator;
			//typedef		const_reverse_iterator;

	private:
		size_type		_size;
		size_type		_capacity;
		pointer			data;

	};
}

#endif
