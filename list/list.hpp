/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 10:48:13 by averheij      #+#    #+#                 */
/*   Updated: 2021/03/09 15:38:43 by dries            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <iterator>
# include <cstddef>
# include <cmath>



#include <iostream>

/*	memory		std::allocator
 *	iterator	bidirectional_iterator_tag //this doesnt look right
 *	cstddef		ptrdiff_t
 *	cmath		__true_type __is_integer*/

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class list { //https://cplusplus.com/reference/list/list/

		public:
			/*	member type				definition notes
			 *	value_type				The first template parameter (T)	
			 *	allocator_type			The second template parameter (Alloc)	
			 *	reference				allocator_type::reference				
			 *	const_reference			allocator_type::const_reference			
			 *	pointer					allocator_type::pointer					
			 *	const_pointer			allocator_type::const_pointer			
			 *	difference_type			a signed integral type, identical to:	
			 *							iterator_traits<iterator>::difference_type	
			 *	size_type				an unsigned integral type that can 		
			 *							represent any non-negative value of 
			 *							difference_type	*/

			typedef	T										value_type;
			typedef	Alloc									allocator_type;
			typedef	value_type&								reference;
			typedef	const value_type&						const_reference;
			typedef	value_type*								pointer;
			typedef	const value_type*						const_pointer;
			typedef	ptrdiff_t								difference_type;
			typedef size_t									size_type;

/*-------------------------------------------NODE CLASS-------------------------------------------*/
		private:
			template<typename value_t>
			class Node {
				public:
					typedef	value_t							value_type;
					typedef	value_type*						pointer;

					Node(void) : data(NULL), next(NULL), prev(NULL) {}
					Node(pointer data_, Node *next_ = NULL, Node* prev_ = NULL) : data(data_), next(next_), prev(prev_) {}

					~Node(void) {}

					Node&		operator=(const Node& rhs) {
						if (this != rhs) {
							this->data = rhs.data;
							this->next = rhs.next;
							this->prev = rhs.prev;
						}
						return *this;
					}

					pointer		data;
					Node		*next;
					Node		*prev;
			};

		public:
			typedef Node<T>									node_type;

/*-------------------------------------------ITERATOR CLASS-------------------------------------------*/
			template<class node_t, class value_t, class reference_t, class pointer_t>
			class ListBiIterator { //https://en.cppreference.com/w/cpp/iterator/iterator
				public:
					node_t	*node;

					typedef std::bidirectional_iterator_tag			iterator_category;
					typedef	value_t									value_type;
					typedef	reference_t								reference;
					typedef	pointer_t								pointer;
					typedef	ptrdiff_t								difference_type;

					ListBiIterator(node_t* n = NULL) : node(n) {}
					ListBiIterator(const ListBiIterator& src) { *this = src; }
					~ListBiIterator(void) {}

					ListBiIterator&		operator=(const ListBiIterator& rhs) {
						node = rhs.node;
						return *this;
					}


					ListBiIterator		operator++(int n) {		//i++
						ListBiIterator	ret(*this);

						(void)n;
						++(*this);
						return ret;
					}

					ListBiIterator		operator--(int n) {		//i--
						ListBiIterator	ret(*this);

						(void)n;
						--(*this);
						return ret;
					}

					ListBiIterator&		operator++() {			//++i
						node = node->next;
						return *this;
					}

					ListBiIterator&		operator--() {			//--i
						node = node->prev;
						return *this;
					}

					ListBiIterator		operator+(const int& rhs) {			//i + x
						ListBiIterator	ret(*this);

						if (rhs > 0)
							for (int i = 0; i < rhs; ++i)
								ret.node = ret.node->next;
						else if (rhs < 0)
							for (int i = 0; i > rhs; --i)
								ret.node = ret.node->next;
						return ret;
					}

					ListBiIterator		operator-(const int& rhs) {			//i - x
						ListBiIterator	ret(*this);

						if (rhs > 0)
							for (int i = 0; i < rhs; ++i)
								ret.node = ret.node->prev;
						else if (rhs < 0)
							for (int i = 0; i > rhs; --i)
								ret.node = ret.node->prev;
						return ret;
					}

					bool					operator==(const ListBiIterator& rhs) const { return node == rhs.node; }
					bool					operator!=(const ListBiIterator& rhs) const { return node != rhs.node; }
					pointer					operator->() const { return node->data; }
					reference 				operator*() const { return *node->data; }

					operator ListBiIterator<node_t, const value_t, const reference, const pointer>() { /* pass butter; */ return node; }

			};

			template<class node_t, class value_t, class reference_t, class pointer_t>
			class ReverseListBiIterator : public ListBiIterator<node_t, value_t, reference_t, pointer_t> { //https://en.cppreference.com/w/cpp/iterator/iterator
				public:
					node_t	*node;

					typedef std::bidirectional_iterator_tag			iterator_category;
					typedef	value_t									value_type;
					typedef	reference_t								reference;
					typedef	pointer_t								pointer;
					typedef	ptrdiff_t								difference_type;

					ReverseListBiIterator(node_t* n = NULL) : node(n) {}
					ReverseListBiIterator(const ReverseListBiIterator& src) { *this = src; }
					~ReverseListBiIterator(void) {}

					ReverseListBiIterator&		operator=(const ReverseListBiIterator& rhs) {
						node = rhs.node;
						return *this;
					}


					ReverseListBiIterator		operator++(int n) {		//i++
						ReverseListBiIterator	ret(*this);

						(void)n;
						++(*this);
						return ret;
					}

					ReverseListBiIterator		operator--(int n) {		//i--
						ReverseListBiIterator	ret(*this);

						(void)n;
						--(*this);
						return ret;
					}

					ReverseListBiIterator&		operator++() {			//++i
						node = node->prev;
						return *this;
					}

					ReverseListBiIterator&		operator--() {			//--i
						node = node->next;
						return *this;
					}

					ReverseListBiIterator		operator+(const int& rhs) {			//i + x
						ReverseListBiIterator	ret(*this);

						if (rhs > 0)
							for (int i = 0; i < rhs; ++i)
								ret.node = ret.node->prev;
						else if (rhs < 0)
							for (int i = 0; i > rhs; --i)
								ret.node = ret.node->prev;
						return ret;
					}

					ReverseListBiIterator		operator-(const int& rhs) {			//i - x
						ReverseListBiIterator	ret(*this);

						if (rhs > 0)
							for (int i = 0; i < rhs; ++i)
								ret.node = ret.node->next;
						else if (rhs < 0)
							for (int i = 0; i > rhs; --i)
								ret.node = ret.node->next;
						return ret;
					}


					bool					operator==(const ReverseListBiIterator& rhs) const { return node == rhs.node; }
					bool					operator!=(const ReverseListBiIterator& rhs) const { return node != rhs.node; }
					pointer					operator->() const { return node->data; }
					reference 				operator*() const { return *node->data; }

					operator ReverseListBiIterator<node_t, const value_type, const reference, const pointer>() { /* pass butter; */ return node; }

			};

		public:
			/*	member type					definition notes
			 *	iterator					a bidirectional iterator to value_type	
			 *	const_iterator				a bidirectional iterator to const value_type	
			 *	reverse_iterator			reverse_iterator<iterator>	
			 *	const_reverse_iterator		reverse_iterator<const_iterator>	
			 *	Node						class used for nodes	*/

			//TODO
			typedef	ListBiIterator<node_type, T, T&, T*>							iterator;
			typedef	ListBiIterator<node_type, const T, const T&, const T*>			const_iterator;
			typedef	ReverseListBiIterator<node_type, T, T&, T*>					reverse_iterator;
			typedef	ReverseListBiIterator<node_type, const T, const T&, const T*>	const_reverse_iterator;

		private:
			size_type					_size;
			Alloc						alloc;
			node_type*					head;
			node_type*					tail;
			node_type*					base;

/*-------------------------------------------CANON-------------------------------------------*/
		public:
			/*	(1) empty container constructor (default constructor)
			 *		Constructs an empty container, with no elements.
			 *	(2) fill constructor
			 *		Constructs a container with n elements. Each element is 
			 *		a copy of val.
			 *	(3) range constructor
			 *		Constructs a container with as many elements as the range 
			 *		[first,last), with each element constructed from its 
			 *		corresponding element in that range, in the same order.
			 *	(4) copy constructor
			 *		Constructs a container with a copy of each of the elements 
			 *		in x, in the same order.
			 *
			 * 		The container keeps an internal copy of alloc, which is 
			 * 		used to allocate storage throughout its lifetime.
			 *		The copy constructor (4) creates a container that keeps and 
			 *		uses a copy of x's allocator.
			 *
			 *		The storage for the elements is allocated using this internal allocator.  */

			explicit list(const allocator_type& alloc = allocator_type())
								: _size(0), alloc(alloc),  head(NULL), tail(NULL), base(new node_type()) {}

			explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
								: _size(0), alloc(alloc), head(NULL), tail(NULL), base(new node_type()) {
				for (size_type i = 0; i != n; i++) {
					push_back(val);
				}
			}

			template<bool B>
			struct enable_if {};

			template<>
			struct enable_if<true> {
				typedef T type;
			};

			template<typename not_an_iterator>
			struct is_iterator {
				static const bool		result = false;
			};

			template<>
			struct is_iterator<std::bidirectional_iterator_tag> {
				static const bool		result = true;
			};

			template <class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename enable_if<is_iterator<typename InputIterator::iterator_category>::result>::type* = NULL)
			  					: _size(0), alloc(alloc), head(NULL), tail(NULL), base(new node_type()) {
				while (first != last) {
					push_back(*first);
					first++;
				}
			}

			list(const list& x) : _size(0), head(NULL), tail(NULL), base(new node_type()) {
				const_iterator		iter;
				const_iterator		end;

				iter = x.begin();
				end = x.end();
				while (!x.empty() && iter != end) {
					push_back(*iter);
					iter++;
				}
			}

			/*	This destroys all container elements, and deallocates all the
			 *	storage capacity allocated by the list container using its allocator.  */

			~list(void) {
				while (!empty())
					pop_back();
				delete base;
			}

			/*	Copies all the elements from x into the container.
			 *	The container preserves its current allocator, which is used to
			 *	allocate additional storage if needed.
			 *	Any elements held in the container before the call are either
			 *	assigned to or destroyed.  */

			list&				operator=(const list& x) {
				const_iterator		iter;
				const_iterator		end;

				while (!empty())
					pop_front();
				delete base;
				base = new node_type();
				iter = x.begin();
				end = x.end();
				while (!x.empty() && iter != end) {
					push_back(*iter);
					iter++;
				}
				return *this;
			}

