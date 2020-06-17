#ifndef LIST_H
#define LIST_H
namespace custom {
	template <class T>
	class list
	{
	public:
		#ifdef UNIT_TESTING_H
			friend int ::main(int argc, const char* argv[]);
		#endif // UNIT_TESTING_H
		

		// constructors and destructors
		list();
		list(const list<T>& rhs);
		~list();

		// getters
		int size()		const;
		bool empty()	const;
		void clear();

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

		// access elements
		class iterator;
		iterator begin() const;
		iterator end() const;

		// special functions
		iterator insert(iterator& it, const T& t);
		iterator find(T t);
		iterator erase(iterator it);
		list<T>& operator=(const list<T>& rhs);

	public:
		class node;
		node* pHead;
		node* pTail;
		int numElements;
	};

	template <class T>
	class list<T>::iterator
	{

	public:
		list<T>::node* ptr;

	public:
		friend iterator list<T>::insert(iterator& it, const T& t);

		// constructors
		iterator() {
			this->ptr = NULL;
		}

		iterator(node* ptr) {
			this->ptr = ptr;
		}

		iterator(const iterator& it) {
			this->ptr = it.ptr;
		}

		// Derefference operator
		T operator*() 
		{ 
			if (this->ptr == NULL)
				throw "Error: Dereferencing null node.";
			return ptr->data; 
		}

		// Assignment operator
		iterator& operator=(const iterator& rhs) {
			this->ptr = rhs.ptr;
			return *this;
		}

		// Increments and decrements
		iterator& operator++() {
			if (this->ptr == NULL)
				throw "Error: Incrementing null node.";
			(this->ptr->pNext != NULL) ? this->ptr = this->ptr->pNext : this->ptr;
			return *this;
		}

		iterator operator++(int) {
			iterator copy(*this);
			operator++();
			return copy;
		}

