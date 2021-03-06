/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   vector.hpp                                        e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/10 16:43:21 by dries             *8*   8   *8*          */
/*   Updated: 2021/03/31 15:59:26 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iterator>
#include <memory>
#include <iostream>
#include <stdexcept>

/*	memory		allocator
 *	iterator	iterator_tag	
 *	iostream	debug prints
 *	stdexcept	out_of_range	*/

namespace ft {

/*-------------------------------------------ITERATORS-------------------------------------------*/

	template<class value_t, class reference_t, class pointer_t>
	class VectorRandIterator { //https://en.cppreference.com/w/cpp/iterator/iterator
		public:
			typedef std::random_access_iterator_tag			iterator_category;
			typedef	value_t									value_type;
			typedef	reference_t								reference;
			typedef	pointer_t								pointer;
			typedef	ptrdiff_t								difference_type;
		private:
			pointer		_data;
		public:

			VectorRandIterator(pointer d = NULL) : _data(d) {}
			VectorRandIterator(const VectorRandIterator& src) { *this = src; }
			~VectorRandIterator(void) {}

			VectorRandIterator&		operator=(const VectorRandIterator& rhs) {
				_data = rhs._data;
				return *this;
			}

			VectorRandIterator		operator++(int n) {		//i++
				VectorRandIterator	ret(*this);

				(void)n;
				++(*this);
				return ret;
			}

			VectorRandIterator		operator--(int n) {		//i--
				VectorRandIterator	ret(*this);

				(void)n;
				--(*this);
				return ret;
			}

			VectorRandIterator&		operator++() {			//++i
				_data++;
				return *this;
			}

			VectorRandIterator&		operator--() {			//--i
				_data--;
				return *this;
			}

			VectorRandIterator&		operator+=(const int& rhs) {			//i += n
				_data += rhs;
				return *this;
			}

			VectorRandIterator&		operator-=(const int& rhs) {			//i -= n
				_data -= rhs;
				return *this;
			}

			VectorRandIterator		operator+(const int& rhs) {			//i + x
				VectorRandIterator	ret(*this);

				ret._data += rhs;
				return ret;
			}

			VectorRandIterator		operator-(const int& rhs) {			//i - x
				VectorRandIterator	ret(*this);

				ret._data -= rhs;
				return ret;
			}

			difference_type		operator-(const VectorRandIterator& rhs) {			//a - b
				difference_type		ret;

				ret = 0;
				if (_data < rhs._data)
					while ((_data - ret) != rhs._data)
						--ret;
				else
					while ((_data - ret) != rhs._data)
						++ret;
				return ret;
			}

			bool					operator==(const VectorRandIterator& rhs) const { return _data == rhs._data; }
			bool					operator!=(const VectorRandIterator& rhs) const { return _data != rhs._data; }
			pointer					operator->() const { return _data; }
			reference 				operator*() const { return *_data; }
			bool					operator<(const VectorRandIterator& rhs) const { return (_data < rhs._data); }
			bool					operator>(const VectorRandIterator& rhs) const { return (_data > rhs._data); }
			bool					operator<=(const VectorRandIterator& rhs) const { return (_data <= rhs._data); }
			bool					operator>=(const VectorRandIterator& rhs) const { return (_data >= rhs._data); }
			reference				operator[](const int& rhs) const { return *(_data + rhs); }

			operator VectorRandIterator<const value_t, const reference, const pointer>() { return _data; }
	};

	template<class value_t, class reference_t, class pointer_t>
	class ReverseVectorRandIterator { //https://en.cppreference.com/w/cpp/iterator/iterator
		public:
			typedef std::random_access_iterator_tag			iterator_category;
			typedef	value_t									value_type;
			typedef	reference_t								reference;
			typedef	pointer_t								pointer;
			typedef	ptrdiff_t								difference_type;
		private:
			pointer		_data;
		public:

			ReverseVectorRandIterator(pointer d = NULL) : _data(d) {}
			ReverseVectorRandIterator(const ReverseVectorRandIterator& src) { *this = src; }
			~ReverseVectorRandIterator(void) {}

			ReverseVectorRandIterator&		operator=(const ReverseVectorRandIterator& rhs) {
				_data = rhs._data;
				return *this;
			}

			ReverseVectorRandIterator		operator++(int n) {		//i++
				ReverseVectorRandIterator	ret(*this);

				(void)n;
				++(*this);
				return ret;
			}