/*-------------------------------------------ITERATORS-------------------------------------------*/

			/*	Returns an iterator pointing to the first element in the list container.	*/

			iterator				begin() {
				return iterator(head);
			}

			const_iterator			begin() const {
				return const_iterator(head);
			}

			/*	Returns an iterator referring to the past-the-end element in the list container.
			 *	The past-the-end element is the theoretical element that would follow the last 
			 *	element in the list container. It does not point to any element, and thus shall 
			 *	not be dereferenced.
			 *	If the container is empty, this function returns the same as list::begin.	*/

			iterator				end() {
				return iterator(base);
			}

			const_iterator			end() const {	//TODO check that this is expected behaviour i.e. that stl does not just seg fault
				return const_iterator(base);
			}

			/*	Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
			 *	Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			 *	rbegin points to the element right before the one that would be pointed to by member end.	*/

			reverse_iterator		rbegin() {
				return reverse_iterator(tail);
			}

			const_reverse_iterator	rbegin() const {
				return const_reverse_iterator(tail);
			}

			/*	 Returns a reverse iterator pointing to the theoretical element preceding the 
			 *	 first element in the list container (which is considered its reverse end).	*/

			reverse_iterator				rend() {
				return reverse_iterator(base);
			}

			const_reverse_iterator			rend() const {	//TODO check that this is expected behaviour i.e. that stl does not just seg fault
				return const_reverse_iterator(base);
			}

