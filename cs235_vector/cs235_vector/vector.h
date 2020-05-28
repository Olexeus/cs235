/*************************************************************
 * File: vector.h
 * Author: Oleksii Fedorenko
 *
 * Description: Contains the definition of the bullet class.
 *
 *************************************************************/

#ifndef vector_h
#define vector_h

#include <string>

namespace custom {

	template <class T>
	class vector
	{
	public:
		vector();
		vector(int numElements);
		vector(int numElements, T t);
		vector(const vector& rhs);
		~vector();

		// getters
		int size()		const { return this->numElements; }
		int capacity() const { return this->numCapacity; }
		bool empty()	const { return numElements == 0; }

		void clear();
		vector& operator=(const vector& rhs);
		void push_back(T t);

		// assess
		const T operator[](int index) const;
		T& operator[](int index);

		class iterator;
		iterator begin() { return iterator(buffer); }
		iterator end() { return iterator(buffer + this->numElements); }

	public:
		int numElements;
		int numCapacity;
		T* buffer;
		void resize(int numCapacity);
	};

	template <class T>
	class vector<T> ::iterator
	{

	public:
		const T* vp;
		int index;

	public:

		iterator() {
			this->vp = NULL;
		}

		iterator(const iterator& it) {
			this->vp = it.vp;
		}

		iterator(const T* vp) {
			this->vp = vp;
		}

		iterator& operator=(const iterator& rhs) {
			this->vp = rhs.vp;
			return *this;
		}

		iterator& operator++() {
			(this->vp != NULL) ? this->vp++ : this->vp;
			
			return *this;
		}

		iterator operator++(int) {
			iterator copy(*this);
			operator++();
			return copy;
		}

		iterator& operator--() {
			(this->vp != NULL) ? this->vp-- : this->vp;
			return *this;
		}

		iterator operator--(int) {
			iterator copy(*this);
			operator--();
			return copy;
		}

		bool operator==(const iterator& rhs) {
			return vp == rhs.vp && index == rhs.index;
		}

		bool operator!=(const iterator& rhs) {
			return !(*this == rhs);
		}

		T operator*() {
			return *vp;
		}

	};

	template<class T>
	inline vector<T>::vector()
	{
		numCapacity = 0;
		numElements = 0;
		buffer = NULL;
	}

	template<class T>
	inline vector<T>::vector(int numElements) : vector()
	{
		if (numElements <= 0) throw "Error: vector sizes must be greater than 0.";
		this->numElements = numElements;
		this->resize(this->numElements);

		if (buffer != NULL)
		{
			for (int i = 0; i < this->numCapacity; i++)
			{
				buffer[i] = 0;
			}
		}
	}

	template<class T>
	inline vector<T>::vector(int numElements, T t)
	{
		if (numElements <= 0) throw "Error: vector sizes must be greater than 0.";
		this->numElements = numElements;
		this->resize(this->numElements);

		if (buffer != NULL)
		{
			for (int i = 0; i < this->numCapacity; i++)
			{
				buffer[i] = t;
			}
		}
	}

	template<class T>
	vector<T>::vector(const vector& rhs)
	{
		this->resize(rhs.size());
		this->numElements = rhs.size();
		for (int i = 0; i < this->numElements; i++)
		{
			buffer[i] = rhs.buffer[i];
		}
	}

	template<class T>
	inline vector<T>::~vector()
	{
		if (buffer != NULL) delete[] buffer;
		this->numElements = this->numCapacity = 0;
		buffer = NULL;
	}

	template<class T>
	inline void vector<T>::clear()
	{
		this->numElements = 0;
	}

	template<class T>
	vector<T>& vector<T>::operator=(const vector& rhs)
	{
		this->numElements = 0;
		if (rhs.size() > this->numCapacity)
		{
			this->resize(rhs.size());
		}
		this->numElements = rhs.size();
		for (int i = 0; i < this->numElements; i++)
		{
			buffer[i] = rhs.buffer[i];
		}
		return *this;
	}

	template<class T>
	inline void vector<T>::push_back(T t)
	{
		if (this->numElements == this->numCapacity)
		{
			this->resize((1 < numElements * 2) ? numElements * 2 : 1);
		}
		buffer[this->numElements++] = t;
	}

	template<class T>
	const T vector<T>::operator[](int index) const
	{
		if (index < 0 || index >= this->numElements) throw "Error: indices must be greater than zero and less than size().";
		return buffer[index];
	}

	template<class T>
	T& vector<T>::operator[](int index)
	{
		if (index < 0 || index >= this->numElements) throw "Error: indices must be greater than zero and less than size().";
		return buffer[index];
	}

	template<class T>
	inline void vector<T>::resize(int numCapacity)
	{
		//if (numCapacity <= 0) throw "Error: vector sizes must be greater than 0.";
		if (numCapacity >= 0)
		{
			/*int currentCapacity = this->numCapacity;
			while (currentCapacity < numCapacity)
			{
				currentCapacity = (1 < currentCapacity * 2) ? currentCapacity * 2 : 1;
			}*/
			int currentCapacity = numCapacity;
			T* newArray = new T[currentCapacity];
			

			if (buffer != NULL)
			{
				int upperBound = (this->numElements > currentCapacity) ? currentCapacity : this->numElements;
				for (int i = 0; i < upperBound; i++)
				{
					newArray[i] = buffer[i];
				}
			}

			delete[] buffer;
			buffer = newArray;
			if (currentCapacity == 0)
			{
				buffer = NULL;
			}
			
			this->numCapacity = currentCapacity;
			if (this->numCapacity <= this->numElements)
			{
				this->numElements = currentCapacity;
			}
		}

	}

}



#endif /* vector_h */