			ReverseVectorRandIterator		operator--(int n) {		//i--
				ReverseVectorRandIterator	ret(*this);

				(void)n;
				--(*this);
				return ret;
			}

			ReverseVectorRandIterator&		operator++() {			//++i
				_data--;
				return *this;
			}

			ReverseVectorRandIterator&		operator--() {			//--i
				_data++;
				return *this;
			}

			ReverseVectorRandIterator&		operator+=(const int& rhs) {			//i += n
				_data -= rhs;
				return *this;
			}

			ReverseVectorRandIterator&		operator-=(const int& rhs) {			//i -= n
				_data += rhs;
				return *this;
			}

			ReverseVectorRandIterator		operator+(const int& rhs) {			//i + x
				ReverseVectorRandIterator	ret(*this);

				ret._data -= rhs;
				return ret;
			}

			ReverseVectorRandIterator		operator-(const int& rhs) {			//i - x
				ReverseVectorRandIterator	ret(*this);

				ret._data += rhs;
				return ret;
			}

			difference_type		operator-(const ReverseVectorRandIterator& rhs) {			//a - b
				difference_type		ret;

				ret = 0;
				if (_data < rhs._data)
					while ((_data - ret) != rhs._data)
						--ret;
				else
					while ((_data - ret) != rhs._data)
						++ret;
				return (ret * -1);
			}

			bool					operator==(const ReverseVectorRandIterator& rhs) const { return _data == rhs._data; }
			bool					operator!=(const ReverseVectorRandIterator& rhs) const { return _data != rhs._data; }
			pointer					operator->() const { return _data; }
			reference 				operator*() const { return *_data; }
			bool					operator<(const ReverseVectorRandIterator& rhs) const { return (_data > rhs._data); }
			bool					operator>(const ReverseVectorRandIterator& rhs) const { return (_data < rhs._data); }
			bool					operator<=(const ReverseVectorRandIterator& rhs) const { return (_data >= rhs._data); }
			bool					operator>=(const ReverseVectorRandIterator& rhs) const { return (_data <= rhs._data); }
			reference				operator[](const int& rhs) const { return *(_data - rhs); }

			operator ReverseVectorRandIterator<const value_t, const reference, const pointer>() { return _data; }
	};

/*-------------------------------------------VECTOR-------------------------------------------*/

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

/*	iterator				a random access iterator to value_type	convertible to const_iterator
 *	const_iterator			a random access iterator to const 
 *							value_type	
 *	reverse_iterator		reverse_iterator<iterator>	
 *	const_reverse_iterator	reverse_iterator<const_iterator>	*/
			typedef	T										value_type;
			typedef	Alloc									allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef	value_type*								pointer;
			typedef	const value_type*						const_pointer;
			typedef	ptrdiff_t								difference_type;
			typedef size_t									size_type;
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

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
						 const allocator_type& alloc = allocator_type())  : _size(0), _capacity(0), _data(NULL), _alloc(alloc) {
			resize(last - first);
			for (iterator i = first; i != last; i++)
				_data[i - first] = *i;
		}

		vector (const vector& x) : _size(x._size), _capacity(x._capacity), _data(NULL), _alloc(x._alloc) {
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i != _size; i++)
				_alloc.construct(_data + i, x[i]);
		}

/*	Destroys the container object.	*/

		~vector() {
			dellocate(_data, _size);
			_data = NULL;
			_size = 0;
			_capacity = 0;
		}

/*-------------------------------------------OPERATORS-------------------------------------------*/

/*	Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
 * 	Copies all the elements from x into the container.
 *	The container preserves its current allocator, which is used to allocate storage in case of reallocation.
 *	Any elements held in the container before the call are either assigned to or destroyed.	*/

 		vector&					operator= (const vector& x) {
			reserve(x._size);
			for (size_t i = 0; i != _size; i++)
				_alloc.destroy(_data + i);
			for (size_t i = 0; i != x._size; i++)
				_alloc.construct(_data + i, x[i]);
			_size = x._size;
			return *this;
		}

/*-------------------------------------------ITERATORS ACCESS-------------------------------------------*/

