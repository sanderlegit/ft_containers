/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   vector.hpp                                        e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/10 16:43:21 by dries             *8*   8   *8*          */
/*   Updated: 2021/03/15 18:04:29 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iterator>
#include <memory>
#include <iostream>

/*	memory		allocator
 *	iterator	iterator_tag	
 *	iostream	debug prints	*/

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
	public:
/*	(1) empty container constructor (default constructor)
 *		Constructs an empty container, with no elements.
 * 	(2) fill constructor
 *		Constructs a container with n elements. Each element is a copy of val.
 *	(3) range constructor
 * 		Constructs a container with as many elements as the range [first,last), with each element 
 * 		constructed from its corresponding element in that range, in the same order.
 * 	(4) copy constructor
 * 		Constructs a container with a copy of each of the elements in x, in the same order.	*/

		explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _data(NULL), _alloc(alloc) {}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _data(NULL), _alloc(alloc) {
			resize(n, val);
		}

		//template <class InputIterator>
		//vector (InputIterator first, InputIterator last,
						 //const allocator_type& alloc = allocator_type()) {

		//}

		//vector (const vector& x) {

		//}
/*-------------------------------------------CAPACITY-------------------------------------------*/

/*	Returns the number of elements in the vector.
 *	This is the number of actual objects held in the vector, which is not necessarily equal to 
 *	its storage capacity.	*/

		size_type				size() const {
			return _size;
		}

/*	Returns the size of the storage space currently allocated for the vector, expressed in terms 
 *	of elements.
 *	This capacity is not necessarily equal to the vector size. It can be equal or greater, with 
 *	the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
 *	Notice that this capacity does not suppose a limit on the size of the vector. When this 
 *	capacity is exhausted and more is needed, it is automatically expanded by the container 
 *	(reallocating it storage space). The theoretical limit on the size of a vector is given by 
 *	member max_size.
 *	The capacity of a vector can be explicitly altered by calling member vector::reserve.	*/


		size_type				capacity() const {
			return _capacity;
		}

/*	Returns whether the vector is empty (i.e. whether its size is 0).
 *	This function does not modify the container in any way. To clear the content of a vector,
 *	see vector::clear.	*/

		bool					empty() const {
			return !_size;
		}

/*	Resizes the container so that it contains n elements.  
 *	If n is smaller than the current container size, the content is reduced to its first n 
 *	elements, removing those beyond (and destroying them).
 *	If n is greater than the current container size, the content is expanded by inserting at 
 *	the end as many elements as needed to reach a size of n. If val is specified, the new elements 
 *	are initialized as copies of val, otherwise, they are value-initialized.
 *	If n is also greater than the current container capacity, an automatic reallocation of the 
 *	allocated storage space takes place.
 *	Notice that this function changes the actual content of the container by inserting or erasing 
 *	elements from it.	*/

		void					resize (size_type n, value_type val = value_type()) {
			value_type	*tmp;
			size_type	new_capacity;

			if (n == _size) {
				return;
			}
			if (_capacity == 0) {
				new_capacity = 2;
				while (new_capacity * 2 < n * 2)
					new_capacity *= 2;
				tmp = _alloc.allocate(new_capacity);
				for (size_type i = 0; i != n; i++)
					_alloc.construct(tmp + i, val);
				for (size_type i = n; i != new_capacity; i++)
					_alloc.construct(tmp + i);
				_data = tmp;
				_size = n;
				_capacity = new_capacity;
			}
			if (n > _capacity) {
				new_capacity = 2;
				while (new_capacity * 2 < n * 2)
					new_capacity *= 2;
				tmp = _alloc.allocate(new_capacity);
				for (size_type i = 0; i != _size; i++)
					_alloc.construct(tmp + i, _data[i]);
				for (size_type i = _size; i != n; i++)
					_alloc.construct(tmp + i, val);
				for (size_type i = n; i != new_capacity; i++)
					_alloc.construct(tmp + i);
				dellocate(_data, _capacity);
				_data = tmp;
				_size = n;
				_capacity = new_capacity;
			} else if (n > _size) {
				for (size_type i = _size; i != n; i++)
					_data[i] = val;
				_size = n;
			} else if (n < _size) {
				for (size_type i = n; i != _size; i++) {
					_alloc.destroy(_data + i);
					_alloc.construct(_data + i);
				}
				_size = n;
			}
		}

/*-------------------------------------------ELEMENT ACCESS-------------------------------------------*/

/*	Returns a reference to the first element in the vector.
 *	Unlike member vector::begin, which returns an iterator to this same element, this function returns
 *	a direct reference.
 *	Calling this function on an empty container causes undefined behavior.	*/

		reference				front() {
			return _data[0];
		}

		const_reference			front() const {
			return _data[0];
		}

/*	Returns a reference to the last element in the vector.
 *	Unlike member vector::end, which returns an iterator just past this element, this function returns 
 *	a direct reference.
 *	Calling this function on an empty container causes undefined behavior.	*/

		reference				back() {
			return _data[_size - 1];
		}

		const_reference			back() const {
			return _data[_size - 1];
		}

/*-------------------------------------------MODIFIERS-------------------------------------------*/

/*	Adds a new element at the end of the vector, after its current last element. The content of val 
 *	is copied (or moved) to the new element.
 *	This effectively increases the container size by one, which causes an automatic reallocation of 
 *	the allocated storage space if -and only if- the new vector size surpasses
 *	the current vector capacity.	*/

		void					push_back (const value_type& val) {
			resize(_size + 1, val);
		}
/*	Removes the last element in the vector, effectively reducing the container size by one.
 *	This destroys the removed element.	*/

		void					pop_back() {
			resize(_size - 1);
		}

	public:
		void					debug() {
			std::cout << "size: " << _size << std::endl;
			std::cout << "capacity: " << _capacity << std::endl;
			for (size_t i = 0; i != _size; i++) {
				std::cout << "data[" << i << "] = " << _data[i] << std::endl;
			}
		}

	private:
		value_type*				allocate(const size_type& size) {
			value_type	*tmp;

			tmp = _alloc.allocate(size);
			for (size_type i = 0; i != size; i++)
				_alloc.construct(tmp + i);
			return tmp;
		}

		void					dellocate(pointer ptr, const size_type& size) {
			for (size_type i = 0; i != size; i++)
				_alloc.destroy(ptr + i);
			_alloc.deallocate(ptr, 2);
		}
	};

/*-------------------------------------------NON-MEMBER OVERLOADS-------------------------------------------*/

}

#endif
