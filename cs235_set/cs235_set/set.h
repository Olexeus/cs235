#ifndef SET_H
#define SET_H

namespace custom {
	template <class T>
	class set
	{
	public:
		#ifdef UNIT_TESTING_H
			friend int ::main(int argc, const char* argv[]);
		#endif // UNIT_TESTING_H

		// constructors and destructors
		set();
		set(int numCapacity);
		set(const set<T>& rhs);
		~set();

		// getters
		int size()		const { return this->numElements; }
		//int capacity() const { return this->numCapacity; }
		bool empty()	const { return this->numElements == 0; }
		void clear() { this->numElements = 0; }

		// access elements
		class iterator;
		iterator begin() { return iterator(buffer); }
		iterator end() { return iterator(buffer + this->numElements); }

		// special functions
		void insert(T t);
		iterator find(T t);
		iterator erase(set<T>::iterator it);
		set<T>& operator=(const set<T>& rhs);

		// combining operations
		set<T> operator|| (const set<T>& rhs) const;
		set<T> operator&& (const set<T>& rhs) const;
		set<T> operator- (const set<T>& rhs) const;

	public:
		int numElements;
		int numCapacity;
		T* buffer;
		void resize(int numCapacity);
		int findIndex(T t);
	};


	template <class T>
	class set<T>::iterator
	{

	public:
		const T* ptr;

	public:
		// constructors
		iterator() {
			this->ptr = NULL;
		}

		iterator(const iterator& it) {
			this->ptr = it.ptr;
		}

		iterator(const T* ptr) {
			this->ptr = ptr;
		}

		// Derefference operator
		T operator*() { return *ptr; }

		// Assignment operator
		iterator& operator=(const iterator& rhs) {
			this->ptr = rhs.ptr;
			return *this;
		}

		// Increments and decrements
		iterator& operator++() {
			(this->ptr != NULL) ? this->ptr++ : this->ptr;
			return *this;
		}

		iterator operator++(int) {
			iterator copy(*this);
			operator++();
			return copy;
		}

		iterator& operator--() {
			(this->ptr != NULL) ? this->ptr-- : this->ptr;
			return *this;
		}

		iterator operator--(int) {
			iterator copy(*this);
			operator--();
			return copy;
		}

		// Comparison operators
		bool operator==(const iterator& rhs) {
			return ptr == rhs.ptr;
		}

		bool operator!=(const iterator& rhs) {
			return !(*this == rhs);
		}
	};




	template<class T>
	inline set<T>::set()
	{
		this->numCapacity = 0;
		this->numElements = 0;
		this->buffer = NULL;
	}

	template<class T>
	inline set<T>::set(int numCapacity)
	{
		if (numCapacity < 0)
			throw "Error: set sizes must be greater than or equal to 0.";
		this->numCapacity = numCapacity;
		this->numElements = 0;
		this->buffer = new T[this->numCapacity];
	}

	template<class T>
	inline set<T>::set(const set<T>& rhs) : set<T>()
	{
		*this = rhs;
	}

	template<class T>
	inline set<T>::~set()
	{
		if (buffer != NULL) delete[] buffer;
		this->numElements = this->numCapacity = 0;
		buffer = NULL;
	}

	template<class T>
	inline void set<T>::insert(T t)
	{
		int iInsert = this->findIndex(t);

		if (this->numElements == this->numCapacity)
		{
			bool resize = true;
			// resize if element was not found and capacity reached
			if (iInsert < this->numCapacity && this->buffer[iInsert] == t)
				resize = false;

			if (resize == true)
				this->resize((1 < numElements * 2) ? numElements * 2 : 1);
		}

		if (buffer[iInsert] != t)
		{
			
			// shift all the elements
			for (int i = this->numElements - 1; i >= iInsert; i--)
			{
				buffer[i + 1] = buffer[i];
			}
			buffer[iInsert] = t;
			this->numElements++;
		}
	}

	template<class T>
	inline typename set<T>::iterator set<T>::find(T t)
	{
		int iInsert = this->findIndex(t);
		if (iInsert < this->numCapacity && buffer[iInsert] != t)
		{
			return iterator();
		}
		else
		{
			return iterator(buffer + iInsert);
		}
	}

	template<class T>
	inline typename set<T>::iterator set<T>::erase(set<T>::iterator it)
	{
		if (it.ptr != NULL)
		{
			int iErase = this->findIndex(*it);
			if (buffer[iErase] == *it)
			{
				for (int i = iErase; i < this->numElements; i++)
				{
					buffer[i] = buffer[i + 1];
				}
				this->numElements--;
			}
			return iterator(buffer + iErase);
		}
		return iterator();
	}

	template<class T>
	inline int set<T>::findIndex(T t)
	{
		int iBegin = 0;
		int iEnd = this->numElements - 1;
		int iMiddle = (iBegin + iEnd) / 2;

		while (iBegin <= iEnd)
		{
			if (t == buffer[iMiddle])
			{
				break;
			}
			else if (t < buffer[iMiddle]) {
				iEnd = iMiddle - 1;
			}
			else
			{
				iBegin = iMiddle + 1;
				// if needs to be inserted before the element
				// iMiddle--;
			}
			iMiddle = (iBegin + iEnd + 1) / 2;
		}
		return iMiddle;
	}

