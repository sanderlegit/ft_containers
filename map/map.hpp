/* ************************************************************************** */
/*                                                                            */
/*                                                       ..eeeee..            */
/*   map.hpp                                           e8'   8   '8e          */
/*                                                    d8     8     8b         */
/*   By: dries <sanderlegit@gmail.com>                8!   .dWb.   !8         */
/*                                                    Y8 .e* 8 *e. 8P         */
/*   Created: 2021/03/31 17:27:17 by dries             *8*   8   *8*          */
/*   Updated: 2021/04/08 18:17:02 by dries               **ee8ee**            */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iterator>
#include <memory>
#include <iostream>
//#include <stdexcept>

/*	memory		allocator
 *	iterator	iterator_tag	
 *	iostream	debug prints
 *	stdexcept	out_of_range	*/

namespace ft {

/*-------------------------------------------ITERATORS-------------------------------------------*/
	template<class node_t, class value_t>
	class MapBiIterator {
		public:
			node_t	*node;

			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef	value_t									value_type;
			typedef	value_t&								reference;
			typedef	value_t*								pointer;
			typedef	ptrdiff_t								difference_type;

			MapBiIterator(node_t* n = NULL) : node(n) {}
			MapBiIterator(const MapBiIterator& src) { *this = src; }
			~MapBiIterator(void) {}

			MapBiIterator&		operator=(const MapBiIterator& rhs) {
				node = rhs.node;
				return *this;
			}


			MapBiIterator		operator++(int n) {		//i++
				MapBiIterator	ret(*this);

				(void)n;
				++(*this);
				return ret;
			}

			MapBiIterator		operator--(int n) {		//i--
				MapBiIterator	ret(*this);

				(void)n;
				--(*this);
				return ret;
			}

			MapBiIterator&		operator++() {			//++i
				node = node->next();
				return *this;
			}

			MapBiIterator&		operator--() {			//--i
				node = node->prev();
				return *this;
			}

			MapBiIterator		operator+(const int& rhs) {			//i + x
				MapBiIterator	ret(*this);

				if (rhs > 0)
					for (int i = 0; i < rhs; ++i)
						++(*this);
				else if (rhs < 0)
					for (int i = 0; i > rhs; --i)
						--(*this);
				return ret;
			}

			MapBiIterator		operator-(const int& rhs) {			//i - x
				MapBiIterator	ret(*this);

				if (rhs > 0)
					for (int i = 0; i < rhs; ++i)
						--(*this);
				else if (rhs < 0)
					for (int i = 0; i > rhs; --i)
						++(*this);
				return ret;
			}

			bool					operator==(const MapBiIterator& rhs) const { return node == rhs.node; }
			bool					operator!=(const MapBiIterator& rhs) const { return node != rhs.node; }
			pointer					operator->() const { return &(node->data); }
			reference 				operator*() const { return node->data; }

			/* operator ConstMapBiIterator<node_t, const value_t>() { return node; } */
	};
/*-------------------------------------------MAP-------------------------------------------*/

template < class Key,											 	// map::key_type
		   class T,									   			// map::mapped_type
		   class Compare = std::less<Key>,					 		// map::key_compare
		   class Alloc = std::allocator<std::pair<const Key,T> >	// map::allocator_type
		   >
	class map {//https://cplusplus.com/reference/map/map/
/*-------------------------------------------NODE CLASS-------------------------------------------*/
		private:
			template<class key_t, class map_t>
			class Node {
				public:
					typedef	std::pair<const key_t, map_t>	pair;

					Node(void) : data(), left(NULL), right(NULL), parent(NULL) {}
					Node(key_t key_, map_t map_, Node *left_ = NULL, Node *right_ = NULL, Node* prev_ = NULL)
							: data(pair(key_, map_)), left(left_), right(right_), parent(prev_) {}
					Node(pair data_, Node *left_ = NULL, Node *right_ = NULL, Node* prev_ = NULL)
							: data(pair(data_)), left(left_), right(right_), parent(prev_) {}
					~Node(void) {}

					Node&		operator=(const Node& rhs) {
						if (this != rhs) {
							this->data = rhs.data;
							this->left = rhs.left;
							this->right = rhs.right;
							this->prev = rhs.prev;
						}
						return *this;
					}

