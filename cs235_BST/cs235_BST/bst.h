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
		BNode** findParent(T t);
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
		bool isRed()		{ return this->color == RED; }
		bool isBlack()		{ return this->color == BLACK; }
		void setRed()		{ this->color = RED; }
		void setBlack()	{ this->color = BLACK; }
		void addLeft(BNode* pAdd);
		void addRight(BNode* pAdd);

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
				throw "Error: dereferencing null node.";
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
				throw "Error: incrementing null node.";

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
				throw "Error: decrementing null node.";

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

		while (pCurrent != NULL && pCurrent->pLeft != NULL)
		{
			pCurrent = pCurrent->pLeft;
		}
		return iterator(pCurrent);
	}
	template<class T>
	inline typename BST<T>::iterator BST<T>::end() const
	{
		BST<T>::BNode* pCurrent = this->root;

		while (pCurrent != NULL && pCurrent->pRight != NULL)
		{
			pCurrent = pCurrent->pRight;
		}
		return iterator(pCurrent);
	}

	

	// Inserting and finding
	template<class T>
	inline typename BST<T>::iterator BST<T>::insert(const T& t)
	{
		// we need to change the value of treePointer to the node
		// at the location at which this treePointer to the node is stored in the tree
		// therefore, we store the pointer to the treePointer in the
		// doublePointer and then we change the value of the treePointer to point to the new node
		// by accessing from the doublePointer the location at which 
		// treePointer is stored and changing its value

		// edit: we actually sent the doublePointer of parent of treePointer
		// to be able to set the parent for the treePointer node

		BST<T>::BNode** pTemporary = this->findParent(t);

		// use *pTemporary != NULL && to check if root is NULL
		if (*pTemporary != NULL && (*pTemporary)->data == t)
		{ // return if element exists
			return iterator(*pTemporary);
		}

		// if data smaller then node - go left
		if (*pTemporary != NULL && t < (*pTemporary)->data)
		{
			(*pTemporary)->pLeft = new BST<T>::BNode(t);
			(*pTemporary)->pLeft->pParent = (*pTemporary);
			(pTemporary) = &(*pTemporary)->pLeft;
		}
		// if data bigger then node - go right
		else if (*pTemporary != NULL && t > (*pTemporary)->data)
		{
			(*pTemporary)->pRight = new BST<T>::BNode(t);
			(*pTemporary)->pRight->pParent = (*pTemporary);
			(pTemporary) = &(*pTemporary)->pRight;
		} 
		// if root is NULL
		else
		{
			(*pTemporary) = new BST<T>::BNode(t);
		}

		this->numElements++;
		BST<T>::BNode* pNew				= *pTemporary;
		BST<T>::BNode* pParent			= pNew->pParent;
		BST<T>::BNode* pSiblingLeft	= NULL;
		BST<T>::BNode* pSiblingRight	= NULL;
		BST<T>::BNode* pGparent			= NULL;
		BST<T>::BNode* pAuntLeft		= NULL;
		BST<T>::BNode* pAuntRight		= NULL;
		if (pParent != NULL)
		{
			pSiblingLeft = pNew->pParent->pLeft;
			pSiblingRight = pNew->pParent->pLeft;
			pGparent = pNew->pParent->pParent;
			if (pGparent != NULL)
			{
				pAuntLeft = pNew->pParent->pParent->pLeft;
				pAuntRight = pNew->pParent->pParent->pRight;
			}
		}


		// No parent (1)
		if (pParent == NULL)
		{
			pNew->setBlack();
		}
		// Parent is black (2)
		else if (pParent->isBlack())
		{
			// Do nothing I guess
		}
		else if (pParent->isRed() && pGparent->isBlack()) // pGparent must exist if pParent is red
		{
			// Right Child
			if (pSiblingRight == pNew)
			{
				if (pParent == pAuntRight)
				{
					// Parent and aunt are red (3)
					if (pAuntLeft != NULL && pAuntLeft->isRed())
					{
						// Right child. Right Parent. Red Aunt
						// recolor
						// TODO
					}
					else if (pAuntLeft == NULL || pAuntLeft->isBlack())
					{ // didn't count for black sibling. IDK whether i have to
						// Right child. Right Parent. No Aunt
						// Rotate left. (4b)
						pParent->addLeft(pGparent);
						pGparent->addRight(pSiblingLeft);
						pParent->pParent = pGparent->pParent;
						pGparent->pParent = pParent;

						pParent->setBlack();
						pGparent->setRed();
					}
				}
				else if (pParent == pAuntLeft)
				{
					// Parent and aunt are red (3)
					if (pAuntRight != NULL && pAuntRight->isRed())
					{
						// Right child. Left Parent. Red Aunt
						// recolor
						// TODO
					}
					else if (pAuntRight == NULL || pAuntRight->isBlack())
					{
						// Right child. Left Parent. No Aunt
						// Swap. (4c)
						pParent->addRight(pNew->pLeft);
						pGparent->addLeft(pNew->pRight);

						if (pGparent->pParent == NULL)
						{
							pNew->pParent = NULL;
						}
						else if (pGparent->pParent->pRight = pGparent)
						{
							pGparent->pParent->pRight = pNew;
						}
						else if (pGparent->pParent->pLeft = pGparent)
						{
							pGparent->pParent->pLeft = pNew;
						}

						pNew->addLeft(pParent);
						pNew->addRight(pGparent);

						pNew->setBlack();
						pGparent->setRed();
					}
				}
			}
			// Left Child
			else if (pSiblingLeft == pNew)
			{
				if (pParent == pAuntRight)
				{
					// Parent and aunt are red (3)
					if (pAuntLeft != NULL && pAuntLeft->isRed())
					{
						// Left child. Right Parent. Red Aunt
						// recolor
						// TODO
					}
					else if (pAuntLeft == NULL || pAuntLeft->isBlack())
					{ // didn't count for black sibling. IDK whether i have to
						// Left child. Right Parent. No Aunt
						// Rotate left. (4a)
						pParent->addRight(pGparent);
						pGparent->addLeft(pSiblingRight);
						pParent->pParent = pGparent->pParent;
						pGparent->pParent = pParent;

						pParent->setBlack();
						pGparent->setRed();
					}
				}
				else if (pParent == pAuntLeft)
				{
					// Parent and aunt are red (3)
					if (pAuntRight != NULL && pAuntRight->isRed())
					{
						// Left child. Left Parent. Red Aunt
						// recolor
						// TODO
					}
					else if (pAuntRight == NULL || pAuntRight->isBlack())
					{
						// Left child. Left Parent. No Aunt
						// Swap. (4d)
						pParent->addLeft(pNew->pRight);
						pGparent->addRight(pNew->pLeft);

						if (pGparent->pParent == NULL)
						{
							pNew->pParent = NULL;
						}
						else if (pGparent->pParent->pRight = pGparent)
						{
							pGparent->pParent->pRight = pNew;
						}
						else if (pGparent->pParent->pLeft = pGparent)
						{
							pGparent->pParent->pLeft = pNew;
						}

						pNew->addLeft(pGparent);
						pNew->addRight(pParent);

						pNew->setBlack();
						pGparent->setRed();
					}
				}
			}
		}

		return iterator();
	}

	template<class T>
	inline typename BST<T>::iterator BST<T>::find(T t)
	{
		BST<T>::BNode** pCurrent = this->findParent(t);
		// use *pCurrent != NULL to check when root is NULL
		if (*pCurrent != NULL && (*pCurrent)->data != t)
		{
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
		return iterator(*pCurrent);
	}

	template<class T>
	inline typename BST<T>::BNode** BST<T>::findParent(T t)
	{
		BST<T>::BNode** pCurrent = &this->root;
		BST<T>::BNode** pPrev = pCurrent;

		while (*pCurrent != NULL/* && (pCurrent->pRight || pCurrent->pLeft)*/)
		{
			// if data found break the loop
			if ((*pCurrent)->data == t)
			{
				pPrev = pCurrent;
				break;
			}

			// if data smaller then node - go left
			if (t < (*pCurrent)->data)
			{
				pPrev = pCurrent;
				(pCurrent) = &(*pCurrent)->pLeft;
			}
			// if data bigger then node - go right
			else if (t > (*pCurrent)->data)
			{
				pPrev = pCurrent;
				(pCurrent) = &(*pCurrent)->pRight;
			}
		}

		return (pPrev);
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
	inline void BST<T>::BNode::addLeft(BST<T>::BNode* pAdd)
	{
		if (pAdd != NULL)
		{
			pAdd->pParent = this;
		}
		this->pLeft = pAdd;
	}

	template<class T>
	inline void BST<T>::BNode::addRight(BST<T>::BNode* pAdd)
	{
		if (pAdd != NULL)
		{
			pAdd->pParent = this;
		}
		this->pRight = pAdd;
	}
}

#endif // !BST_H
