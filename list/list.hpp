/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 10:48:13 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/17 14:30:20 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <iterator>
# include <cstddef>

/*	memory		std::allocator
 *	iterator	bidirectional_iterator_tag
 *	cstddef		ptrdiff_t
*/

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class list {

		public:
			/*member type				definition notes
			 *value_type				The first template parameter (T)	
			 *
			 *allocator_type			The second template parameter (Alloc)	
			 *
			 *reference					allocator_type::reference				
			 *
			 *const_reference			allocator_type::const_reference			
			 *
			 *pointer					allocator_type::pointer					
			 *
			 *const_pointer				allocator_type::const_pointer			
			 *
			 *iterator					a bidirectional iterator to value_type	
			 *
			 *const_iterator			a bidirectional iterator to const value_type	
			 *
			 *reverse_iterator			reverse_iterator<iterator>	
			 *
			 *const_reverse_iterator	reverse_iterator<const_iterator>	
			 *
			 *difference_type			a signed integral type, identical to:	
			 *							iterator_traits<iterator>::difference_type	
			 *
			 *size_type					an unsigned integral type that can 		
			 *							represent any non-negative value of 
			 *							difference_type	
			*/

			typedef	T										value_type;
			typedef	Alloc									allocator_type;
			typedef	value_type&								reference;
			typedef	const value_type&						const_reference;
			typedef	value_type*								pointer;
			typedef	const value_type*						const_pointer;
			//TODO
			//typedef	std::bidirectional_iterator_tag<>		iterator;
			//typedef	std::bidirectional_iterator_tag<const>	const_iterator;
			//typedef	std::reverse_iterator<iterator>			reverse_iterator;
			//typedef	std::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef	ptrdiff_t								difference_type;
			typedef size_t									size_type;

		private:

			class link {
				public:
					link(void) : next(NULL), prev(NULL) {}
					link(const T& data_, link *next_ = NULL, link* prev_ = NULL) : data(data_), next(next_), prev(prev_) {}

					~link(void) {}

					link&		operator=(const link& rhs) {
						if (this != rhs) {
							this->data = rhs.data;
							this->next = rhs.next;
							this->prev = rhs.prev;
						}
						return *this;
					}

					T			data;
					link		*next;
					link		*prev;
			};

		private:

			size_type					_size;
			Alloc						alloc;
			link*						head;
			link*						tail;

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
			 *		The storage for the elements is allocated using this internal allocator.
			 *
			 *	https://cplusplus.com/reference/list/list/list/
			*/

			explicit list (const allocator_type& alloc = allocator_type())
								: _size(0), alloc(alloc),  head(NULL), tail(NULL) {}

			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
								: _size(n), alloc(alloc), head(NULL), tail(NULL) {
				for (size_type i = 0; i != _size; i++) {
					push_back(val);
				}
			}

			template <class InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			  					: alloc(alloc) {
				while (first != last) {
					push_back(*first);
					first++;
				}
			}

			list (const list& x) {
				(void)x;
				//TODO
			}

			/*	This destroys all container elements, and deallocates all the
			 *	storage capacity allocated by the list container using its allocator.
			 *
			 *	https://cplusplus.com/reference/list/list/~list/
			*/

			~list(void) {
				//TODO
				//destruct stuff
				//delete all links
			}

			/*	Copies all the elements from x into the container.
			 *	The container preserves its current allocator, which is used to
			 *	allocate additional storage if needed.
			 *	Any elements held in the container before the call are either
			 *	assigned to or destroyed.
			 *
			 *	https://cplusplus.com/reference/list/list/operator=/
			*/

			list&				operator=(const list& x) {
				(void)x;
				//TODO
			}

			/*		ELEMENT ACCESS
			*/

			/*	Returns a reference to the first element in the list container.
			*/

			reference 			front() {
				return head->data;
			}
			const_reference 	front() const {
				return head->data;
			}

			/*	Returns a reference to the last element in the list container.
			*/

			reference 			back() {
				return tail->data;
			}
			const_reference 	back() const {
				return tail->data;
			}

			/*		MODIFIERS
			*/

			/*	Adds a new element at the end of the list container, after its current last element. 
			 *	The content of val is copied (or moved) to the new element.
			 *
			 *	This effectively increases the container size by one.
			*/

			void				push_back(const value_type& val) {
				if (tail) {
					tail->next = new_link(val, NULL, tail);
					tail = tail->next;
				} else {
					head = new_link(val, NULL, NULL);
					tail = head;
				}
			}

		private:

			link*				new_link(const value_type& val, link *next = NULL, link *prev = NULL) {
				//link		*l;

				//l = alloc.allocate(sizeof(link));
				//alloc.construct(l, val, next, prev);
				//return l;
				return new link(val, next, prev);
			}
	};

}

#endif