/*-------------------------------------------CAPACITY-------------------------------------------*/


			/*	Returns whether the list container is empty (i.e. whether its size is 0).  */

			bool				empty() const {
				return !_size;
			}

			/*	Returns the number of elements in the list container.  */

			size_type			size() const {
				return _size;
			}

			/* Returns the maximum number of elements that the list container can hold.  */

			size_type			max_size() const {
				return (alloc.max_size() / (24 / sizeof(value_type)));
			}

/*-------------------------------------------ELEMENT ACCESS-------------------------------------------*/

			/*	Returns a reference to the first element in the list container.  */

			reference 			front() {
				return *head->data;
			}
			const_reference 	front() const {
				return *head->data;
			}

			/*	Returns a reference to the last element in the list container.  */

			reference 			back() {
				return *tail->data;
			}
			const_reference 	back() const {
				return *tail->data;
			}

/*-------------------------------------------MODIFIERS-------------------------------------------*/

			/*	In the range version (1), the new contents are elements constructed from each of
			 *	the elements in the range between first and last, in the same order.
			 *	In the fill version (2), the new contents are n elements, each initialized to a
			 *	copy of val.
			 *	Any storage needed for the assigned elements is allocated using the internal allocator.
			 *	Any elements held in the container before the call are destroyed and replaced by
			 *	newly constructed elements (no assignments of elements take place).	*/

			template <class InputIterator>
			void				assign (InputIterator first, InputIterator last) {
				while (!empty())
					pop_front();
				delete base;
				base = new node_type();
				head = NULL;
				tail = NULL;
				while (first != last) {
					push_back(*first);
					first++;
				}
			}

			void				assign (size_type n, const value_type& val) {
				while (!empty())
					pop_front();
				delete base;
				base = new node_type();
				head = NULL;
				tail = NULL;
				for (size_type i = 0; i != n; i++) {
					push_back(val);
				}
			}

			/*	Inserts a new element at the beginning of the list, right before its current first element. 
			 *	The content of val is copied (or moved) to the inserted element.
			 *	This effectively increases the container size by one. */

			void				push_front(const value_type& val) {
				if (head) {
					head->prev = new_node(val, head, base);
					head = head->prev;
					head->prev = base;
					base->next = head;
				} else {
					head = new_node(val, base, base);
					tail = head;
					base->next = head;
					base->prev = tail;
				}
				_size++;
			}

			/*	Removes the first element in the list container, effectively reducing its size by one.
			 *	This destroys the removed element. */

			void				pop_front(void) {
				node_type		*tmp;

				if (head) {
					tmp = head;
					head = head->next;
					if (_size != 1) {
						head->prev = base;
					} else {
						base->prev = NULL;
						tail = NULL;
					}
					base->next = head;
					_size--;
					alloc.destroy(tmp->data);
					alloc.deallocate(tmp->data, 1);
					delete tmp;
				}
			}

			/*	Adds a new element at the end of the list container, after its current last element. 
			 *	The content of val is copied (or moved) to the new element.  
			 *	This effectively increases the container size by one.  */

			void				push_back(const value_type& val) {
				if (tail) {
					tail->next = new_node(val, base, tail);
					tail = tail->next;
					tail->next = base;
					base->prev = tail;
				} else {
					head = new_node(val, base, base);
					tail = head;
					base->next = head;
					base->prev = tail;
				}
				_size++;
			}

			/*	Removes the last element in the list container, effectively reducing the container size by one.
			 *	This destroys the removed element.  */

			void				pop_back() {
				node_type		*tmp;

				if (tail) {
					tmp = tail;
					tail = tail->prev;
					if (_size != 1)
						tail->next = base;
					else {
						base->next = NULL;
						head = NULL;
					}
					base->prev = tail;
					_size--;
					alloc.destroy(tmp->data);
					alloc.deallocate(tmp->data, 1);
					delete tmp;
				}
			}

			/*	The container is extended by inserting new elements before the element at the
			 *	specified position.
			 *	This effectively increases the list size by the amount of elements inserted.	*/

			iterator			insert (iterator position, const value_type& val) {
				node_type		*ptr;

				ptr = base;
				while (position.node != ptr->next)
					ptr = ptr->next;
				return iterator(insert_new_node(ptr, val));
			}

			void				insert (iterator position, size_type n, const value_type& val) {
				node_type		*ptr;

				ptr = base;
				while (position.node != ptr->next)
					ptr = ptr->next;
				for (size_type i = 0; i != n; ++i) {
					insert_new_node(ptr, val);
					ptr = ptr->next;
				}
			}

			template <class InputIterator>
			void				insert (iterator position, InputIterator first, InputIterator last) {
				node_type		*ptr;

				ptr = base;
				while (position.node != ptr->next)
					ptr = ptr->next;
				for (; first != last; ++first) {
					if (first.node == NULL)
						break;
					insert_new_node(ptr, *first);
					ptr = ptr->next;
				}
			}

			/*	Removes from the list container either a single element (position) or a range
			 *	of elements ([first,last)).  
			 *	This effectively reduces the container size by the number of elements removed,
			 *	which are destroyed.	*/

			iterator			erase (iterator position) {
				node_type		*ptr;

				//ptr = base;
				//while (position.node != ptr)
					//ptr = ptr->next;
				//ptr = iton(position);
				ptr = position.node;
				++position;
				delete_node(ptr);
				//std::cout << "position:" << std::endl;
				//debug_node(position.node);
				return position;
			}

			iterator			erase (iterator first, iterator last) {
				node_type		*del;

				while (first != last) {
					del = first.node;
					++first;
					delete_node(del);
				}
				return last;
			}

			/*	Exchanges the content of the container by the content of x, which is another 
			 *	list of the same type. Sizes may differ.
			 *	All iterators, references and pointers remain valid for the swapped objects.	*/


			void				swap (list& x) {
				node_type*		swp;
				size_type		swp_size;

				swp_size = x._size;
				x._size = _size;
				_size = swp_size;
				swp = x.head;
				x.head = head;
				head = swp;
				swp = x.tail;
				x.tail = tail;
				tail = swp;
				swp = x.base;
				x.base = base;
				base = swp;
			}

			/*	Resizes the container so that it contains n elements.
			 *	If n is smaller than the current container size, the content is reduced to its
			 *	first n elements, removing those beyond (and destroying them).
			 *	If n is greater than the current container size, the content is expanded by
			 *	inserting at the end as many elements as needed to reach a size of n. If val is
			 *	specified, the new elements are initialized as copies of val, otherwise, they
			 *	are value-initialized.	*/

			void				resize (size_type n, value_type val = value_type()) {
				if (n == _size)
					return;
				while (n > _size)
					push_back(val);
				while (n < _size)
					pop_back();
			}

			void				clear (void) {
				while (_size)
					pop_back();
			}