	template<class T>
	inline void set<T>::resize(int newCapacity)
	{
		if (newCapacity == 0)
		{
			if (buffer != NULL) delete[] buffer;
			this->numElements = this->numCapacity = 0;
			buffer = NULL;
		}
		else if (newCapacity > 0)
		{
			T* newArray = new T[newCapacity];

			if (buffer != NULL)
			{
				int upperBound = (this->numElements > newCapacity) ? newCapacity : this->numElements;
				for (int i = 0; i < upperBound; i++)
				{
					newArray[i] = buffer[i];
				}
			}

			// TODO
			//if (buffer != NULL) delete[] buffer;
			buffer = newArray;
			this->numCapacity = newCapacity;
			if (this->numCapacity <= this->numElements)
			{
				this->numElements = newCapacity;
			}
		}
	}

	template<class T>
	inline set<T>& set<T>::operator=(const set<T>& rhs)
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
	inline set<T> set<T>::operator||(const set<T>& rhs) const
	{
		/*set<T>* setReturn = new set<T>(*this);
		for (int i = 0; i < rhs.size(); i++)
		{
			setReturn->insert(rhs.buffer[i]);
		}
		return *setReturn;*/

		set<T>* setReturn = new set<T>();
		int iLhs = 0;
		int iRhs = 0;
		
		while (iLhs < this->numElements || iRhs < rhs.numElements)
		{
			// resize
			if (setReturn->numElements == setReturn->numCapacity)
			{
				setReturn->resize((1 < setReturn->numElements * 2) ? setReturn->numElements * 2 : 1);
			}

			// insert elements
			if (iLhs == this->numElements)
			{
				setReturn->buffer[setReturn->numElements++] = rhs.buffer[iRhs++];
			}
			else if (iRhs == rhs.numElements)
			{
				setReturn->buffer[setReturn->numElements++] = this->buffer[iLhs++];
			}
			else if (this->buffer[iLhs] == rhs.buffer[iRhs])
			{
				setReturn->buffer[setReturn->numElements++] = this->buffer[iLhs];
				iLhs++;
				iRhs++;
			}
			else if (this->buffer[iLhs] < rhs.buffer[iRhs])
			{
				setReturn->buffer[setReturn->numElements++] = this->buffer[iLhs++];
			}
			else if (this->buffer[iLhs] > rhs.buffer[iRhs])
			{
				setReturn->buffer[setReturn->numElements++] = rhs.buffer[iRhs++];
			}
		}

		return *setReturn; 
	}

	template<class T>
	inline set<T> set<T>::operator&&(const set<T>& rhs) const
	{
		set<T>* setReturn = new set<T>();
		int iLhs = 0;
		int iRhs = 0;

		while (iLhs < this->numElements || iRhs < rhs.numElements)
		{
			// resize
			if (setReturn->numElements == setReturn->numCapacity)
			{
				setReturn->resize((1 < setReturn->numElements * 2) ? setReturn->numElements * 2 : 1);
			}

			// insert elements
			if (iLhs == this->numElements)
			{
				return *setReturn;
			}
			else if (iRhs == rhs.numElements)
			{
				return *setReturn;
			}
			else if (this->buffer[iLhs] == rhs.buffer[iRhs])
			{
				setReturn->buffer[setReturn->numElements++] = this->buffer[iLhs];
				iLhs++;
				iRhs++;
			}
			else if (this->buffer[iLhs] < rhs.buffer[iRhs])
			{
				iLhs++;
			}
			else if (this->buffer[iLhs] > rhs.buffer[iRhs])
			{
				iRhs++;
			}
		}

		return *setReturn;
	}

	template<class T>
	inline set<T> set<T>::operator-(const set<T>& rhs) const
	{
		set<T>* setReturn = new set<T>();
		int iLhs = 0;
		int iRhs = 0;

		while (iLhs < this->numElements || iRhs < rhs.numElements)
		{
			// resize
			if (setReturn->numElements == setReturn->numCapacity)
			{
				setReturn->resize((1 < setReturn->numElements * 2) ? setReturn->numElements * 2 : 1);
			}

			// insert elements
			if (iLhs == this->numElements)
			{
				return *setReturn;
			}
			else if (iRhs == rhs.numElements)
			{
				setReturn->buffer[setReturn->numElements++] = this->buffer[iLhs++];
			}
			else if (this->buffer[iLhs] == rhs.buffer[iRhs])
			{
				iLhs++;
				iRhs++;
			}
			else if (this->buffer[iLhs] < rhs.buffer[iRhs])
			{
				setReturn->buffer[setReturn->numElements++] = this->buffer[iLhs++];
			}
			else if (this->buffer[iLhs] > rhs.buffer[iRhs])
			{
				iRhs++;
			}
		}

		return *setReturn;
	}

}

#endif // !SET_H
