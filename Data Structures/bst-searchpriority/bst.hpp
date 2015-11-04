template<typename T>
BST<T>::BST(int th)
{
	rotate_threshold_value = th;
	root = nullptr;
}
template<typename T>
BST<T>::BST(const string input, int th)
{
	rotate_threshold_value = th;
	root = nullptr;
	buildFromInputString(input);
}
template<typename T>
void BST<T>::buildFromInputString(const string input)
{
	stringstream nodestream;
	makeEmpty(root);
	nodestream.str(input);
	while (nodestream)
	{
		T nodeVal;
		nodestream >> nodeVal;
		insert(nodeVal);
		nodestream.ignore();
	}
}
template<typename T>
void BST<T>::insert(const T& v)
{
	insert(v, root);
}

template<typename T>
void BST<T>::insert(const T& v, BSTNode*& t)
{
	if (t == nullptr)
	{
		t = new BSTNode{v, nullptr, nullptr};
	}
	else if ( v < t->element)
	{
		insert(v, t->left);
	}
	else if ( v > t->element)
	{
		insert(v, t->right);
	}
}

template<typename T>
BST<T>::BST(BST&& tree)
{
	rotate_threshold_value = tree.rotate_threshold_value;
	root = move(tree.root);
	tree.root = nullptr;
}

template<typename T>
BST<T>::BST(const BST& tree)
{
	rotate_threshold_value = tree.rotate_threshold_value;
	root = clone(tree.root);
}

template<typename T>
BST<T>::~BST()
{
	makeEmpty();
}

template<typename T>
const BST<T>& BST<T>::operator= (const BST& tree)
{
	if (this != &tree)
	{
		makeEmpty();		
	}
	root = clone(tree.root);
	rotate_threshold_value = tree.rotate_threshold_value;
	return *this;
}

template<typename T>
const BST<T>& BST<T>::operator= (BST&& tree)
{
	makeEmpty();		
	root = move(tree.root);
	tree.root = nullptr;
	rotate_threshold_value = tree.rotate_threshold_value;
	return *this;
}

template<typename T>
bool BST<T>::empty()
{
	return root == nullptr;
}

template<typename T>
void BST<T>::printInOrder() const
{
	printInOrder(root);
	cout << endl;
}

template<typename T>
void BST<T>::printInOrder(BSTNode* t) const
{
	if (t == nullptr)
	{
		return;
	}
	printInOrder(t->left);
	cout << t->element << " ";
	printInOrder(t->right);
}

template<typename T>
void BST<T>::printLevelOrder() const
{
	printLevelOrder(root);
	cout << endl;
}

template<typename T>
void BST<T>::printLevelOrder(BSTNode* t) const
{
	if (t == nullptr)
	{
		return;
	}
	list<BSTNode*> nodeList; 
	nodeList.push_back(t);
	while (!nodeList.empty())
	{

		BSTNode* next = nodeList.front();
		cout << next->element << " ";			
		if (next->left != nullptr)
		{
			nodeList.push_back(next->left);
		}
		if (next->right != nullptr)
		{
			nodeList.push_back(next->right);
		}
		nodeList.pop_front();
	}

}

template<typename T>
int BST<T>::numOfNodes() const
{
	return numOfNodes(root);
}

template<typename T>
void BST<T>::makeEmpty()
{
	makeEmpty(root);
}

template<typename T>
void BST<T>::remove(const T& v)
{
	remove(v, root);
}

template<typename T>
bool BST<T>::contains(const T& v)
{
	return contains(v, root, root);
}

template<typename T>
bool BST<T>::contains(const T& v, BSTNode* &t, BSTNode*& parent)
{
	if (t == nullptr)
	{
		return false;
	}
	if (v == t->element)
	{
		t->search++;
		if (t->search == rotate_threshold_value)
		{
			t->search = 0;
			if (parent->left == t)
			{
				rotateLeftChild(parent);
			}	
			else if (parent->right == t)
			{
				rotateRightChild(parent);
			}
		}
		return true;
	}

	if (v < t->element)
	{
		return contains(v, t->left, t);

	}
	else
	{
		return contains(v, t->right, t);
	}

}
template<typename T>
void BST<T>::makeEmpty(BSTNode* &t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = nullptr;
	}

}

template<typename T>
void BST<T>::remove(const T& v, BSTNode*& t)
{
	BSTNode* temp = nullptr;
	//not found
	if( t == nullptr )
	{
		return; 
	}
	if( v < t->element )
	{
		remove( v, t->left );
	}
	else if(v > t->element)
	{
		remove( v, t->right );
	}
	//has no children
	else if( t->left == nullptr && t->right == nullptr ) 
	{
		temp = t;
		t = nullptr;
		delete temp;
	}
	//has both children
	else if (t->right != nullptr && t->left != nullptr)
	{
		temp = t->right;
		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		t->element = temp->element;
		t->search = temp->search;
		remove(t->element, t->right);
	}
	// 1 child
	else 
	{
		t->left != nullptr ? temp = t->left : temp = t->right;
		delete t;
		t = temp;
	}
}

template<typename T>
void BST<T>::rotateLeftChild(BSTNode*& p)
{
	BSTNode* t = p->left; 
	p->left = t->right; 
	t->right = p; 
	p = t;
}

template<typename T>
void BST<T>::rotateRightChild(BSTNode*& t)
{
	BSTNode* temp = t->right;
	t->right = temp->left;
	temp->left = t;
	t = temp;
}


template<typename T>
int BST<T>::numOfNodes(BSTNode* t) const
{
	if (t == nullptr)
	{
		return 0;
	}
	return 1 + numOfNodes(t->left) + numOfNodes(t->right);
}

template<typename T>
int BST<T>::height() const
{
	return height(root);
}

template<typename T>
int BST<T>::height(BSTNode* t) const
{
	if (t == nullptr)
	{
		return -1;		
	}
	return 1 + max(height(t->left), height(t->right));
}

template<typename T>
typename BST<T>::BSTNode* BST<T>::clone(BSTNode* t) const
{
	if (t == nullptr)
	{
		return nullptr;
	}
	return new BSTNode{t->element, clone(t->left), clone(t->right), t->search};
}