/*-------------------------------------------OPERATIONS-------------------------------------------*/

			/*	Transfers elements from x into the container, inserting them at position.
			 *	This effectively inserts those elements into the container and removes them from x, 
			 *	altering the sizes of both containers. The operation does not involve the construction 
			 *	or destruction of any element. They are transferred, no matter whether x is an lvalue 
			 *	or an rvalue, or whether the value_type supports move-construction or not.
			 *	The first version (1) transfers all the elements of x into the container.
			 *	The second version (2) transfers only the element pointed by i from x into the container.
			 *	The third version (3) transfers the range [first,last) from x into the container.	*/

			void				splice (iterator position, list& x) {
				node_type*	local_head;
				node_type*	local_tail;

				if (x._size == 0)
					return;
				//local_tail = iton(position);
				local_tail = position.node;
				if ((local_tail == base || local_tail == NULL) && head == NULL) {	//uninitialized
					local_head = base;
					local_tail = base;
				} else
					local_head = local_tail->prev;
				local_head->next = x.head;
				x.head->prev = local_head;
				x.head = NULL;
				x.base->next = NULL;
				local_tail->prev = x.tail;
				x.tail->next = local_tail;
				x.tail = NULL;
				x.base->prev = NULL;
				if (_size == 0) {	//local_head = base, local_tail = base
					head = local_head->next;
					tail = local_tail->prev;
				}
				if (local_tail == head)
					head = local_head->next;
				if (local_head == tail)
					tail = local_tail->prev;
				_size += x._size;
				x._size = 0;
			}

			void				splice (iterator position, list& x, iterator i) {
				node_type*	local_head;
				node_type*	local_tail;
				node_type*	splice_me;

				if (x._size == 0)
					return;
				//splice_me = x.base;
				//while (i.node != splice_me)
					//splice_me = splice_me->next;
				splice_me = i.node;
				//local_tail = iton(position);
				local_tail = position.node;
				if ((local_tail == base || local_tail == NULL) && head == NULL) {	//uninitialized
					local_head = base;
					local_tail = base;
				} else
					local_head = local_tail->prev;
				//remove from x
				splice_me->prev->next = splice_me->next;
				splice_me->next->prev = splice_me->prev;
				--x._size;
				if (splice_me == x.head && x._size > 0)
					x.head = splice_me->next;
				else if (x._size == 0) {
					x.head = NULL;
					x.base->next = NULL;
				}
				if (splice_me == x.tail && x._size > 0)
					x.tail = splice_me->prev;
				else if (x._size == 0) {
					x.tail = NULL;
					x.base->prev = NULL;
				}
				//add to this
				local_head->next = splice_me;
				splice_me->prev = local_head;
				local_tail->prev = splice_me;
				splice_me->next = local_tail;
				if (_size == 0) {	//local_head = base, local_tail = base
					head = local_head->next;
					tail = local_tail->prev;
				}
				if (local_tail == head)
					head = local_head->next;
				if (local_head == tail)
					tail = local_tail->prev;
				++_size;
			}

			//void				splice (iterator position, list& x, iterator first, iterator last) {
				//for (; first != last; ++first)
					//splice(position, x, first);
			//}

			void				splice (iterator position, list& x, iterator first, iterator last) {
				node_type*	local_head;
				node_type*	local_tail;
				node_type*	splice_head;
				node_type*	splice_tail;
				int			i;

				splice_head = x.base;
				i = 1;
				while (first.node != splice_head) {
					splice_head = splice_head->next;
					--i;
				}
				splice_tail = x.base;
				while (last.node != splice_tail->next) {
					splice_tail = splice_tail->next;
					++i;
				}
				local_tail = base;
				while (position.node != local_tail)
					local_tail = local_tail->next;
				if ((local_tail == base || local_tail == NULL) && head == NULL) {	//uninitialized
					local_head = base;
					local_tail = base;
				} else
					local_head = local_tail->prev;
				//remove from x
				splice_head->prev->next = splice_tail->next;
				splice_tail->next->prev = splice_head->prev;
				x._size -= i;
				if (splice_head == x.head && x._size > 0)
					x.head = splice_tail->next;
				else if (x._size == 0) {
					x.head = NULL;
					x.base->next = NULL;
				}
				if (splice_tail == x.tail && x._size > 0)
					x.tail = splice_head->prev;
				else if (x._size == 0) {
					x.tail = NULL;
					x.base->prev = NULL;
				}
				//add to this
				local_head->next = splice_head;
				splice_head->prev = local_head;
				local_tail->prev = splice_tail;
				splice_tail->next = local_tail;
				if (_size == 0) {	//local_head = base, local_tail = base
					head = local_head->next;
					tail = local_tail->prev;
				}
				if (local_tail == head)
					head = local_head->next;
				if (local_head == tail)
					tail = local_tail->prev;
				_size += i;
				//std::cout << "x" << std::endl;
				//x.debug();
				//std::cout << "this" << std::endl;
				//debug();
			}

			/*	Removes from the container all the elements that compare equal to val. 
			 *	This calls the destructor of these objects and reduces the container 
			 *	size by the number of elements removed.	*/

			void				remove (const value_type& val) {
				node_type*		ptr;
				//node_type*		next;
				//node_type*		prev;

				//debug();
				if (_size == 0)
					return;
				for (iterator i = begin(); i != end();)
					if (*i == val) {
						ptr = base;
						while (i.node != ptr)
							ptr = ptr->next;
						//delete_node(i.node);
						++i;
						//debug_node("del", ptr);
						//prev = ptr->prev;
						//next = ptr->next;
						//debug_node("dpr", prev);
						//debug_node("dnx", next);
						delete_node(ptr);
						//debug_node("dpr", prev);
						//debug_node("dnx", next);
					} else
						++i;
			}

			/*	Removes from the container all the elements for which Predicate pred 
			 *	returns true. This calls the destructor of these objects and reduces 
			 *	the container size by the number of elements removed.  
			 *	The function calls pred(*i) for each element (where i is an iterator 
			 *	to that element). Any of the elements in the list for which this returns 
			 *	true, are removed from the container.	*/

			template <class Predicate>
			void				remove_if (Predicate pred) {
				node_type*		ptr;
				//node_type*		next;
				//node_type*		prev;

				if (_size == 0)
					return;
				for (iterator i = begin(); i != end();) {
					if (pred(*i)) {
						ptr = base;
						while (i.node != ptr)
							ptr = ptr->next;
						//delete_node(i.node);
						++i;
						//debug_node("del", ptr);
						//prev = ptr->prev;
						//next = ptr->next;
						//debug_node("dpr", prev);
						//debug_node("dnx", next);
						delete_node(ptr);
						//debug_node("dpr", prev);
						//debug_node("dnx", next);
					} else
						++i;
				}
			}

			/*	The version with no parameters (1), removes all but the first element 
			 *	from every consecutive group of equal elements in the container.
			 *	Notice that an element is only removed from the list container if it 
			 *	compares equal to the element immediately preceding it.
			 *	The second version (2), takes as argument a specific comparison function 
			 *	that determine the "uniqueness" of an element. The function will call 
			 *	binary_pred(*i,*(i-1)) for all pairs of elements 
			 *	(where i is an iterator to an element, starting from the second) and 
			 *	remove i from the list if the predicate returns true.
			 *	The elements removed are destroyed.	*/

			void				unique() {
				node_type*		ptr;

				if (_size <= 1)
					return;
				for (iterator i = ++begin(); i != end();) {
					if (*i == *(i - 1)) {
						ptr = base;
						while (i.node != ptr)
							ptr = ptr->next;
						++i;
						delete_node(ptr);
					} else
						++i;
				}
			}

			template <class BinaryPredicate>
			void				unique (BinaryPredicate binary_pred) {
				node_type*		ptr;

				if (_size <= 1)
					return;
				for (iterator i = ++begin(); i != end();)
					if (binary_pred(*i, *(i - 1))) {
						ptr = base;
						while (i.node != ptr)
							ptr = ptr->next;
						++i;
						delete_node(ptr);
					} else
						++i;
			}

			/*	Merges x into the list by transferring all of its elements into the container 
			 *	(both containers shall already be ordered).
			 *	X becomes empty, and inserts them into their ordered position within container 
			 *	(size += x old size). The elements are !transferred! (no construction or destruction).
			 *	The resulting order of equivalent elements is stable (i.e., equivalent elements 
			 *	preserve relative order the call, and existing elements precede those equivalent inserted from x).
			 *	The function does nothing if (&x == this).	*/

			void				merge (list& x) {
				node_type	*lptr;
				node_type	*xptr;
				node_type	*tmp;

				lptr = head;
				xptr = x.head;
				//debug();
				//x.debug();
				while (x._size) {
					if (lptr != base) {
						//debug_node("xptr", xptr);
						//debug_node("lptr", lptr);
						if (*(xptr->data) < *(lptr->data)) {
							tmp = xptr->next;
							lptr->prev->next = xptr;
							if (lptr == head)
								head = xptr;
							xptr->prev = lptr->prev;
							xptr->next = lptr;
							lptr->prev = xptr;
							_size++;
							x._size--;
							xptr = tmp;
						} else
							lptr = lptr->next;
					} else {
						tmp = xptr->next;
						lptr->prev->next = xptr;
						tail = xptr;
						xptr->prev = lptr->prev;
						xptr->next = lptr;
						lptr->prev = xptr;
						_size++;
						x._size--;
						xptr = tmp;
					}
				}
				x.head = NULL;
				x.tail = NULL;
				x.base->next = NULL;
				x.base->prev = NULL;
			}

			template <class Compare>
			void				merge (list& x, Compare comp) {
				node_type	*lptr;
				node_type	*xptr;
				node_type	*tmp;

				lptr = head;
				xptr = x.head;
				//debug();
				//x.debug();
				while (x._size) {
					if (lptr != base) {
						//debug_node("xptr", xptr);
						//debug_node("lptr", lptr);
						if (comp(*(xptr->data), *(lptr->data))) {
							tmp = xptr->next;
							lptr->prev->next = xptr;
							if (lptr == head)
								head = xptr;
							xptr->prev = lptr->prev;
							xptr->next = lptr;
							lptr->prev = xptr;
							_size++;
							x._size--;
							xptr = tmp;
						} else
							lptr = lptr->next;
					} else {
						tmp = xptr->next;
						lptr->prev->next = xptr;
						tail = xptr;
						xptr->prev = lptr->prev;
						xptr->next = lptr;
						lptr->prev = xptr;
						_size++;
						x._size--;
						xptr = tmp;
					}
				}
				x.head = NULL;
				x.tail = NULL;
				x.base->next = NULL;
				x.base->prev = NULL;
			}

			/*	Sorts the elements in the list, altering their position within the container.
			 *	The sorting is performed by applying an algorithm that uses either operator< 
			 *	(in version (1)) or comp (in version (2)) to compare elements. This comparison 
			 *	shall produce a strict weak ordering of the elements (i.e., a consistent transitive 
			 *	comparison, without considering its reflexiveness).
			 *	The resulting order of equivalent elements is stable: i.e., equivalent elements 
			 *	preserve the relative order they had before the call.
			 *	The entire operation does not involve the construction, destruction or copy of any 
			 *	element object. Elements are moved within the container.	*/

			void				sort() {
				size_type	unsorted;
				size_type	highest_sort;
				node_type	*ptr;
				node_type	*tmp;

				unsorted = _size;
				//debug();
				while (unsorted > 1) {
					highest_sort = 0;
					ptr = head->next;
					for (size_type i = 1; i != unsorted; ++i) {
						//debug_node("prev", ptr->prev);
						//debug_node("ptr", ptr);
						if (*(ptr->data) < *(ptr->prev->data)) {
							tmp = ptr->next;
							//swap(ptr->prev, ptr);
							swap_adj(ptr);
							highest_sort = i;
							ptr = tmp;
						} else
							ptr = ptr->next;
						//debug();
					}
					unsorted = highest_sort;
				}
			}

			template <class Compare>
			void				sort (Compare comp) {
				size_type	unsorted;
				size_type	highest_sort;
				node_type	*ptr;
				node_type	*tmp;

				unsorted = _size;
				//debug();
				while (unsorted > 1) {
					highest_sort = 0;
					ptr = head->next;
					for (size_type i = 1; i != unsorted; ++i) {
						//debug_node("prev", ptr->prev);
						//debug_node("ptr", ptr);
						//if (comp(*(ptr->prev->data), *(ptr->data))) {
						if (comp(*(ptr->data), *(ptr->prev->data))) {
							tmp = ptr->next;
							//swap(ptr->prev, ptr);
							swap_adj(ptr);
							highest_sort = i;
							ptr = tmp;
						} else
							ptr = ptr->next;
						//debug();
					}
					unsorted = highest_sort;
				}
			}

