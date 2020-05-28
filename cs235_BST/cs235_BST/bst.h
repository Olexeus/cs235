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
		BNode** findLocation(T t);
		int numElements;
		void deleteNode(BNode* toDelete, bool right);
		void deleteBinaryTree(BNode* toDelete);
		void copyBinaryTree(const BNode* src, BNode*& dest) const;
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

		// other functions
		bool isRed() { return this->color == RED; }
		bool isBlack() { return this->color == BLACK; }
		void addLeft(const BNode* pAdd);
		void addRight(const BNode* pAdd);

	public:
		void verifyRB(int depth);
		void verifyBST();
		void balance();
	};



	template <class T>
	class BST<T>::iterator
	{

	public:
		BST<T>::BNode* ptr;
		BST<T>::BNode** pDouble;

	public:
		//friend iterator BST<T>::insert(const T& t);

		// constructors
		iterator() {
			this->ptr = NULL;
			this->pDouble = NULL;
		}

		iterator(BNode* ptr) {
			this->ptr = ptr;
			this->pDouble = NULL;
		}

		/*iterator(BNode** ptr) {
			this->pDouble = ptr;
			this->ptr = *ptr;
		}*/

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

			BST<T>::BNode* pCurrent = this->ptr;

			if (pCurrent->pRight)
			{
				pCurrent = pCurrent->pRight;
				while (pCurrent->pLeft)
				{
					pCurrent = pCurrent->pLeft;
				}
			}
			else if (pCurrent->pRight == NULL && pCurrent->pParent->pLeft == pCurrent)
			{
				pCurrent = pCurrent->pParent;
			}
			else if (pCurrent->pRight == NULL && pCurrent->pParent->pRight == pCurrent)
			{
				while (pCurrent->pParent && pCurrent->pParent->pRight == pCurrent)
				{
					pCurrent = pCurrent->pParent;
				}
				pCurrent = pCurrent->pParent;
			}

			this->ptr = pCurrent;
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

			BST<T>::BNode* pCurrent = this->ptr;

			if (pCurrent->pLeft)
			{
				pCurrent = pCurrent->pLeft;
				while (pCurrent->pRight)
				{
					pCurrent = pCurrent->pRight;
				}
			}
			else if (pCurrent->pLeft == NULL && pCurrent->pParent->pRight == pCurrent)
			{
				pCurrent = pCurrent->pParent;
			}
			else if (pCurrent->pLeft == NULL && pCurrent->pParent->pLeft == pCurrent)
			{
				while (pCurrent->pParent && pCurrent->pParent->pLeft == pCurrent)
				{
					pCurrent = pCurrent->pParent;
				}
				pCurrent = pCurrent->pParent;
			}

			this->ptr = pCurrent;
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
		*this = rhs;
	}

	template<class T>
	inline BST<T>::~BST()
	{
		this->clear();
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
		return this->numElements == 0;
	}



	// iterating through
	template<class T>
	inline typename BST<T>::iterator BST<T>::begin() const
	{
		BST<T>::BNode* pCurrent = this->root;

		while (pCurrent->pLeft)
		{
			pCurrent = pCurrent->pLeft;
		}
		return iterator(pCurrent);
	}
	template<class T>
	inline typename BST<T>::iterator BST<T>::end() const
	{
		return NULL;
	}

	

	// Inserting and finding
	template<class T>
	inline typename BST<T>::iterator BST<T>::insert(const T& t)
	{
		BST<T>::BNode** pCurrent = &this->root;

		while (*pCurrent != NULL/* && (pCurrent->pRight || pCurrent->pLeft)*/)
		{
			// if data found break the loop
			if ((*pCurrent)->data == t)
			{
				break;
			}

			// if data smaller then node - go left
			if (t < (*pCurrent)->data)
			{
				(pCurrent) = &(*pCurrent)->pLeft;
			}
			// if data bigger then node - go right
			else if (t > (*pCurrent)->data)
			{
				(pCurrent) = &(*pCurrent)->pRight;
			}
		}
		BST<T>::BNode* pNew = new BST<T>::BNode(t);
		//*pCurrent = pNew;
		pCurrent = this->findLocation(t);
		*pCurrent = pNew;


		// TODO
		return iterator();
	}

	template<class T>
	inline typename BST<T>::iterator BST<T>::find(T t)
	{
		BST<T>::BNode** pCurrent = &this->root;
		
		while (*pCurrent != NULL/* && (pCurrent->pRight || pCurrent->pLeft)*/)
		{
			// if data found break the loop
			if ((*pCurrent)->data == t)
			{
				break;
			}

			// if data smaller then node - go left
			if (t < (*pCurrent)->data)
			{
				(pCurrent) = &(*pCurrent)->pLeft;
			} 
			// if data bigger then node - go right
			else if (t > (*pCurrent)->data)
			{
				(pCurrent) = &(*pCurrent)->pRight;
			}
		}
		pCurrent = this->findLocation(t);
		return iterator(*pCurrent);
	}

	template<class T>
	inline typename BST<T>::BNode** BST<T>::findLocation(T t)
	{
		BST<T>::BNode** pCurrent = &this->root;

		while (*pCurrent != NULL/* && (pCurrent->pRight || pCurrent->pLeft)*/)
		{
			// if data found break the loop
			if ((*pCurrent)->data == t)
			{
				break;
			}

			// if data smaller then node - go left
			if (t < (*pCurrent)->data)
			{
				(pCurrent) = &(*pCurrent)->pLeft;
			}
			// if data bigger then node - go right
			else if (t > (*pCurrent)->data)
			{
				(pCurrent) = &(*pCurrent)->pRight;
			}
		}

		return (pCurrent);
	}

	template<class T>
	inline BST<T>& BST<T>::operator=(const BST<T>& rhs)
	{
		if (rhs.root == NULL)
		{
			return *this;
		}

		this->clear();

		copyBinaryTree(rhs.root, this->root);

		this->numElements = rhs.numElements;
		return *this;
	}

	template<class T>
	inline void BST<T>::copyBinaryTree(const BNode* src, BNode*& dest) const
	{
		if (src == NULL)
			return;

		dest = new BST<T>::BNode(src->data);

		this->copyBinaryTree(src->pLeft, dest->pLeft);
		if (dest->pLeft != NULL)
		{
			dest->pLeft->pParent = dest;
		}

		this->copyBinaryTree(src->pRight, dest->pRight);
		if (dest->pRight != NULL)
		{
			dest->pRight->pParent = dest;
		}
	}



	// Deleting nodes
	template<class T>
	inline void BST<T>::clear()
	{
		deleteBinaryTree(this->root);
	}

	template<class T>
	inline void BST<T>::deleteNode(BNode* toDelete, bool right)
	{
		// TODO
	}

	template<class T>
	inline void BST<T>::deleteBinaryTree(BNode* toDelete)
	{
		if (toDelete == NULL)
			return;

		this->deleteBinaryTree(toDelete->pLeft);
		this->deleteBinaryTree(toDelete->pRight);

		delete (toDelete);
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
		data = T();			
		pLeft = NULL;		
		pRight = NULL;				
		pParent = NULL;				
		color = RED;
	}

	template<class T>
	inline BST<T>::BNode::BNode(T t)
	{
		data = t;
		pLeft = NULL;
		pRight = NULL;
		pParent = NULL;
		color = RED;
	}

	template<class T>
	inline BST<T>::BNode::~BNode()
	{
		if (pLeft != NULL)
		{
			delete pLeft;
			pLeft = NULL;
		}
		if (pRight != NULL)
		{
			delete pRight;
			pRight = NULL;
		}
		if (pParent != NULL)
		{
			if (pParent->pLeft == this)
			{
				pParent->pLeft = NULL;
				pParent = NULL;
			}
			else if (pParent->pRight == this)
			{
				pParent->pRight = NULL;
				pParent = NULL;
			}
		}
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

	template<class T>
	inline void BST<T>::BNode::addLeft(const BST<T>::BNode* pAdd)
	{
		if (pAdd != NULL)
		{
			pAdd->pParrent = this;
		}
		this->pLeft = pAdd;
	}

	template<class T>
	inline void BST<T>::BNode::addRight(const BST<T>::BNode* pAdd)
	{
		if (pAdd != NULL)
		{
			pAdd->pParrent = this;
		}
		this->pRight = pAdd;
	}
}

#endif // !BST_H
