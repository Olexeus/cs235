#ifndef BST_H
#define BST_H

namespace custom {
	enum Color { RED, BLACK };

	template <class T>
	class BST
	{
	public:
		#ifdef UNIT_TESTING
			//friend int ::main(int argc, const char* argv[]);
		#endif // UNIT_TESTING

		// constructors and destructors
		BST();
		BST(const BST<T>& rhs);
		~BST();

		// getters
		int size()		const;
		bool empty()	const;
		void clear();

		// access elements
		class iterator;
		iterator begin() const;
		iterator end() const;

		// special functions
		iterator insert(const T& t);
		iterator find(T t);
		iterator erase(iterator it);
		BST<T>& operator=(const BST<T>& rhs);
	public:
		class BNode;
		BNode* root;
		int numElements;
		void deleteNode(BNode* toDelete, bool right);
		void deleteBinaryTree(BNode* toDelete);
		void copyBinaryTree(BNode* src, BNode* dest);
	};



	template <class T>
	class BST<T>::iterator
	{

	public:
		BST<T>::BNode* ptr;

	public:
		//friend iterator BST<T>::insert(const T& t);

		// constructors
		iterator() {
			this->ptr = NULL;
		}

		iterator(BNode* ptr) {
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
			//(this->ptr->pNext != NULL) ? this->ptr = this->ptr->pNext : this->ptr;
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
			//(this->ptr->pPrev != NULL) ? this->ptr = this->ptr->pPrev : this->ptr;
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
	class BST<T>::BNode
	{
	public:
		T data;
		BNode* pLeft;
		BNode* pRight;
		BNode* pParent;
		bool color;

		BNode();
		BNode(T t);
		~BNode();

	public:
		void verifyRB(int depth);
		void verifyBST();
		void balance();
	};



	// constructors and destructors
	template<class T>
	inline BST<T>::BST()
	{
		this->root = NULL;
		this->numElements = 0;
	}

	template<class T>
	inline BST<T>::BST(const BST<T>& rhs)
	{
		// TODO
	}

	template<class T>
	inline BST<T>::~BST()
	{
		// TODO
	}



	// getters
	template<class T>
	inline int BST<T>::size() const
	{
		return this->numElements;
	}
	template<class T>
	inline bool BST<T>::empty() const
	{
		return this->root == NULL;
	}



	// iterating through
	template<class T>
	inline typename BST<T>::iterator BST<T>::begin() const
	{
		// TODO
		return iterator();
	}
	template<class T>
	inline typename BST<T>::iterator BST<T>::end() const
	{
		// TODO
		return iterator();
	}

	

	// Inserting and finding
	template<class T>
	inline typename BST<T>::iterator BST<T>::insert(const T& t)
	{
		// TODO
		return iterator();
	}

	template<class T>
	inline typename BST<T>::iterator BST<T>::find(T t)
	{
		// TODO
		return iterator();
	}

	template<class T>
	inline BST<T>& BST<T>::operator=(const BST<T>& rhs)
	{
		// TODO
		return *this;
	}

	template<class T>
	inline void BST<T>::copyBinaryTree(BNode* src, BNode* dest)
	{
		// TODO
	}



	// Deleting nodes
	template<class T>
	inline void BST<T>::clear()
	{
		// TODO
	}

	template<class T>
	inline void BST<T>::deleteNode(BNode* toDelete, bool right)
	{
		// TODO
	}

	template<class T>
	inline void BST<T>::deleteBinaryTree(BNode* toDelete)
	{
		// TODO
	}

	template<class T>
	inline typename BST<T>::iterator BST<T>::erase(iterator it)
	{
		// TODO
		return iterator();
	}



	// BNode constructors and destructors
	template<class T>
	inline BST<T>::BNode::BNode()
	{
		// TODO
	}

	template<class T>
	inline BST<T>::BNode::BNode(T t)
	{
		// TODO
	}

	template<class T>
	inline BST<T>::BNode::~BNode()
	{
		// TODO
	}

	// BNode special functions
	template<class T>
	inline void BST<T>::BNode::verifyRB(int depth)
	{
		// TODO
	}

	template<class T>
	inline void BST<T>::BNode::verifyBST()
	{
		// TODO
	}

	template<class T>
	inline void BST<T>::BNode::balance()
	{
		// TODO
	}
}

#endif // !BST_H
