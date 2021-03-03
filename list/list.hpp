/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 10:48:13 by averheij      #+#    #+#                 */
/*   Updated: 2021/03/03 14:53:06 by dries            ###   ########.fr       */
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
						++(*this);
						return ret;
					}

					ListBiIterator		operator--(int n) {		//i--
						ListBiIterator	ret(*this);
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
						++(*this);
						return ret;
					}

					ReverseListBiIterator		operator--(int n) {		//i--
						ReverseListBiIterator	ret(*this);
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
			  					: alloc(alloc), _size(0), head(NULL), tail(NULL), base(new node_type()) {
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

			iterator		insert (iterator position, const value_type& val) {
				node_type		*ptr;
				node_type		*tmp;

				ptr = base;
				while (position.node != ptr->next)
					ptr = ptr->next;
				return iterator(insert_new_node(ptr, val));
			}

			void			insert (iterator position, size_type n, const value_type& val) {
				node_type		*ptr;
				node_type		*tmp;

				ptr = base;
				while (position.node != ptr->next)
					ptr = ptr->next;
				for (size_type i = 0; i != n; ++i) {
					insert_new_node(ptr, val);
					ptr = ptr->next;
				}
			}

			template <class InputIterator>
			void			insert (iterator position, InputIterator first, InputIterator last) {
				node_type		*ptr;
				node_type		*tmp;

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

			iterator erase (iterator position) {
				node_type		*ptr;

				ptr = base;
				while (position.node != ptr)
					ptr = ptr->next;
				++position;
				delete_node(ptr);
				//std::cout << "position:" << std::endl;
				//debug_node(position.node);
				return position;
			}

			iterator erase (iterator first, iterator last) {
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


			void			swap (list& x) {
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

		private:
			/*	print out a single notes member variables	*/

			static void			debug_node(node_type *n) {
					std::cout << "prev: " << n->prev;
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

				std::cout << "\tdebug" << std::endl;
				std::cout << "base: " << base;
				std::cout << "\tbase->next: " << base->next;
				std::cout << "\thead: " << head;
				std::cout << std::endl;
				for (node_type *i = head; i != base; i = i->next) {
					debug_node(i);
					if (i->next == i) {
						std::cout << "infinite loop!" << std::endl;
						break;
					}
				}
				std::cout << "base->prev: " << base->prev;
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
	};

}

#endif