		iterator& operator--() {
			if (this->ptr == NULL)
				throw "Error: Decrementing null node.";
			(this->ptr->pPrev != NULL) ? this->ptr = this->ptr->pPrev : this->ptr;
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

	template <class T>
	class list<T>::node
	{
	public:
		node() 
		{
			data = T();
			pNext = NULL;
			pPrev = NULL;
		}
		node(T t) : node()
		{
			data = t;
		}
		~node()
		{
			/*if (pNext != NULL)
				delete pNext;
			if (pPrev != NULL)
				delete pPrev;*/
			pNext = NULL;
			pPrev = NULL;
		}

	public:
		T data;
		node* pNext;
		node* pPrev;
	};


	// constructors
	template<class T>
	inline list<T>::list()
	{
		this->numElements = 0;
		this->pHead = NULL;
		this->pTail = NULL;
	}

	template<class T>
	inline list<T>::list(const list<T>& rhs)
	{
		*this = rhs;
	}

	template<class T>
	inline list<T>::~list()
	{
		for (list<T>::iterator it = this->begin(); it != this->end(); it)
		{
			if (it.ptr != NULL)
			{
				it = this->erase(it);
			}
		}
		if (pHead != NULL)
		{
			// delete pHead;
			pHead = NULL;
		}
		if (pTail != NULL)
		{
			// delete pTail;
			pTail = NULL;
		}
	}


	// getters and setters
	template<class T>
	inline int list<T>::size() const
	{
		return this->numElements;
	}

	template<class T>
	inline bool list<T>::empty() const
	{
		return pHead == NULL;
	}

	template<class T>
	inline void list<T>::clear()
	{
		for (list<T>::iterator it = this->begin(); it.ptr != NULL; it)
		{
			if (it.ptr != NULL)
			{
				it = this->erase(it);
			}
		}
		this->pHead = NULL;
		this->pTail = NULL;
		this->numElements = 0;
	}

	// insertion functions
	template<class T>
	inline typename list<T>::iterator list<T>::insert(iterator& it, const T& t)
	{
		node* pNew = new node(t);

		if (it != NULL)
		{
			pNew->pNext = it.ptr;
			pNew->pPrev = it.ptr->pPrev;
			it.ptr->pPrev = pNew;
			if (pNew->pPrev)
			{
				pNew->pPrev->pNext = pNew;
			}
		}

		if (this->pHead != NULL && this->pHead->pPrev != NULL)
		{
			this->pHead = pNew;
		}
		else if (this->pHead == NULL && this->pTail == NULL)
		{
			this->pHead = pNew;
			this->pTail = pNew;
		}
		/*if (it != NULL)
		{
			
			else if (it.ptr->pPrev == NULL)
			{
				pNew->pNext = it.ptr;
				pNew->pPrev = NULL;
				it.ptr->pPrev = pNew;
			}
			else if (it.ptr->pNext == NULL)
			{
				pNew->pPrev = it.ptr;
				pNew->pNext = NULL;
				it.ptr->pNext = pNew;
			}
			else
			{
				pNew->pNext = it.ptr;
				pNew->pPrev = it.ptr->pPrev;
				it.ptr->pPrev = pNew;
			}
			if (pNew->pPrev)
			{
				pNew->pPrev->pNext = pNew;
			}
		}*/
		it.ptr = pNew;
		this->numElements++;
		return it;
	}
	template<class T>
	inline void list<T>::push_front(T t)
	{
		node* pNew = new node(t);

		if (this->pHead != NULL)
		{
			pNew->pNext = this->pHead;
			if (pNew->pNext)
			{
				pNew->pNext->pPrev = pNew;
			}
			this->pHead = pNew;
		}
		else if (this->pHead == NULL && this->pTail == NULL)
		{
			this->pHead = pNew;
			this->pTail = pNew;
		}
		this->numElements++;
	}
	template<class T>
	inline void list<T>::push_back(T t)
	{
		node* pNew = new node(t);

		if (this->pTail != NULL)
		{
			pNew->pPrev = this->pTail;
			if (pNew->pPrev)
			{
				pNew->pPrev->pNext = pNew;
			}
			this->pTail = pNew;
		}
		else if (this->pHead == NULL && this->pTail == NULL)
		{
			this->pHead = pNew;
			this->pTail = pNew;
		}
		this->numElements++;
	}

	// pop functions
	template<class T>
	inline void list<T>::pop_front()
	{
		list<T>::iterator it(this->pHead);
		it = this->erase(it);
		this->pHead = it.ptr;
	}
	template<class T>
	inline void list<T>::pop_back()
	{
		list<T>::iterator it(this->pTail);
		it = this->erase(it);
		this->pTail = it.ptr;
	}

	// getters and setters
	template<class T>
	inline const T& list<T>::front() const
	{
		if (!this->empty())
		{
			return pHead->data;
		}
		throw "Error: Calling front on empty list.";
	}
	template<class T>
	inline T& list<T>::front()
	{
		if (!this->empty())
		{
			return pHead->data;
		}
		throw "Error: Calling front on empty list.";
	}
	template<class T>
	inline const T& list<T>::back() const
	{
		if (!this->empty())
		{
			return pTail->data;
		}
		throw "Error: Calling back on empty list.";
	}
	template<class T>
	inline T& list<T>::back()
	{
		if (!this->empty())
		{
			return pTail->data;
		}
		throw "Error: Calling back on empty list.";
	}

	// working with iterators
	template<class T>
	inline typename list<T>::iterator list<T>::begin() const
	{
		return iterator(this->pHead);
	}

	template<class T>
	inline typename list<T>::iterator list<T>::end() const
	{
		return iterator(this->pTail);
	}

	// insert
	template<class T>
	inline typename list<T>::iterator list<T>::find(T t)
	{
		list<T>::iterator it;
		for (it = this->begin(); it != this->end(); ++it)
		{
			if (it.ptr->data == t)
			{
				return it;
			}
		}
		if (this->end() != NULL && it.ptr->data == t)
		{
			return it;
		}
		return NULL;
	}

	template<class T>
	inline typename list<T>::iterator list<T>::erase(iterator it)
	{
		
		if (it != NULL)
		{
			if (it.ptr->pNext == NULL && it.ptr->pPrev == NULL)
			{
				delete it.ptr;
				it.ptr = NULL;
				return it;
			}
			if (it.ptr->pNext == NULL && it.ptr->pPrev != NULL)
			{
				it.ptr->pPrev->pNext = NULL;
				this->pTail = it.ptr->pPrev;
				delete it.ptr;
				it.ptr = this->pTail;
			}
			if (it.ptr->pPrev == NULL && it.ptr->pNext != NULL)
			{
				it.ptr->pNext->pPrev = NULL;
				this->pHead = it.ptr->pNext;
				delete it.ptr;
				it.ptr = this->pHead;
			}
			if (it.ptr->pPrev != NULL && it.ptr->pNext != NULL)
			{
				list<T>::iterator tempIt = it.ptr->pPrev;
				it.ptr->pPrev->pNext = it.ptr->pNext;
				it.ptr->pNext->pPrev = it.ptr->pPrev;
				delete it.ptr;
				it.ptr = tempIt.ptr;
			}
			this->numElements--;
		}
		return it;
	}

	template<class T>
	inline list<T>& list<T>::operator=(const list<T>& rhs)
	{
		this->clear();
		list<T>::iterator it;
		for (it = rhs.begin(); it != rhs.end(); ++it)
		{
			this->push_back(it.ptr->data);
		}
		if (rhs.end() != NULL)
		{
			this->push_back(it.ptr->data);
		}
		return *this;
	}
}
#endif // LIST_H
