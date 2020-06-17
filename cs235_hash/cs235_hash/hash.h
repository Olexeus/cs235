#ifndef HASH_H
#define HASH_H

#include "list.h"

namespace custom
{
   template <class T>
	class Hash
	{
	public:
#ifdef UNIT_TESTING
		// friend int ::main(int argc, const char* argv[]);
#endif // UNIT_TESTING

		Hash(int numBuckets);
		Hash(const Hash<T>& rhs);
		~Hash();

		// getters
		int size()		const;
		int capacity()	const;
		bool empty()	const;

		// access // TODO what is this
		void insert(const T& t, long (*hashFunc)(const T& aValue, long theBucketCount));
		bool find(const T& t, long (*hashFunc)(const T& aValue, long theBucketCount));
		Hash<T>& operator=(const Hash<T>& rhs);

	public:
		int numElements;
		int numBuckets;
		list<T>** table;
	};


	
	// constructors
	template<class T>
	inline Hash<T>::Hash(int numBuckets)
	{
		if (numBuckets <= 0)
			throw "Error: Hashes must have at least 1 bucket.";

		this->numBuckets = numBuckets;
		this->numElements = 0;

		table = new list<T> * [this->numBuckets];
		for (int i = 0; i < this->numBuckets; i++)
		{
			this->table[i] = new list<T>();
		}
	}
	template<class T>
	inline Hash<T>::Hash(const Hash<T>& rhs)
	{
		*this = rhs;
	}
	template<class T>
	inline Hash<T>::~Hash()
	{
		for (int i = 0; i < this->numBuckets; i++)
		{
			// delete this->table[i];
		}
		// delete[] table;
	}



	// getters
	template<class T>
	inline int Hash<T>::size() const
	{
		return this->numElements;
	}
	template<class T>
	inline int Hash<T>::capacity() const
	{
		return this->numBuckets;
	}
	template<class T>
	inline bool Hash<T>::empty() const
	{
		return this->numElements == 0;
	}



	// access
	template<class T>
	inline void Hash<T>::insert(const T& t, long (*hashFunc)(const T& aValue, long theBucketCount) )
	{
		int index = hashFunc(t, this->numBuckets);
		this->table[index]->push_back(t);
		this->numElements++;
	}
	template<class T>
	inline bool Hash<T>::find(const T& t, long (*hashFunc)(const T& aValue, long theBucketCount))
	{
		int index = hashFunc(t, this->numBuckets);
		typename list<T>::iterator it = this->table[index]->find(t);
		return it != NULL;
	}
	template<class T>
	inline Hash<T>& Hash<T>::operator=(const Hash<T>& rhs)
	{
		this->~Hash();
		table = new list<T> * [rhs.numBuckets];
		this->numBuckets = rhs.numBuckets;
		this->numElements = rhs.numElements;
		for (int i = 0; i < rhs.numBuckets; i++)
		{
			this->table[i] = rhs.table[i];
		}
		return *this;
	}
}
#endif // !HASH_H