/*	Returns an iterator pointing to the first element in the vector.
 *	Notice that, unlike member vector::front, which returns a reference to the first element, this function returns a random access iterator pointing to it.
 *	If the container is empty, the returned iterator value shall not be dereferenced.	*/

	iterator					begin() {
		return iterator(_data);
	}

	const_iterator				begin() const {
		return iterator(_data);
	}

	iterator					end() {
		return iterator(_data + _size);
	}

	const_iterator				end() const {
		return iterator(_data + _size);
	}

	reverse_iterator					rbegin() {
		return reverse_iterator(_data + _size - 1);
	}

	const_reverse_iterator				rbegin() const {
		return reverse_iterator(_data + _size - 1);
	}

	reverse_iterator					rend() {
		return reverse_iterator(_data - 1);
	}

	const_reverse_iterator				rend() const {
		return reverse_iterator(_data - 1);
	}


/*-------------------------------------------CAPACITY-------------------------------------------*/

/*	Returns the number of elements in the vector.
 *	This is the number of actual objects held in the vector, which is not necessarily equal to 
 *	its storage capacity.	*/

		size_type				size () const {
			return _size;
		}

/*	Returns the maximum number of elements that the vector can hold.
 *	This is the maximum potential size the container can reach due to known system or library 
 *	implementation limitations, but the container is by no means guaranteed to be able to reach 
 *	that size: it can still fail to allocate storage at any point before that size is reached.	*/


		size_type				max_size () const {
			return (size_type(-1) / sizeof(int));
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
			pointer		tmp;
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
				//for (size_type i = n; i != new_capacity; i++)
					//_alloc.construct(tmp + i);
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
				//for (size_type i = n; i != new_capacity; i++)
					//_alloc.construct(tmp + i);
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
					//_alloc.construct(_data + i);
				}
				_size = n;
			}
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


		size_type				capacity () const {
			return _capacity;
		}

/*	Returns whether the vector is empty (i.e. whether its size is 0).
 *	This function does not modify the container in any way. To clear the content of a vector,
 *	see vector::clear.	*/

		bool					empty () const {
			return !_size;
		}

/*	Requests that the vector capacity be at least enough to contain n elements.
 *	If n is greater than the current vector capacity, the function causes the container to 
 *	reallocate its storage increasing its capacity to n (or greater).
 *	In all other cases, the function call does not cause a reallocation and the vector capacity 
 *	is not affected.
 *	This function has no effect on the vector size and cannot alter its elements.	*/

		void					reserve (size_type n) {
			pointer	tmp;

			if (n <= _capacity)
				return;
			tmp = _alloc.allocate(n);
			for (size_type i = 0; i != _size; i++)
				_alloc.construct(tmp + i, _data[i]);
			//for (size_type i = n; i != n; i++)
				//_alloc.construct(tmp + i);
			dellocate(_data, _capacity);
			_data = tmp;
			_capacity = n;
		}


/*-------------------------------------------ELEMENT ACCESS-------------------------------------------*/

/*	Returns a reference to the element at position n in the vector container.
 *	Portable programs should never call this function with an argument n that is out of range, since 
 *	this causes undefined behavior.	*/

		reference				operator[] (size_type n) {
			return _data[n];
		}

		const_reference			operator[] (size_type n) const {
			return _data[n];
		}

/*	Returns a reference to the element at position n in the vector.
 *	The function automatically checks whether n is within the bounds of valid elements in the vector, 
 *	throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).	*/

		reference				at (size_type n) {
			if (n >= _size)
				throw std::out_of_range("Vector::at(n) : n is out of range");
			return _data[n];
		}

		const_reference			at (size_type n) const {
			if (n >= _size)
				throw std::out_of_range("Vector::at(n) : n is out of range");
			return _data[n];
		}

/*	Returns a reference to the first element in the vector.
 *	Unlike member vector::begin, which returns an iterator to this same element, this function returns
 *	a direct reference.
 *	Calling this function on an empty container causes undefined behavior.	*/

		reference				front () {
			return _data[0];
		}

		const_reference			front () const {
			return _data[0];
		}

/*	Returns a reference to the last element in the vector.
 *	Unlike member vector::end, which returns an iterator just past this element, this function returns 
 *	a direct reference.
 *	Calling this function on an empty container causes undefined behavior.	*/

		reference				back () {
			return _data[_size - 1];
		}

		const_reference			back () const {
			return _data[_size - 1];
		}

/*-------------------------------------------MODIFIERS-------------------------------------------*/

