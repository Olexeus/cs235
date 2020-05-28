#ifndef STACK_H
#define STACK_H

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{

	template <class T>
	class stack
	{
	public:
		// for unit testing give access to private data	
		#ifdef UNIT_TESTING
			friend int ::main(int argc, const char* argv[]);
		#endif

		// constructors
		stack();
		stack(int numCapacity);
		stack(const stack& rhs);
		~stack();

		// getters and setters
		int size()		const { return this->numElements;	}
		int capacity() const { return this->numCapacity;	}
		bool empty()	const { return this->size() == 0;	}
		void clear()			{ this->numElements = 0;		}

		// special functions
		void push(T t);
		void pop();
		T& top();
		const T top() const;

		// operators
		stack& operator= (const stack& rhs);

	private:
		T* buffer;
		int numElements;
		int numCapacity;
		void resize(int numCapacity);
	};

	template <class T>
	stack<T>::stack()
	{
		buffer = NULL;
		this->numElements = 0;
		this->numCapacity = 0;
	}

	template<class T>
	inline stack<T>::stack(int numCapacity)
	{
		if (this->numCapacity <= 0)
			throw "";

		this->numCapacity = numCapacity;
		this->numElements = 0;
		buffer = new T[this->capacity()];
	}

	template<class T>
	inline stack<T>::stack(const stack& rhs)
	{
		*this = rhs;
	}

	template <class T>
	stack<T>::~stack()
	{
		if (buffer != NULL) delete[] buffer;
		this->numElements = this->numCapacity = 0;
		buffer = NULL;
	}

	template<class T>
	inline void stack<T>::push(T t)
	{
		if (this->size() == this->capacity())
		{
			this->resize((1 < numElements * 2) ? numElements * 2 : 1);
		}
		this->buffer[this->numElements++] = t;
	}

	template<class T>
	inline void stack<T>::pop()
	{
		if (!this->empty())
			this->numElements--;
	}

	template<class T>
	inline T& stack<T>::top()
	{
		if (this->empty())
			throw "Error: asking for top of empty stack.";
		return *(buffer + this->size() - 1);
	}

	template<class T>
	inline const T stack<T>::top() const
	{
		if (this->empty())
			throw "";
		return buffer[this->size() - 1];
	}

	template<class T>
	inline stack<T>& stack<T>::operator=(const stack& rhs)
	{
		this->clear();
		if (rhs.size() > this->capacity())
		{
			this->resize(rhs.size());
		}
		for (int i = 0; i < rhs.size(); i++)
		{
			this->buffer[i] = rhs.buffer[i];
		}
		this->numElements = rhs.size();
		return *this;
	}

	template<class T>
	inline void stack<T>::resize(int numCapacity)
	{
		if (numCapacity == 0)
		{
			delete[] buffer;
			buffer = NULL;
			this->numCapacity = 0;
			this->numElements = 0;
		}
		if (numCapacity > 0)
		{
			T* newBuffer = new T[numCapacity];
			int numItems = (this->numElements > numCapacity) ? numCapacity : this->numElements;
			if (buffer != NULL)
			{
				for (int i = 0; i < numItems; i++)
					newBuffer[i] = this->buffer[i];
			}
			delete[] buffer;
			buffer = newBuffer;
			this->numCapacity = numCapacity;
			this->numElements = numItems;
		}
	}
}

#endif // !STACK_H
