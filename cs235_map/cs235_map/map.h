#ifndef MAP_H
#define MAP_H

#include "bst.h"
namespace custom {
   template <class K, class V>
	class map
	{
	public:
		#ifdef UNIT_TESTING
			//friend int ::main(int argc, const char* argv[]);
		#endif // UNIT_TESTING
		map();
		map(const map<K, V>& rhs);
		~map();

		// getters
		int size()		const { return bst.size(); }
		bool empty()	const { return bst.empty(); }
		void clear() { bst.clear(); }

		// access elements
		class pair;
		class iterator;
		iterator begin() const;
		iterator end() const;

		// special functions
		void insert(const K& k, const V& v);
		iterator find(const K& k);
		map<K, V>& operator=(const map<K, V>& rhs);

		// assess
		const V operator[](const K& k) const;
		V& operator[](const K& k);

	public:
		BST<pair> bst;
	};



	template <class K, class V>
	class map<K, V>::pair
	{
	public:
		pair() :first(), second() {}
		pair(const K& first, const V& second) :first(first), second(second) {}
		pair(const pair& rhs) { *this = rhs; }

		pair& operator=(const pair& rhs)
		{
			this->first = rhs.first;
			this->second = rhs.second;
			return *this;
		}
		bool operator==(const pair& rhs) const { return first == rhs.first; }
		bool operator!=(const pair& rhs) const { return first != rhs.first; }
		bool operator>(const pair& rhs) const	{ return first >  rhs.first; }
		bool operator<(const pair& rhs) const	{ return first <  rhs.first; }
		bool operator>=(const pair& rhs) const { return first >= rhs.first; }
		bool operator<=(const pair& rhs) const { return first <= rhs.first; }

	public:
		K first;
		V second;
	};



	template <class K, class V>
	class map<K, V>::iterator
	{

	public:
		typename BST<pair>::iterator it;

	public:

		// constructors
		iterator() {
			this->it = NULL;
		}

		iterator(const typename BST<pair>::iterator& it) {
			// accepts the bst iterator and assigns it
			this->it = it;
		}

		iterator(const iterator& it) {
			// access the bst iterator of map iterator
			this->it = it.it;
		}

		// Derefference operator
		pair operator*()
		{ 
			// derefference the bst it
			return *it;
		}

		// Assignment operator
		iterator& operator=(const iterator& rhs) {
			this->it = rhs.it;
			return *this;
		}

		// Increments and decrements
		iterator& operator++() {
			it++;
			return *this;
		}

		iterator operator++(int) {
			iterator copy(*this);
			operator++();
			return copy;
		}

		iterator& operator--() {
			it--;
			return *this;
		}

		iterator operator--(int) {
			iterator copy(*this);
			operator--();
			return copy;
		}

		// Comparison operators
		bool operator==(const iterator& rhs) {
			return this->it == rhs.it;
		}

		bool operator!=(const iterator& rhs) {
			return !(*this == rhs);
		}
	};


	// constructors
	template<class K, class V>
	inline map<K, V>::map()
	{
		this->bst = BST<pair>();
	}
	template<class K, class V>
	inline map<K, V>::map(const map<K, V>& rhs)
	{
		this->bst = rhs.bst;
	}
	template<class K, class V>
	inline map<K, V>::~map()
	{
		this->clear();
	}



	// access functions
	template<class K, class V>
	inline typename map<K, V>::iterator map<K, V>::begin() const
	{
		return iterator(bst.begin());
	}
	template<class K, class V>
	inline typename map<K, V>::iterator map<K, V>::end() const
	{
		return iterator(bst.end());
	}



	// search and insert functions
	template<class K, class V>
	inline void map<K, V>::insert(const K& k, const V& v)
	{
		// creating a pair 
		pair newPair(k, v);

		// creating the iterator of BST and finding the object
		typename BST<pair>::iterator it;
		it = bst.find(newPair);
		if (it != NULL)
		{
			// if found updaiting the value of the pair
			*it = newPair;
		}
		else
		{
			// inserting otherwise
			bst.insert(newPair);
		}
	}
	template<class K, class V>
	inline typename map<K, V>::iterator map<K, V>::find(const K& k)
	{
		// creating a pair 
		pair newPair(k, V());

		// creating the iterator of BST and finding the object
		typename BST<pair>::iterator it;
		return iterator(bst.find(newPair));
	}
	template<class K, class V>
	inline map<K, V>& map<K, V>::operator=(const map<K, V>& rhs)
	{
		this->bst = rhs.bst;
		return this;
	}
	template<class K, class V>
	inline const V map<K, V>::operator[](const K& k) const
	{
		// creating a pair 
		pair newPair(k, V());

		// creating the iterator of BST and finding the object
		typename BST<pair>::iterator it;
		it = bst.find(newPair);
		if (it != NULL)
		{ // if found return data
			return it.ptr->data.second;
		}

		// insert and return otherwise
		bst.insert(newPair);
		return bst.find(newPair).ptr->data.second;
	}
	template<class K, class V>
	inline V& map<K, V>::operator[](const K& k)
	{
		// creating a pair 
		pair newPair(k, V());

		// creating the iterator of BST and finding the object
		typename BST<pair>::iterator it;
		it = bst.find(newPair);
		if (it != NULL)
		{ // if found return data
			return it.ptr->data.second;
		}
		
		// insert and return otherwise
		bst.insert(newPair);
		return bst.find(newPair).ptr->data.second;
	}
}

#endif // !MAP_H