					Node		*next(void) {
						Node	*ptr;

						ptr = this;
						if (ptr->right) {
							ptr = ptr->right;
							while (ptr->left)
								ptr = ptr->left;
						} else {
							while (ptr->parent && ptr->parent->right == ptr)
								ptr = ptr->parent;
							ptr = ptr->parent;
						}
						return ptr;
					}

					Node		*prev(void) {
						Node	*ptr;

						ptr = this;
						if (ptr->left) {
							ptr = ptr->left;
							while (ptr->right)
								ptr = ptr->right;
						} else {
							while (ptr->parent && ptr->parent->left == ptr)
								ptr = ptr->parent;
							ptr = ptr->parent;
						}
						return ptr;
					}

					pair		data;
					Node		*left;
					Node		*right;
					Node		*parent;
			};

/*-------------------------------------------TYPEDEFS-------------------------------------------*/
		public:
/*	key_type				The first template parameter (Key)	
 *	mapped_type				The second template parameter (T)	
 *	value_type				pair<const key_type,mapped_type>	
 *	key_compare				The third template parameter (Compare)			defaults to: less<key_type>
 *	value_compare			Nested function class to compare elements		see value_comp
 *	allocator_type			The fourth template parameter (Alloc)			defaults to: allocator<value_type>
 *	reference				allocator_type::reference						default allocator: value_type&
 *	const_reference			allocator_type::const_reference					default allocator: const value_type&
 *	pointer					allocator_type::pointer							default allocator: value_type*
 *	const_pointer			allocator_type::const_pointer					default allocator: const value_type*
 *	iterator				a bidirectional iterator to value_type			convertible to const_iterator
 *	const_iterator			a bidirectional iterator to const value_type	
 *	reverse_iterator		reverse_iterator<iterator>	
 *	const_reverse_iterator	reverse_iterator<const_iterator>	
 *	difference_type			a signed integral type, identical to: 			usually ptrdiff_t
 *							iterator_traits<iterator>::difference_type	
 *	size_type				an unsigned integral type that can represent	usually size_t 
 *							any non-negative value of difference_type		*/

			typedef Key													key_type;
			typedef T													mapped_type;
			typedef std::pair<const key_type, mapped_type>				value_type;
			typedef Node<key_type, mapped_type>							node_type;
			typedef Compare												key_compare;
			//typedef			value_compare;
			typedef	Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef MapBiIterator<node_type, value_type>				iterator;
			typedef MapBiIterator<node_type, const value_type>			const_iterator;
			//typedef ReverseMapBiIterator<node_type, mapped_type>		reverse_iterator:
			//typedef ReverseMapBiIterator<node_type, const mapped_type>	const_reverse_iterator:
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;

/*-------------------------------------------MEMBER VARIABLES-------------------------------------------*/
		private:
			node_type	*_head;
			node_type	*_lend;
			node_type	*_rend;
			size_type	_size;
			key_compare	_kcomp;
			Alloc		_alloc;

/*-------------------------------------------CONSTRUCTORS-------------------------------------------*/
		public:

/*	empty container constructor (default constructor) : Constructs an empty container, with no elements.	*/

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _head(NULL), _lend(new node_type()), _rend(new node_type()), _size(0), _kcomp(comp), _alloc(alloc) {}

/*	range constructor : Constructs a container with as many elements as the range [first,last), with each 
 *	element constructed from its corresponding element in that range.	*/

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

/*	copy constructor : Constructs a container with a copy of each of the elements in x.	*/

			map (const map& x);

			~map(void) {
				_rdel(_head);
			} 

/*-------------------------------------------OPERATORS-------------------------------------------*/

/*-------------------------------------------ITERATORS ACCESS-------------------------------------------*/

/*	Returns an iterator referring to the first element in the map container.
 *	Because map containers keep their elements ordered at all times, begin points to the element that 
 *	goes first following the container's sorting criterion.
 *	If the container is empty, the returned iterator value shall not be dereferenced.	*/

			iterator					begin() {
				if (empty())
					return iterator(_rend);
				return iterator(_lend->parent);
			}

			const_iterator				begin() const {
				if (empty())
					return const_iterator(_rend);
				return const_iterator(_lend->parent);
			}

/*	Returns an iterator referring to the past-the-end element in the map container.
 *	The past-the-end element is the theoretical element that would follow the last element in the 
 *	map container. It does not point to any element, and thus shall not be dereferenced.
 *	Because the ranges used by functions of the standard library do not include the element pointed 
 *	by their closing iterator, this function is often used in combination with map::begin to specify
 *	a range including all the elements in the container.
 *	If the container is empty, this function returns the same as map::begin.	*/

