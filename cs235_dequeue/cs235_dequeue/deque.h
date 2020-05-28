#ifndef DEQUEUE_H
#define DEQUEUE_H

#define ABS(N) ((N<0)?(-N):(N))

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif


namespace custom
{
	template <class T>
	class deque
	{
	public:
		// for unit testing give access to private data	
#ifdef UNIT_TESTING
		friend int ::main(int argc, const char* argv[]);
#endif // UNIT_TESTING

		// constructors
		deque();
		deque(int numCapacity);
		deque(deque<T>& rhs);
		~deque();

		// getters and setters(this->iBack <= 0) ? 0 : 
		int size()		const { return this->iBack - this->iFront + 1; }
		int capacity() const { return this->numCapacity; }
		bool empty()	const { return this->size() == 0; }
		void clear() { this->iFront = 0; this->iBack = -1; }

		// general 
		void push_front(T t);
		void pop_front();
		void push_back(T t);
		void pop_back();

		// getters and setters
		const T& front() const;
		T& front();
		const T& back() const;
		T& back();

		// operators
		deque<T>& operator= (const deque<T>& rhs);

	private:
		T* buffer;
		long long int iFront;
		long long int iBack;
		unsigned int numCapacity;
		void resize(unsigned int numCapacity);

		// getters and setters
		int iFrontNormalize() { return this->iNormalize(iFront); }
		int iBackNormalize() { return this->iNormalize(iBack); }
		int iNormalize(int i) const
		{ 
			if (this->capacity() == 0)
				throw "Error: Uninitialized deque.";
			if (this->capacity() == 1)
				return 0;
			return ((i < 0) ? (this->capacity() - ABS(i) % this->capacity()) : ABS(i)) % this->capacity();
		}
	};

	// constructors and destructor
	template <class T>
	deque<T>::deque()
	{
		this->iFront = 0;
		this->iBack = -1;
		this->numCapacity = 0;
		buffer = NULL;
	}

	template<class T>
	inline deque<T>::deque(int numCapacity)
	{
		if (numCapacity < 0)
			throw "Error: deque sizes must be greater than or equal to 0.";
		this->iFront = 0;
		this->iBack = -1;
		this->numCapacity = numCapacity;
		buffer = new T[this->numCapacity];
	}

	template<class T>
	inline deque<T>::deque(deque<T>& rhs)
	{
		*this = rhs;
	}

	template <class T>
	deque<T>::~deque()
	{
		if (buffer != NULL)
			delete[] buffer;
		buffer = NULL;
	}

	// general functions
	template<class T>
	inline void deque<T>::push_back(T t)
	{
		if (this->size() == this->capacity())
		{
			this->resize((this->capacity() == 0) ? 1 : this->capacity() * 2);
		}
		this->iBack++;
		buffer[iBackNormalize()] = t;
	}

	template<class T>
	inline void deque<T>::push_front(T t)
	{
		if (this->size() == this->capacity())
		{
			this->resize((this->capacity() == 0) ? 1 : this->capacity() * 2);
		}
		this->iFront--;
		buffer[iFrontNormalize()] = t;
	}


	template<class T>
	inline void deque<T>::pop_back()
	{
		if (this->empty())
			throw "Error: Can not pop an empty deque.";
		this->iBack--;
	}

	template<class T>
	inline void deque<T>::pop_front()
	{
		if (this->empty())
			throw "Error: Can not pop an empty deque.";
		this->iFront++;
	}

	template<class T>
	inline deque<T>& deque<T>::operator=(const deque<T>& rhs)
	{
		this->clear();
		if (this->capacity() < rhs.size())
			this->resize(rhs.size());

		this->iFront = 0;
		this->iBack = -1;
		for (int i = rhs.iFront; i <= rhs.iBack; i++)
		{
			int rhsIndex = rhs.iNormalize(i);
			this->push_back(rhs.buffer[rhsIndex]);
		}
		return *this;
	}

	template<class T>
	inline void deque<T>::resize(unsigned int numCapacity)
	{
		if (numCapacity <= 0)
		{
			if (buffer != NULL)
			{
				delete[] buffer;
				buffer = NULL;
			}
			this->numCapacity = 0;
			this->iFront = 0;
			this->iBack = -1;
		}
		else if (numCapacity > 0)
		{
			T* newBuffer = new T[numCapacity];
			
			long long int numItems = 0;
			if (buffer != NULL)
			{
				int numMax = (this->size() > numCapacity) ? numCapacity : this->size();
				int numMin = this->iFrontNormalize();
				for (int i = numMin; i < numMin + numMax; i++)
				{
					newBuffer[numItems] = this->buffer[this->iNormalize(i)];
					numItems++;
				}
			}
			delete[] buffer;
			buffer = newBuffer;
			this->numCapacity = numCapacity;
			this->iBack = numItems - 1;
			this->iFront = 0;
		}
	}

	// getters and setters
	template<class T>
	inline const T& deque<T>::front() const
	{
		if (this->empty())
			throw "Error: deque is empty.";
		return buffer[this->iFrontNormalize()];
	}
	template<class T>
	inline T& deque<T>::front()
	{
		if (this->empty())
			throw "Error: deque is empty.";
		return buffer[this->iFrontNormalize()];
	}
	template<class T>
	inline const T& deque<T>::back() const
	{
		if (this->empty())
			throw "Error: deque is empty.";
		return buffer[this->iBackNormalize()];
	}
	template<class T>
	inline T& deque<T>::back()
	{
		if (this->empty())
			throw "Error: deque is empty.";
		return buffer[this->iBackNormalize()];
	}
}
#endif // !DEQUEUE_H