/*	Assigns new contents to the vector, replacing its current contents, and modifying its size 
 *	accordingly.
 *	In the range version (1), the new contents are elements constructed from each of the elements 
 *	in the range between first and last, in the same order.
 *	In the fill version (2), the new contents are n elements, each initialized to a copy of val.  
 *	If a reallocation happens,the storage needed is allocated using the internal allocator.
 *	Any elements held in the container before the call are destroyed and replaced by newly 
 *	constructed elements (no assignments of elements take place).
 *	This causes an automatic reallocation of the allocated storage space if -and only if- the new 
 *	vector size surpasses the current vector capacity.	*/

		template <class InputIterator>
		void					assign (InputIterator first, InputIterator last) {
			resize(0);
			for (iterator i = first; i != last; i++)
				push_back(*i);
		}

		void					assign (size_type n, const value_type& val) {
			resize(0);
			resize(n, val);
		}

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

		void					pop_back () {
			resize(_size - 1);
		}

/*	The vector is extended by inserting new elements before the element at the specified position, 
 *	effectively increasing the container size by the number of elements inserted.
 *	This causes an automatic reallocation of the allocated storage space if -and only if- the new
 *	vector size surpasses the current vector capacity.
 *	Because vectors use an array as their underlying storage, inserting elements in positions other
 *	than the vector end causes the container to relocate all the elements that were after position
 *	to their new positions. This is generally an inefficient operation compared to the one performed
 *	for the same operation by other kinds of sequence containers (such as list or forward_list).	*/


		iterator				insert (iterator position, const value_type& val) {
			size_type		idx;

			idx = position - begin();
			//std::cout << "idx: " << idx << std::endl;
			//debug();
			resize(_size + 1);
			//debug();
			for (reverse_iterator i = rbegin(); i != rend() - idx - 1; i++) {
				//std::cout << rend() - i << std::endl;
				//std::cout << "swapping i: " << *i << " \ti+1: " << *(i + 1) << std::endl;
				//debug();
				*i = *(i + 1);
			}
			//debug();
			_data[idx] = val;
			return (begin() + idx);
		}

		void					insert (iterator position, size_type n, const value_type& val) {
			size_type		idx;

			idx = position - begin();
			//std::cout << "idx: " << idx << std::endl;
			//debug();
			resize(_size + n);
			//debug();
			for (reverse_iterator i = rbegin(); i != rend() - idx - n; i++) {
				//std::cout << rend() - i << std::endl;
				//std::cout << "swapping i: " << *i << " \ti+1: " << *(i + 1) << std::endl;
				//debug();
				*i = *(i + n);
			}
			//debug();
			for (size_type i = 0; i < n; i++)
				_data[idx + i] = val;
		}

		template <class InputIterator>
		void					insert (iterator position, InputIterator first, InputIterator last) {
			size_type	idx;
			size_type	n;
			iterator	vi;

			n = last - first;
			idx = position - begin();
			//std::cout << "idx: " << idx << std::endl;
			//debug();
			resize(_size + n);
			//debug();
			for (reverse_iterator i = rbegin(); i != rend() - idx - n; i++) {
				//std::cout << rend() - i << std::endl;
				//std::cout << "swapping i: " << *i << " \ti+1: " << *(i + n) << std::endl;
				//debug();
				*i = *(i + n);
			}
			//debug();
			vi = first;
			for (size_type i = 0; i < n; i++) {
				_data[idx + i] = *vi;
				vi++;
			}
		}

/*	Removes from the vector either a single element (position) or a range of elements ([first,last)).
 *	This effectively reduces the container size by the number of elements removed, which are destroyed.
 *	Because vectors use an array as their underlying storage, erasing elements in positions other than 
 *	the vector end causes the container to relocate all the elements after the segment erased to their 
 *	new positions. This is generally an inefficient operation compared to the one performed for the 
 *	same operation by other kinds of sequence containers (such as list or forward_list).	*/

		iterator	erase (iterator position) {
			int			idx;

			idx = begin() - position;
			for (iterator i = position; i != end() - 1; i++) {
				*i = *(i + 1);
			}
			resize(_size - 1);
			return (begin() + idx);
		}

		iterator	erase (iterator first, iterator last) {
			difference_type	diff;
			int				idx;

			diff = last - first;
			idx = begin() - first;
			for (iterator i = first; i != end() - diff; i++) {
				*i = *(i + diff);
			}
			resize(_size - diff);
			return (begin() + idx);
		}

/*	Exchanges the content of the container by the content of x, which is another vector object 
 *	of the same type. Sizes may differ.
 *	After the call to this member function, the elements in this container are those which were 
 *	in x before the call, and the elements of x are those which were in this. All iterators, 
 *	references and pointers remain valid for the swapped objects.	*/

		void					swap (vector& x) {
			pointer		dswp;
			size_type	sswp;

			dswp = _data;
			_data = x._data;
			x._data = dswp;
			sswp = _size;
			_size = x._size;
			x._size = sswp;
			sswp = _capacity;
			_capacity = x._capacity;
			x._capacity = sswp;
		}