/*-------------------------------------------OTHER-------------------------------------------*/
		private:
			/*	print out a single notes member variables	*/

			static void			debug_node(std::string name, node_type *n) {
				std::cout << name;
				if (!n) {
					std::cout << "\tNULL" << std::endl;
					return;
				}
				std::cout << "\tprev: " << n->prev;
				std::cout << "\ti: " << n;
				std::cout << "\tnext: " << n->next;
				std::cout << "\tdata: " << n->data;
				if (n->data)
					std::cout << "\tval: " << *n->data;
				std::cout << std::endl;
			}

			/*	print out the whole list using debug_node
			 *	incl base|head|tail	*/

			void			debug (void) {
				node_type		*ptr;
				int				n;

				std::cout << "\tdebug" << std::endl;
				std::cout << "base: " << base;
				std::cout << "\tbnxt: " << base->next;
				std::cout << "\thead: " << head;
				std::cout << "\tsize: " << _size;
				std::cout << std::endl;
				n = 0;
				for (node_type *i = head; i != base; i = i->next) {
					if (!i) {
						std::cout << "NULL" << std::endl;
						break;
					}
					std::cout << "prev: " << i->prev;
					std::cout << "\tnode: " << i;
					std::cout << "\tnext: " << i->next;
					std::cout << "\tno: " << n;
					std::cout << "\tdata: " << i->data;
					if (i->data)
						std::cout << "\tval: " << *i->data;
					n++;
					std::cout << std::endl;
					if (i->next == i) {
						std::cout << "infinite loop!" << std::endl;
						break;
					}
					if (n > _size) {
						std::cout << "infinite loop!" << std::endl;
						break;
					}
				}
				std::cout << "bprv: " << base->prev;
				std::cout << "\ttail: " << tail;
				std::cout << std::endl;
			}

		private:
			/*	creates a new node, with given arguements (val, next, prev)
			 *	returns: node_type* new node	*/

			node_type*				new_node(const value_type& val, node_type *next = NULL, node_type *prev = NULL) {
				value_type	*tmp;

				tmp = alloc.allocate(1);
				alloc.construct(tmp, val);
				return new node_type(tmp, next, prev);
			}

			/*	inserts a new node following the node passed as ptr, with given value
			 *	returns: node_type* to node inserted	*/

			node_type*				insert_new_node(node_type* ptr, const value_type& val) {
				node_type*		node;

				_size++;
				if (ptr->next) {		//If no next, ptr is base & list is uninitialized
					node = new_node(val, ptr->next, ptr);
					ptr->next->prev = node;
				}
				else {
					node = new_node(val, base, ptr);
					tail = node;
					base->prev = node;
				}
				ptr->next = node;
				if (ptr == base) {
					head = node;
					base->next = head;
				}
				if (ptr == tail || _size == 1)
					tail = node;
				if (ptr == base || _size == 1)
					head = node;
				return ptr->next;
			}

			void					delete_node(node_type *del) {
				//node_type *prev = del->prev;
				//node_type *next = del->next;
				//std::cout << "\tdel:" << std::endl;
				//debug_node(del);
				//std::cout << "\tprev:" << std::endl;
				//debug_node(prev);
				//std::cout << "\tnetx:" <<  std::endl;
				//debug_node(next);

				if (del == head) {
					head = del->next;
					base->next = head;
				}
				if (del == tail) {
					tail = del->prev;
					base->prev = tail;
				}
				del->next->prev = del->prev;
				del->prev->next = del->next;
				_size--;
				alloc.destroy(del->data);
				alloc.deallocate(del->data, 1);
				delete del;

				//std::cout << "\tprev:" << std::endl;
				//debug_node(prev);
				//std::cout << "\tnext:" << std::endl;
				//debug_node(next);
			}

			/*	swaps the node pointed at by ptr with the preceeding node	*/

			void					swap_adj(node_type *node) {
				node_type	*prior;

				prior = node->prev;
				//debug_node("PREV", prior);
				//debug_node("PTR", node);
				prior->next = node->next;
				node->prev = prior->prev;
				prior->next->prev = prior;
				node->prev->next = node;
				node->next = prior;
				prior->prev = node;
				if (prior == head) {
					head = node;
					base->next = head;
				}
				if (node == tail) {
					tail = prior;
					base->prev = tail;
				}
				//debug_node("PREV", prior);
				//debug_node("PTR", node);
			}

			//void					swap(node_type *n1, node_type *n2) {
				//node_type	swp;			//HAHAHAH nice try friend, need to change ->next->prev and ->prev->next
				//node_type	swp2;
				//node_type	swp3;

				//debug_node("n1o", n1);
				//debug_node("n2o", n2);
				//n1->next->prev = n2;	//Fix adj links			//Broken as hell
				//n1->prev->next = n2;
				//n2->next->prev = n1;
				//n2->prev->next = n1;
				//swp.next = n1->next;	//Swap next and prev
				//swp.prev = n1->prev;
				//n1->next = n2->next;
				//n1->prev = n2->prev;
				//n2->next = swp.next;
				//n2->prev = swp.prev;
				//debug_node("n1n", n1);
				//debug_node("n2n", n2);
				//debug_node("n1N", n1->next);
				//debug_node("n1P", n1->prev);
				//debug_node("n2N", n2->next);
				//debug_node("n2P", n2->prev);
				//if (n1 == head) {
					//n2 = head;
					//base->next = head;
				//} else if (n2 == head) {
					//n1 = head;
					//base->next = head;
				//}
				//if (n1 == tail) {
					//n2 = tail;
					//base->prev = tail;
				//} else if (n2 == tail) {
					//n1 = tail;
					//base->prev = tail;
				//}
			//}
	};

}

#endif
