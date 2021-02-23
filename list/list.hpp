/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 10:48:13 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/23 18:01:34 by averheij      ########   odam.nl         */
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
			/*member type				definition notes
			 *value_type				The first template parameter (T)	
			 *allocator_type			The second template parameter (Alloc)	
			 *reference					allocator_type::reference				
			 *const_reference			allocator_type::const_reference			
			 *pointer					allocator_type::pointer					
			 *const_pointer				allocator_type::const_pointer			
			 *difference_type			a signed integral type, identical to:	
			 *							iterator_traits<iterator>::difference_type	
			 *size_type					an unsigned integral type that can 		
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
			class Node {
				public:
					typedef	T								value_type;
					typedef	value_type*						pointer;

					Node(void) : next(NULL), prev(NULL) {}
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
			typedef Node									node_type;

/*-------------------------------------------ITERATOR CLASS-------------------------------------------*/
			class const_list_bi_iterator { //https://en.cppreference.com/w/cpp/iterator/iterator
				public:
					typedef std::bidirectional_iterator_tag			iterator_category;
					typedef Node									node_type;
					typedef	T										value_type;
					typedef	const value_type&						const_reference;
					typedef	const value_type*						const_pointer;
					typedef	ptrdiff_t								difference_type;

					const_list_bi_iterator(node_type* n = NULL) : node(n) {}
					const_list_bi_iterator(const const_list_bi_iterator& src) { *this = src; }
					~const_list_bi_iterator(void) {}

					const_list_bi_iterator&		operator=(const const_list_bi_iterator& rhs) {
						node = rhs.node;
						return *this;
					}

					const_list_bi_iterator		operator++(int n) {		//i++
						const_list_bi_iterator	ret(*this);
						++(*this);
						return ret;
					}

					const_list_bi_iterator		operator--(int n) {		//i--
						const_list_bi_iterator	ret(*this);
						--(*this);
						return ret;
					}

					const_list_bi_iterator&		operator++() { node = node->next; return *this; } //++i
					const_list_bi_iterator&		operator--() { node = node->prev; return *this; } //--i

					bool					operator==(const const_list_bi_iterator& rhs) const { return node == rhs.node; }
					bool					operator!=(const const_list_bi_iterator& rhs) const { return node != rhs.node; }
					pointer					operator->() const { return node->data; }
					reference 				operator*() const { return *node->data; }

					node_type	*node = NULL;
			};

			class list_bi_iterator { //https://en.cppreference.com/w/cpp/iterator/iterator
				public:
					typedef std::bidirectional_iterator_tag			iterator_category;
					typedef Node									node_type;
					typedef	T										value_type;
					typedef	value_type&								reference;
					typedef	value_type*								pointer;
					typedef	ptrdiff_t								difference_type;

					list_bi_iterator(node_type* n = NULL) : node(n) {}
					list_bi_iterator(const list_bi_iterator& src) { *this = src; }
					~list_bi_iterator(void) {}

					list_bi_iterator&		operator=(const list_bi_iterator& rhs) {
						node = rhs.node;
						return *this;
					}


					list_bi_iterator		operator++(int n) {		//i++
						list_bi_iterator	ret(*this);
						++(*this);
						return ret;
					}

					list_bi_iterator		operator--(int n) {		//i--
						list_bi_iterator	ret(*this);
						--(*this);
						return ret;
					}

					list_bi_iterator&		operator++() { node = node->next; return *this; } //++i
					list_bi_iterator&		operator--() { node = node->prev; return *this; } //--i

					bool					operator==(const list_bi_iterator& rhs) const { return node == rhs.node; }
					bool					operator!=(const list_bi_iterator& rhs) const { return node != rhs.node; }
					pointer					operator->() const { return node->data; }
					reference 				operator*() const { return *node->data; }

					operator const_list_bi_iterator() { /* pass butter; */ return node; }		//TODO what is my purpose

					node_type	*node = NULL;
			};

			class reverse_const_list_bi_iterator { //https://en.cppreference.com/w/cpp/iterator/iterator
				public:
					typedef std::bidirectional_iterator_tag			iterator_category;
					typedef Node									node_type;
					typedef	T										value_type;
					typedef	const value_type&						const_reference;
					typedef	const value_type*						const_pointer;
					typedef	ptrdiff_t								difference_type;

					reverse_const_list_bi_iterator(node_type* n = NULL) : node(n) {}
					reverse_const_list_bi_iterator(const const_list_bi_iterator& src) { *this = src; }
					~reverse_const_list_bi_iterator(void) {}

					reverse_const_list_bi_iterator&		operator=(const reverse_const_list_bi_iterator& rhs) {
						node = rhs.node;
						return *this;
					}

					reverse_const_list_bi_iterator		operator++(int n) {		//i++
						reverse_const_list_bi_iterator	ret(*this);
						++(*this);
						return ret;
					}

					reverse_const_list_bi_iterator		operator--(int n) {		//i--
						reverse_const_list_bi_iterator	ret(*this);
						--(*this);
						return ret;
					}

					reverse_const_list_bi_iterator&		operator++() { node = node->prev; return *this; } //++i
					reverse_const_list_bi_iterator&		operator--() { node = node->next; return *this; } //--i

					bool					operator==(const reverse_const_list_bi_iterator& rhs) const { return node == rhs.node; }
					bool					operator!=(const reverse_const_list_bi_iterator& rhs) const { return node != rhs.node; }
					pointer					operator->() const { return node->data; }
					reference 				operator*() const { return *node->data; }

					node_type	*node = NULL;
			};

			class reverse_list_bi_iterator { //https://en.cppreference.com/w/cpp/iterator/iterator
				public:
					typedef std::bidirectional_iterator_tag			iterator_category;
					typedef Node									node_type;
					typedef	T										value_type;
					typedef	value_type&								reference;
					typedef	value_type*								pointer;
					typedef	ptrdiff_t								difference_type;

					reverse_list_bi_iterator(node_type* n = NULL) : node(n) {}
					reverse_list_bi_iterator(const reverse_list_bi_iterator& src) { *this = src; }
					~reverse_list_bi_iterator(void) {}

					reverse_list_bi_iterator&		operator=(const reverse_list_bi_iterator& rhs) {
						node = rhs.node;
						return *this;
					}


					reverse_list_bi_iterator		operator++(int n) {		//i++
						reverse_list_bi_iterator	ret(*this);
						++(*this);
						return ret;
					}

					reverse_list_bi_iterator		operator--(int n) {		//i--
						reverse_list_bi_iterator	ret(*this);
						--(*this);
						return ret;
					}

					reverse_list_bi_iterator&		operator++() { node = node->prev; return *this; } //++i
					reverse_list_bi_iterator&		operator--() { node = node->next; return *this; } //--i

					bool					operator==(const reverse_list_bi_iterator& rhs) const { return node == rhs.node; }
					bool					operator!=(const reverse_list_bi_iterator& rhs) const { return node != rhs.node; }
					pointer					operator->() const { return node->data; }
					reference 				operator*() const { return *node->data; }

					operator reverse_const_list_bi_iterator() { /* pass butter; */ return node; }		//TODO what is my purpose

					node_type	*node = NULL;
			};

		public:
			/*member type				definition notes
			 *iterator					a bidirectional iterator to value_type	
			 *const_iterator			a bidirectional iterator to const value_type	
			 *reverse_iterator			reverse_iterator<iterator>	
			 *const_reverse_iterator	reverse_iterator<const_iterator>	
			 *Node						class used for nodes	*/

			//TODO
			typedef	list_bi_iterator				iterator;
			typedef	const_list_bi_iterator			const_iterator;
			typedef	reverse_list_bi_iterator		reverse_iterator;
			typedef	reverse_const_list_bi_iterator	const_reverse_iterator;

		private:
			size_type					_size;
			Alloc						alloc;
			node_type*					head;
			node_type*					tail;

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
								: _size(0), alloc(alloc),  head(NULL), tail(NULL) {}

			explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
								: _size(0), alloc(alloc), head(NULL), tail(NULL) {
				for (size_type i = 0; i != n; i++) {
					push_back(val);
				}
			}

		private:
			template<typename Integer>
			void	list_paradox_constructor(Integer n, Integer val, std::__true_type) {
				for (size_type i = 0; i != n; i++) {
					push_back(val);
				}
			}

			template<typename InputIterator>
				void	list_fill(InputIterator first, InputIterator last) {
					//std::cout << first.node << " " << last.node << std::endl;
					//std::cout << (first.node != last.node) << std::endl;
					//std::cout << (first != last) << std::endl;

					while (first != last) {
						//std::cout << *first << std::endl;
						push_back(*first);
						first++;
						//std::cout << first.node << " " << last.node << std::endl;
						//std::cout << (first.node != last.node) << std::endl;
						//std::cout << (first != last) << std::endl;
					}
					//std::cout << "head: " << *head->data << std::endl;
					//std::cout << "tail: " << *tail->data << std::endl;
				}

			template<typename InputIterator>
			void	list_paradox_constructor(InputIterator first, InputIterator last, std::__false_type) {
				list_fill(first, last);
			}

		public:
			template <class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			  					: alloc(alloc), _size(0), head(NULL), tail(NULL) {
				list_paradox_constructor(first, last, typename std::__is_integer<InputIterator>::__type());
			}

			//list(const list& x) : alloc(allocator_type()), _size(0), head(NULL), tail(NULL) {
			list(const list& x) : _size(0), head(NULL), tail(NULL) {
				//std::cout << "copy " << x.size() <<std::endl;
				//std::cout <<  x.front() << " " << x.back() << " " << std::endl;
				list_fill(x.begin(), x.end());
			}

			/*	This destroys all container elements, and deallocates all the
			 *	storage capacity allocated by the list container using its allocator.  */

			~list(void) {
				while (!empty()) {
					//std::cout << "empty:" << empty();
					//std::cout << " size:" << size();
					//if (!empty())
						//std::cout << " tail:" << back();
					//std::cout << std::endl;
					pop_back();

				}
			}

			/*	Copies all the elements from x into the container.
			 *	The container preserves its current allocator, which is used to
			 *	allocate additional storage if needed.
			 *	Any elements held in the container before the call are either
			 *	assigned to or destroyed.  */

			list&				operator=(const list& x) {
				node_type		*ptr;

				while (!empty())
					pop_front();
				ptr = x.head;
				while (ptr) {
					push_back(*ptr->data);
					ptr = ptr->next;
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
				if (tail)
					return iterator(tail->next);
				else
					return iterator(NULL);
			}

			const_iterator			end() const {	//TODO check that this is desired behaviour, not just seg fault
				if (tail)
					return const_iterator(tail->next);
				else
					return const_iterator(NULL);
			}

			/* Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
			 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			 * rbegin points to the element right before the one that would be pointed to by member end.	*/

			reverse_iterator		rbegin() {
				return reverse_iterator(tail);
			}

			const_reverse_iterator	rbegin() const {
				return const_reverse_iterator(tail);
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

			/*	Inserts a new element at the beginning of the list, right before its current first element. 
			 *	The content of val is copied (or moved) to the inserted element.
			 *	This effectively increases the container size by one. */

			void				push_front(const value_type& val) {
				node_type		*l;

				if (head) {
					l = new_node(val, head, NULL);
					head->prev = l;
					head = l;
				} else {
					head = new_node(val, NULL, NULL);
					tail = head;
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
					if (head)
						head->prev = NULL;
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
					tail->next = new_node(val, NULL, tail);
					tail = tail->next;
				} else {
					head = new_node(val, NULL, NULL);
					tail = head;
				}
				_size++;
			}

			/* Removes the last element in the list container, effectively reducing the container size by one.
			 * This destroys the removed element.  */

			void				pop_back() {
				node_type		*tmp;

				if (tail) {
					tmp = tail;
					tail = tail->prev;
					if (tail)
						tail->next = NULL;
					_size--;
					alloc.destroy(tmp->data);
					alloc.deallocate(tmp->data, 1);
					delete tmp;
				}
			}

		private:

			node_type*				new_node(const value_type& val, node_type *next = NULL, node_type *prev = NULL) {
				//node		*l;

				//l = alloc.allocate(sizeof(node));
				//alloc.construct(l, val, next, prev);
				//return l;
				value_type	*tmp;

				tmp = alloc.allocate(1);
				alloc.construct(tmp, val);
				return new Node(tmp, next, prev);
				//return new node(val, next, prev);
			}
	};

}

#endif
