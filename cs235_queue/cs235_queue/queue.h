#ifndef QUEUE_H
#define QUEUE_H

#ifdef UNIT_TESTING
	int main(int argc, const char* argv[]);
#endif

namespace custom 
{
   template <class T>
	class queue
	{
	public:
		// for unit testing give access to private data	
		#ifdef UNIT_TESTING
			friend int ::main(int argc, const char* argv[]);
		#endif // UNIT_TESTING

		// constructors
		queue();
		queue(int numCapacity);
		queue(queue<T>& rhs);
		~queue();

		// getters and setters(this->numPop <= 0) ? 0 : 
		int size()		const { return (this->numPush >= this->numPop) ? this->numPush - this->numPop : 0; }
		int capacity() const { return this->numCapacity; }
		bool empty()	const { return this->size() == 0; }
		void clear()			{ this->numPush = this->numPop = 0; }

		// general 
		void push(T t);
		void pop();

		// getters and setters
		const T& front() const;
		T& front();
		const T& back() const;
		T& back();

		// operators
		queue<T>& operator= (const queue<T>& rhs);

	private:
		T* buffer;
		unsigned int numPush;
		unsigned int numPop;
		unsigned int numCapacity;
		void resize(int numCapacity);

		// getters and setters
		int iHead() { return (this->numPop) % this->numCapacity; }
		int iTail() { return ((long long)this->numPush - 1) % this->numCapacity; }
	};

	// constructors and destructor
	template <class T>
	queue<T>::queue()
	{
		this->numPush = this->numPop = this->numCapacity = 0;
		buffer = NULL;
	}

	template<class T>
	inline queue<T>::queue(int numCapacity)
	{
		this->numPush = this->numPop = 0;
		this->numCapacity = numCapacity;
		buffer = new T[this->numCapacity];
	}

	template<class T>
	inline queue<T>::queue(queue<T>& rhs)
	{
		*this = rhs;
	}

	template <class T>
	queue<T>::~queue()
	{
		if (buffer != NULL)
			delete[] buffer;
		buffer = NULL;
	}

	// general functions
	template<class T>
	inline void queue<T>::push(T t)
	{
		if (this->size() == this->capacity())
		{
			this->resize((this->capacity() == 0) ? 1 : this->capacity() * 2);
		}
		this->numPush++;
		buffer[iTail()] = t;
	}

	template<class T>
	inline void queue<T>::pop()
	{
		if (!this->empty())
			this->numPop++;
	}
	
	template<class T>
	inline queue<T>& queue<T>::operator=(const queue<T>& rhs)
	{
		if (this->capacity() < rhs.size())
			this->resize(rhs.size());

		this->numPush = this->numPop = 0;
		for (int i = rhs.numPop; i < rhs.numPush; i++)
		{
			buffer[this->numPush] = rhs.buffer[i % rhs.capacity()];
			this->numPush++;
		}
		return *this;
	}

	template<class T>
	inline void queue<T>::resize(int numCapacity)
	{
		if (numCapacity <= 0)
		{
			if (buffer != NULL)
			{
				delete[] buffer;
				buffer = NULL;
			}
			this->numCapacity = 0;
			this->numPush = this->numPop = 0;
		}
		else if (numCapacity > 0)
		{
			T* newBuffer = new T[numCapacity];
			int numMax = (this->size() > numCapacity) ? numCapacity : this->size();
			int numItems = 0;
			if (buffer != NULL)
			{
				for (int i = this->numPop; i < this->numPop + numMax; i++)
				{
					newBuffer[numItems] = this->buffer[i % this->numCapacity];
					numItems++;
				}
			}
			delete[] buffer;
			buffer = newBuffer;
			this->numCapacity = numCapacity;
			this->numPop = 0;
			this->numPush = numItems;
		}
	}

	// getters and setters
	template<class T>
	inline const T& queue<T>::front() const
	{
		if (this->empty())
			throw "Error: asking for front of empty queue.";
		return buffer[this->iHead()];
	}
	template<class T>
	inline T& queue<T>::front()
	{
		if (this->empty())
			throw "Error: asking for front of empty queue.";
		return buffer[this->iHead()];
	}
	template<class T>
	inline const T& queue<T>::back() const
	{
		if (this->empty())
			throw "Error: asking for back of empty queue.";
		return buffer[this->iTail()];
	}
	template<class T>
	inline T& queue<T>::back()
	{
		if (this->empty())
			throw "Error: asking for back of empty queue.";
		return buffer[this->iTail()];
	}
}
#endif // !QUEUE_H
