#ifndef _BST_H
#define _BST_H
#define default_threshold_value 1
#include <sstream>
#include <iostream>
#include <string>
#include <list>

namespace cop4530
{
using namespace std;


template <typename T>
class BST
{
public:
	struct BSTNode
	{
		T element;
		int search;
		BSTNode* left;
		BSTNode* right;
		BSTNode(const T& e, BSTNode* L, BSTNode* R, int S = 0)
			: element{ e }, left{ L }, right{ R }, search { S } {}
	};
	BST(int th=default_threshold_value);
	BST(const string input, int th=default_threshold_value);
	BST(const BST&);
	BST(BST&&);
	~BST();
	void buildFromInputString(const string input);
	const BST& operator= (const BST&);
	const BST& operator= (BST&&);
	bool empty();
	void printInOrder() const;
	void printLevelOrder() const;
	int numOfNodes() const;
	int height() const;
	void makeEmpty(); //
	void insert(const T& v);
	void remove(const T& v);
	bool contains(const T& v);
	

private:
	void printInOrder(BSTNode* t) const;
	void printLevelOrder(BSTNode* t) const;
	void makeEmpty(BSTNode* &t);
	void insert(const T& v, BSTNode*& t);
	void insert(T&& v, BSTNode* &t);
	void remove(const T& v, BSTNode*& t);
	bool contains(const T& v, BSTNode*& t, BSTNode*& parent);
	int numOfNodes(BSTNode* t) const;
	int height(BSTNode* t) const;
	BSTNode* clone(BSTNode* t) const;
	void rotateLeftChild(BSTNode*& t);
	void rotateRightChild(BSTNode*& t);
	BSTNode* root;
	int rotate_threshold_value;
};

#include "bst.hpp"
}


#endif