/*	Removes all elements from the vector (which are destroyed), leaving the container with a size 
 *	of 0.
 *	A reallocation is not guaranteed to happen, and the vector capacity is not guaranteed to change 
 *	due to calling this function. A typical alternative that forces a reallocation is to use swap:
 *		vector<T>().swap(x);   // clear x reallocating	*/

		void					clear() {
			for (size_type i = 0; i != _size; i++)
				_alloc.destroy(_data + i);
			_size = 0;
		}
/*-------------------------------------------NON-STL FUNCTIONS-------------------------------------------*/

	public:
		void					debug () {
			std::cout << "size: " << _size << std::endl;
			std::cout << "capacity: " << _capacity << std::endl;
			for (size_t i = 0; i != _size; i++) {
				std::cout << "data[" << i << "] = " << _data[i] << std::endl;
			}
		}


	private:
		pointer					allocate (const size_type& size) {
			pointer	tmp;

			tmp = _alloc.allocate(size);
			for (size_type i = 0; i != size; i++)
				_alloc.construct(tmp + i);
			return tmp;
		}

		void					dellocate (pointer ptr, const size_type& size) {
			for (size_type i = 0; i != size; i++)
				_alloc.destroy(ptr + i);
			_alloc.deallocate(ptr, 2);
		}
	};

/*-------------------------------------------NON-MEMBER OVERLOADS-------------------------------------------*/

/*	Performs the appropriate comparison operation between the vector containers lhs and rhs.
 *	The equality comparison (operator==) is performed by first comparing sizes, and if they match, the elements 
 *	are compared sequentially using operator==, stopping at the first mismatch (as if using algorithm equal).
 *	The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare, which compares 
 *	the elements sequentially using operator< in a reciprocal manner (i.e., checking both a<b and b<a) and 
 *	stopping at the first occurrence.
 *	The other operations also use the operators == and < internally to compare the elements,
 *	behaving as if the following equivalent operations were performed:
 *	operation	equivalent operation
 *	a!=b		!(a==b)
 *	a>b			b<a
 *	a<=b		!(b<a)
 *	a>=b		!(a<b)	*/

	template <class T, class Alloc>
	bool					operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename vector<T>::size_type		ir;
		typename vector<T>::size_type		il;

		if (lhs.size() == rhs.size()) {
			ir = 0;
			il = 0;
			while (il != lhs.size()) {
				if (!(lhs.at(il) == rhs.at(il)))
					return false;
				++ir;
				++il;
			}
		} else
			return false;
		return true;
	}

	template <class T, class Alloc>
	bool					operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool					operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename vector<T>::size_type		i;

		i = 0;
		while (i != lhs.size() && i != rhs.size()) {
			if (lhs.at(i) < rhs.at(i))
				return true;
			else if (rhs.at(i) < lhs.at(i))
				return false;
			++i;
		}
		if (lhs.size() < rhs.size())
			return true;
		else if (lhs.size() > rhs.size())
			return false;
		return false;
	}

	template <class T, class Alloc>
	bool 					operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool 					operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool					operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}

/*	The contents of container x are exchanged with those of y. Both container objects must be of the same
 *	type (same template parameters), although sizes may differ.
 *	After the call to this member function, the elements in x are those which were in y before the call,
 *	and the elements of y are those which were in x. All iterators, references and pointers remain valid
 *	for the swapped objects.	*/

	template <class T, class Alloc>
	void					swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

/*	iter = iter + n	*/

	template <class T>
	VectorRandIterator<T, T&, T*>		operator+(const int& lhs, const VectorRandIterator<T, T&, T*>& rhs) {
		VectorRandIterator<T, T&, T*>	ret(rhs);

		for (int i = 0; i < lhs; ++i)
			++ret;
		return ret;
	}

	template <class T>
	ReverseVectorRandIterator<T, T&, T*>		operator+(const int& lhs, const ReverseVectorRandIterator<T, T&, T*>& rhs) {
		ReverseVectorRandIterator<T, T&, T*>	ret(rhs);

		for (int i = 0; i < lhs; ++i)
			++ret;
		return ret;
	}

}

#endif