			iterator					end() {
				return iterator(_rend);
			}

			const_iterator end() const {
				return const_iterator(_rend);
			}

/*-------------------------------------------CAPACITY-------------------------------------------*/
			
			/*	Returns whether the map container is empty (i.e. whether its size is 0).	*/

			bool						empty() const {
				return !_size;
			}

			/*	Returns the number of elements in the map container.	*/

			size_type					size() const {
				return _size;
			}

			/*	Returns the maximum number of elements that the map container can hold.	*/

			size_type		max_size() const {
				return std::numeric_limits<difference_type>::max() / 20;
			}

/*-------------------------------------------ELEMENT ACCESS-------------------------------------------*/

/*	If k matches the key of an element in the container, the function returns a reference to its 
 *	mapped value.	
 *	If k does not match the key of any element in the container, the function inserts a new element 
 *	with that key and returns a reference to its mapped value. Notice that this always increases the 
 *	container size by one, even if no mapped value is assigned to the element (the element is constructed 
 *	using its default constructor).	*/	
			mapped_type&	operator[] (const key_type& k) {
				return  (*((insert(value_type(k, mapped_type()))).first)).second;
			}

/*-------------------------------------------MODIFIERS-------------------------------------------*/

/*	Extends the container by inserting new elements, effectively increasing the container size by the 
 *	number of elements inserted.
 *	Because element keys in a map are unique, the insertion operation checks whether each inserted element 
 *	has a key equivalent to the one of an element already in the container, and if so, the element is not 
 *	inserted, returning an iterator to this existing element (if the function returns a value).	*/

			std::pair<iterator,bool>	insert (const value_type& val) {
				node_type		*ptr;
				int				placed;

				if (_head == NULL) {
					_head = _new_node(val, NULL, NULL, NULL);
					ptr = _head;
					placed = 1;
					++_size;
				} else {
					ptr = _head;
					placed = 0;
					while (!placed) {
						if (val.first == ptr->data.first) {
							break;
						} else if (_kcomp(val.first, ptr->data.first)) {	//TODO use _keycomp
							if (ptr->left && ptr->left != _lend)
								ptr = ptr->left;
							else {
								ptr->left = _new_node(val, NULL, NULL, ptr);
								ptr = ptr->left;
								placed = 1;
								++_size;
							}
						} else {
							if (ptr->right && ptr->right != _rend)
								ptr = ptr->right;
							else {
								ptr->right = _new_node(val, NULL, NULL, ptr);
								ptr = ptr->right;
								placed = 1;
								++_size;
							}
						} 					}
				}
				_fix_tail();
				return std::pair<iterator,bool>(iterator(ptr), placed);
			}

			iterator					insert (iterator position, const value_type& val) {
				/* trying to do this optimization in a way that 100% doesnt result in unsorted tree is hard as hell*/
				(void)position;
				return insert(val).first;
            }

			template <class InputIterator>
			void						insert (InputIterator first, InputIterator last);

/*-------------------------------------------NON-STL FUNCTIONS-------------------------------------------*/
		private:
			/*	creates a new node, with given arguements (pair(key, val), left, right, parent)
			 *	returns: node_type* new node	*/

			node_type*				_new_node(const value_type& val, node_type *left = NULL, node_type *right = NULL, node_type *parent = NULL) {
				value_type	*tmp;

				tmp = _alloc.allocate(1);
				_alloc.construct(tmp, val);
				return new node_type(val, left, right, parent);
			}

			/*	corrects lend and rend	*/

			void					_fix_tail(void) {
				node_type	*ptr;

				/* perror("fix tail: setting left"); */
				ptr = _head;
				while (ptr->left)
					ptr = ptr->left;
				if (ptr != _lend) {
					_lend->parent = ptr;
					ptr->left = _lend;
				}
				/* perror("fix tail: setting right"); */
				ptr = _head;
				while (ptr->right)
					ptr = ptr->right;
				if (ptr != _rend) {
					_rend->parent = ptr;
					ptr->right = _rend;
				}
				/* perror("fix tail: done"); */
			}

			void					_rdel(node_type *me) {
				if (me) {
					if (me->left)
						_rdel(me->left);
					if (me->right)
						_rdel(me->right);
					delete me;
				}
			}

	};
}

/*-------------------------------------------NON-MEMBER OVERLOADS-------------------------------------------*/

#endif
