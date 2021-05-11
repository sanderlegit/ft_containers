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
						/* ++(*this); */
						++ret;
				else if (rhs < 0)
					for (int i = 0; i > rhs; --i)
						/* --(*this); */
						--ret;
				return ret;
			}

			MapBiIterator		operator-(const int& rhs) {			//i - x
				MapBiIterator	ret(*this);

				if (rhs > 0)
					for (int i = 0; i < rhs; ++i)
						/* --(*this); */
						++ret;
				else if (rhs < 0)
					for (int i = 0; i > rhs; --i)
						/* ++(*this); */
						--ret;
				return ret;
			}

			bool					operator==(const MapBiIterator& rhs) const { return node == rhs.node; }
			bool					operator!=(const MapBiIterator& rhs) const { return node != rhs.node; }
			pointer					operator->() const { return &(node->data); }
			reference 				operator*() const { return node->data; }

			operator MapBiIterator<node_t, const value_t>() { return node; }
	};

	template<class node_t, class value_t>
	class MapReverseBiIterator {
		public:
			node_t	*node;

			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef	value_t									value_type;
			typedef	value_t&								reference;
			typedef	value_t*								pointer;
			typedef	ptrdiff_t								difference_type;

			MapReverseBiIterator(node_t* n = NULL) : node(n) {}
			MapReverseBiIterator(const MapReverseBiIterator& src) { *this = src; }
			~MapReverseBiIterator(void) {}

			MapReverseBiIterator&		operator=(const MapReverseBiIterator& rhs) {
				node = rhs.node;
				return *this;
			}


			MapReverseBiIterator		operator++(int n) {		//i++
				MapReverseBiIterator	ret(*this);

				(void)n;
				++(*this);
				return ret;
			}

			MapReverseBiIterator		operator--(int n) {		//i--
				MapReverseBiIterator	ret(*this);

				(void)n;
				--(*this);
				return ret;
			}

			MapReverseBiIterator&		operator++() {			//++i
				node = node->prev();
				return *this;
			}

			MapReverseBiIterator&		operator--() {			//--i
				node = node->next();
				return *this;
			}

			MapReverseBiIterator		operator+(const int& rhs) {			//i + x
				MapReverseBiIterator	ret(*this);

				if (rhs > 0)
					for (int i = 0; i < rhs; ++i)
						/* ++(*this); */
						++ret;
				else if (rhs < 0)
					for (int i = 0; i > rhs; --i)
						/* --(*this); */
						--ret;
				return ret;
			}

			MapReverseBiIterator		operator-(const int& rhs) {			//i - x
				MapReverseBiIterator	ret(*this);

				if (rhs > 0)
					for (int i = 0; i < rhs; ++i)
						/* --(*this); */
						--ret;
				else if (rhs < 0)
					for (int i = 0; i > rhs; --i)
						/* ++(*this); */
						++ret;
				return ret;
			}

			bool					operator==(const MapReverseBiIterator& rhs) const { return node == rhs.node; }
			bool					operator!=(const MapReverseBiIterator& rhs) const { return node != rhs.node; }
			pointer					operator->() const { return &(node->data); }
			reference 				operator*() const { return node->data; }

			operator MapReverseBiIterator<node_t, const value_t>() { return node; }
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
			typedef MapReverseBiIterator<node_type, value_type>			reverse_iterator;
			typedef MapReverseBiIterator<node_type, const value_type>	const_reverse_iterator;
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
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _head(NULL), _lend(new node_type()), _rend(new node_type()), _size(0), _kcomp(comp), _alloc(alloc) {
				insert(first, last);
			}

/*	copy constructor : Constructs a container with a copy of each of the elements in x.	*/

			map (const map& x) : _head(NULL), _lend(new node_type()), _rend(new node_type()), _size(0), _kcomp(key_compare()), _alloc(allocator_type()) {
				insert(x.begin(), x.end());
			}

			~map(void) {
				if (_head == NULL) {
					delete _rend;
					delete _lend;
				} else 
					_rdel(_head);
			} 

/*-------------------------------------------OPERATORS-------------------------------------------*/

/*	Assigns new contents to the container, replacing its current content.	*/

			map&						operator= (const map& x) {
				clear();
				insert(x.begin(), x.end());
				return *this;
			}

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

/*	Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
 *	Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
 *	rbegin points to the element preceding the one that would be pointed to by member end.	*/

			reverse_iterator 			rbegin() {
				if (empty())
					return reverse_iterator(_lend);
				return reverse_iterator(_rend->parent);
			}

			const_reverse_iterator		rbegin() const {
				if (empty())
					return const_reverse_iterator(_lend);
				return const_reverse_iterator(_rend->parent);
			}

/*	Returns a reverse iterator pointing to the theoretical element right before the first element in the 
 *	map container (which is considered its reverse end).
 *	The range between map::rbegin and map::rend contains all the elements of the container (in reverse order).	*/

			reverse_iterator rend() {
				return reverse_iterator(_lend);
			}
			
			const_reverse_iterator rend() const {
				return const_reverse_iterator(_lend);
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
						} else if (_kcomp(val.first, ptr->data.first)) {
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
			void						insert (InputIterator first, InputIterator last) {
				while (first != last) {
					insert(*first);
					first++;
				}
			}

/*	Removes from the map container either a single element or a range of elements ([first,last)).
 *	This effectively reduces the container size by the number of elements removed, which are destroyed.	*/


			void						erase (iterator position) {
				node_type	*ins;
				node_type	*del;
				bool		wentchild;
				bool		wentleft;

				/* _rdebug(_head, 0, 3); */
				/* std::cout << "deleting: " << position->first << std::endl; */
				del = position.node;
				ins = position.node;
				wentchild = false;
				//finding the ins node
				if (del->right) {
					ins = del->right;
					while (ins->left) {
						wentchild = true;
						ins = ins->left;
					}
					wentleft = false;
				} else if (del->left) {
					ins = del->left;
					while (ins->right) {
						wentchild = true;
						ins = ins->right;
					}
					wentleft = true;
				} else {
					ins = NULL;
				}
				/* if (ins) */
				/* 	std::cout << "insert: " << ins->data.first << std::endl; */
				//setting ins
				if (ins) {
					//fixing ins children
					if (wentleft) {
						//if we went left and wentchild, ins must be right child, cannot have a right node
						if (wentchild && ins->left) {
							ins->parent->right = ins->left;
							ins->left->parent = ins->parent;
						} else if (ins->left) {
							ins->parent->left = ins->left;
							/* ins->left->parent = ins->parent; */
						} else if (wentchild) {
							ins->parent->right = NULL; 
						} else {
							ins->parent->left = NULL; 
						}
					} else {
						//if we went right and wentchild, ins must be left child, cannot have a left node
						if (wentchild && ins->right) {
							ins->parent->left = ins->right;
							ins->right->parent = ins->parent;
						} else if (ins->right) {
							ins->parent->right = ins->right;
							/* ins->right->parent = ins->parent; */
						} else if (wentchild) {
							ins->parent->left = NULL; 
						} else {
							ins->parent->right = NULL; 
						}
					}
					//giving ins dels links
					ins->left = del->left;
					if (del->left)
						del->left->parent = ins;
					ins->right = del->right;
					if (del->right)
						del->right->parent = ins;
					ins->parent = del->parent;
				}

				//fixing dels parent
				if (del == _head) {
					_head = ins;
				} else {
					if (del->parent->right == del) {
						del->parent->right = ins;
					} else if (del->parent->left == del) {
						del->parent->left = ins;
					}
				}

				delete position.node;
				_size--;
				_fix_tail();
				/* _rdebug(_head, 0, 3); */
				return;
			}

			size_type					erase (const key_type& k) {
				iterator	i;

				i = find(k);
				if (i != end()) {
					erase(i);
					return 1;
				}
				return 0;
			}

			void						erase (iterator first, iterator last) {
				iterator i;

				while (first != last) {
					i = first;
					first++;
					erase(i);
				}
			}

/*	Exchanges the content of the container by the content of x, which is another map of the same type. 
 *	Sizes may differ.
 *	After the call to this member function, the elements in this container are those which were in x before the 
 *	call, and the elements of x are those which were in this. All iterators, references and pointers remain valid
 *	for the swapped objects	*/

			void						swap (map& x) {
				node_type	*ptr;
				size_type	tmpsize;

				ptr = x._head;
				x._head = _head;
				_head = ptr;

				tmpsize = x._size;
				x._size = _size;
				_size = tmpsize;

				ptr = x._lend;
				x._lend = _lend;
				_lend = ptr;

				ptr = x._rend;
				x._rend = _rend;
				_rend = ptr;
			}

/*	Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.	*/

			void						clear() {
				if (_head != NULL) {
					_rdel(_head);
					_lend = new node_type();
					_rend = new node_type();
				}
			}

/*-------------------------------------------OBSERVERS-------------------------------------------*/

/*	Returns a copy of the comparison object used by the container to compare keys.	*/

			key_compare key_comp() const {
				return _kcomp;
			}


/*	Returns a comparison object that can be used to compare two elements to get whether the key of 
 *	the first one goes before the second.
 *	The arguments taken by this function object are of member type value_type (defined in map as an alias
 *	of pair<const key_type,mapped_type>), but the mapped_type part of the value is not taken into 
 *	consideration in this comparison.
 *	The comparison object returned is an object of the member type map::value_compare, which is a 
 *	nested class that uses the internal comparison object to generate the appropriate comparison functional 
 *	class. It is defined with the same behavior as:	*/

			class value_compare : public std::binary_function<value_type, value_type, bool>{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool				operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};

			value_compare					value_comp() const {
				return value_compare(_kcomp);
			}

/*-------------------------------------------OPERATIONS-------------------------------------------*/

/*	Searches the container for an element with a key equivalent to k and returns an iterator to it if found, 
 *	otherwise it returns an iterator to map::end.
 *	Two keys are considered equivalent if the container's comparison object returns false reflexively
 *	(i.e., no matter the order in which the elements are passed as arguments). */

			iterator					find (const key_type& k) {
				for (iterator i = begin(); i != end(); i++) {
					if (!_kcomp(i->first, k) && !_kcomp(k, i->first)) {
						return i;
					}
				}
				return end();
			}

			const_iterator				find (const key_type& k) const {
				for (iterator i = begin(); i != end(); i++) {
					if (!_kcomp(i->first, k) && !_kcomp(k, i->first)) {
						return i;
					}
				}
				return end();
			}

/*	Searches the container for elements with a key equivalent to k and returns the number of matches.
 *	Because all elements in a map container are unique, the function can only return 1 (if the element 
 *	is found) or zero (otherwise).
 *	Two keys are considered equivalent if the container's comparison object returns false reflexively
 *	(i.e., no matter the order in which the keys are passed as arguments).	*/

			size_type					count (const key_type& k) const {
				for (const_iterator i = begin(); i != end(); i++) {
					if (!_kcomp(i->first, k) && !_kcomp(k, i->first)) {
						return 1;
					}
				}
				return 0;
			}

/*	Returns an iterator pointing to the first element in the container whose key is not considered to
 *	go before k (i.e., either it is equivalent or goes after).
 *	The function uses its internal comparison object (key_comp) to determine this, returning an iterator
 *	to the first element for which key_comp(element_key,k) would return false.	*/

			iterator					lower_bound (const key_type& k) {
				for (iterator i = begin(); i != end(); i++) {
					if (!_kcomp(i->first, k)) {
						return i;
					}
				}
				return end();
			}

			const_iterator				lower_bound (const key_type& k) const {
				for (const_iterator i = begin(); i != end(); i++) {
					if (!_kcomp(i->first, k)) {
						return i;
					}
				}
				return end();
			}
/*	Returns an iterator pointing to the first element in the container whose key is considered to 
 *	go after k.
 *	The function uses its internal comparison object (key_comp) to determine this, returning an 
 *	iterator to the first element for which key_comp(k,element_key) would return true.	*/

			iterator					upper_bound (const key_type& k) {
				for (iterator i = begin(); i != end(); i++) {
					if (_kcomp(k, i->first)) {
						return i;
					}
				}
				return end();
			}

			const_iterator				upper_bound (const key_type& k) const;

/*	Returns the bounds of a range that includes all the elements in the container which have a key 
 *	equivalent to k.
 *	Because the elements in a map container have unique keys, the range returned will contain a 
 *	single element at most.
 *	If no matches are found, the range returned has a length of zero, with both iterators pointing 
 *	to the first element that has a key considered to go after k according to the container's 
 *	internal comparison object (key_comp).
 *	Two keys are considered equivalent if the container's comparison object returns false reflexively
 *	(i.e., no matter the order in which the keys are passed as arguments).	*/

			std::pair<iterator, iterator>             equal_range (const key_type& k) {
				for (iterator i = begin(); i != end(); i++) {
					if (!_kcomp(i->first, k) && !_kcomp(k, i->first)) {
						return std::pair<iterator, iterator>(i, i + 1);
					}
					if (!_kcomp(i->first, k)) {
						return std::pair<iterator, iterator>(i, i);
					}
				}
				return std::pair<iterator, iterator>(end(), end());
			}

			std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
				for (iterator i = begin(); i != end(); i++) {
					if (!_kcomp(i->first, k) && !_kcomp(k, i->first)) {
						return std::pair<iterator, iterator>(i, i + 1);
					}
					if (!_kcomp(i->first, k)) {
						return std::pair<iterator, iterator>(i, i);
					}
				}
				return std::pair<iterator, iterator>(end(), end());
			}

/*-------------------------------------------NON-STL FUNCTIONS-------------------------------------------*/
		private:
			/*	creates a new node, with given arguements (pair(key, val), left, right, parent)
			 *	returns: node_type* new node	*/

			node_type*				_new_node(const value_type& val, node_type *left = NULL, node_type *right = NULL, node_type *parent = NULL) {
				return new node_type(val, left, right, parent);
			}

			/*	corrects lend and rend	*/

			void					_fix_tail(void) {
				node_type	*ptr;

				ptr = _head;
				while (ptr->left)
					ptr = ptr->left;
				if (ptr != _lend) {
					_lend->parent = ptr;
					ptr->left = _lend;
				}
				ptr = _head;
				while (ptr->right)
					ptr = ptr->right;
				if (ptr != _rend) {
					_rend->parent = ptr;
					ptr->right = _rend;
				}
			}

			void					_rdel(node_type *me) {
				_size = 0;
				if (me) {
					if (me->left)
						_rdel(me->left);
					if (me->right)
						_rdel(me->right);
					delete me;
				}
				_head = NULL;
			}

			void					_rdebug(node_type *me, int pad, int incr) {
				if (me) {
					if (pad / incr > _size) {
						std::cout << "infinite loop!" << std::endl;
						return;
					}
					if (me->right)
						_rdebug(me->right, pad + incr, incr);
					for (int i = 0; i < pad; i++) {
						if (i % incr == 0)
							std::cout << "|";
						else
							std::cout << " ";
					}
					printf("%-4d", me->data.first);
					int tmp = _size - (pad / incr);
					tmp *= incr;
					for (int i = 0; i < tmp; i++) {
						std::cout << "-";
					}
						std::cout << "\t";
					std::cout << me << "\tp: " << me->parent << "\tl: " << me->left << "\tr: " << me->right << std::endl;
					if (me->left)
						_rdebug(me->left, pad + incr, incr);
				}
			}

	};
}

/*-------------------------------------------NON-MEMBER OVERLOADS-------------------------------------------*/

#endif
