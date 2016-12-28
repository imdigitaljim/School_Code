#pragma once
#include <list>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "inversion.h"
#define INT_MAX 2147483647

using namespace std;

//this is was found to be the optimum size for the tree/queries
//through program profiling makes an average tree size of about 20-22
const int max_tree_size = 32;

//forward declarations
class MTree;
class MTreeNode;
struct PrintMTreeNode;
struct PrintMTree;
//for easy use, less overhead
typedef struct PrintMTree PrintMTree;
typedef struct PrintMTreeNode PrintMTreeNode;

//heap data structures (externed in main and query)
vector<MTreeNode*> connectors;
vector<MTree*> trees;

//the serialization file pointer
FILE* inputFile;

//tree building structures
class MTreeNode
{
	friend class MTree;
	friend struct PrintMTree;
	friend struct PrintMTreeNode;
	friend void SetPrintMTree(MTree* m, PrintMTree& t) ;
	public:
		MTreeNode(): treeSelf(nullptr), treeChild(nullptr), distance_to_parent(0), radius_cover(0), treeChildId(-1){}
		MTreeNode(char* ary, int id): treeSelf(nullptr), treeChild(nullptr), distance_to_parent(0), radius_cover(0), treeChildId(-1)
		{
			for (int i = 0; i < 32; i++)
			{
				content[i] = ary[i];
			}
			assigned_id = id;
		}
	private:
		char content[32];
		MTree * treeSelf, *treeChild;
		int distance_to_parent, radius_cover, treeChildId, assigned_id;
};

class MTree
{
	friend void SetPrintMTree(MTree* m, PrintMTree& t);
	friend class MTreeNode;
	friend struct PrintMTree;
	friend struct PrintMTreeNode;
	public:
		explicit MTree(bool setRoot = false) : fileId(-1), parent(nullptr), isRoot(setRoot), isLeaf(true)
		{
			srand(time(nullptr));
			 if (setRoot)
			 {
				 root = this;
			 }
		}
		static MTree* root;
		void AddNode(MTreeNode* newNode);
		void Query(const char* n);
		void Serialize();
		
	private:
		void FindClosestId(const char* m, int currentTreeId, vector<pair<int, int>>& result, int& cover, int distance = 0);
		
		void Finalize();
		PrintMTree GetTreeFromFileById(int index);
		
		void SetIds(MTree* t);
		int fileId;
		MTreeNode* parent;
		bool isRoot, isLeaf;
		vector<MTreeNode*> nodes;
		void SplitTree(MTreeNode* newNode);
		void UpdateSplitNode(MTreeNode* oldNode, MTreeNode* newNode);
		void MoveToTree(MTreeNode* child_node, MTreeNode* parent_node, MTree* containingTree, vector<MTreeNode*>& tree, int distance);
		void SplitRoot(MTreeNode* n1, MTreeNode* n2);
		void UpdateParent(MTreeNode* n1, MTreeNode* n2);
};

//serialization data structures *essentially the same as the others just minimized for writing
struct PrintMTreeNode
{
	char content[32];
	int assigned_id, distance_to_parent, radius_cover, treeChildId;
};

struct PrintMTree
{
	bool isRoot, isLeaf;
	int fileId;
	char current;
	PrintMTreeNode treeNodes[max_tree_size];		
};

//helper function to set tree and not add extra size in the print class
void SetPrintMTree(MTree* m, PrintMTree& t)  
{
	t.isRoot = m->isRoot;
	t.isLeaf = m->isLeaf; 
	t.fileId = m->fileId;
	t.current = m->nodes.size();
	for (int i = 0; i < t.current; i++)
	{
		t.treeNodes[i].distance_to_parent = m->nodes[i]->distance_to_parent;
		t.treeNodes[i].treeChildId = m->nodes[i]->treeChildId;
		t.treeNodes[i].radius_cover = m->nodes[i]->radius_cover;
		t.treeNodes[i].assigned_id = m->nodes[i]->assigned_id;			
		for (int j = 0; j < 32; j++)
		{
			t.treeNodes[i].content[j] = m->nodes[i]->content[j];
		}
	}
}

MTree* MTree::root = nullptr;

//this extracts a tree by index from the file (1 tree at a time)
PrintMTree MTree::GetTreeFromFileById(int index)
{
	PrintMTree result;
	fseek(inputFile, index * sizeof(PrintMTree), SEEK_SET);
	int readAmount = fread((char*)&result, sizeof(char), sizeof(PrintMTree), inputFile);
	if (readAmount != sizeof(PrintMTree))
	{
		cerr << "Error: Did not read tree from file correctly" << endl;
		exit(3);
	}
	return result;
}

void MTree::Query(const char* node_to_find)
{
	vector<pair<int, int>> best_ids; // <treeid, nodeid>
	int cover = 800; //large cover (in order to establish a min)
	FindClosestId(node_to_find, 0, best_ids, cover); //performs the query
	int line, len = best_ids.size();
	PrintMTree current;
	cout << "line: ";
	for (int i = 0; i < len; i++)
	{
		current = GetTreeFromFileById(best_ids[i].first); //get the tree that was found
		line = current.treeNodes[best_ids[i].second].assigned_id; //extract the line number
		cout << line; 
		if (i + 1 < len)
		{
			cout << ", ";
		}
	}
	cout << endl << "+++++++++++++++++++++++" << endl;
}

//recursive function to navigate the mtree
void MTree::FindClosestId(const char* node_to_find, int currentTreeId, vector<pair<int, int>>& result, int& cover, int distance)
{
	PrintMTree currentTree = GetTreeFromFileById(currentTreeId); //open the tree
	int len = currentTree.current;
	if (currentTree.isLeaf)
	{
		for (int i = 0; i < len; i++) //check out the nodes in the tree
		{
			//if the inversion distance is the best/match so far on any recursion level (by reference cover)
			if (abs(distance - currentTree.treeNodes[i].distance_to_parent) <= cover)
			{
				int new_distance = calculate_node_distance(node_to_find, currentTree.treeNodes[i].content);
				//if this tree has a matching or better inversion, keep it (multiple matches)
				if (new_distance <= cover)
				{
					if (new_distance < cover)
					{
						//clear it if this is the NEW minimum (best)
						result.clear();
						cover = new_distance;
					}
					result.push_back(make_pair(currentTree.fileId, i));
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			//find the correct path(s) of the tree to take based on their radius cover to specify what range that tree covers
			if (abs(distance - currentTree.treeNodes[i].distance_to_parent) <= cover + currentTree.treeNodes[i].radius_cover)
			{
				int new_distance = calculate_node_distance(node_to_find, currentTree.treeNodes[i].content);
				if (new_distance <= cover + currentTree.treeNodes[i].radius_cover)
				{			
					FindClosestId(node_to_find, currentTree.treeNodes[i].treeChildId,result, cover, new_distance);
				}
			}
		}
	}
}

void MTree::Serialize()
{
	Finalize();
	list<MTree*> bfs;
	bfs.push_back(root);
	int len;
	ofstream os("data.mtree", std::ofstream::binary);
	PrintMTree filePrinter;
	MTree* next;
	//bfs traverse/print the tree to file
	while (!bfs.empty())
	{	
		next = bfs.front();
		SetPrintMTree(next, filePrinter);	
		os.write((char*)&filePrinter, sizeof(PrintMTree));
		len = next->nodes.size();
		MTreeNode* current;
		for (int i = 0; i < len; i++)
		{
			current= next->nodes[i];
			if (current->treeChild != nullptr)
			{
				bfs.push_back(current->treeChild);
			}
		
		}
		bfs.pop_front();
	}
	os.close();
}

void MTree::Finalize() 
//this function will set all the ids of the trees; 
//performs the same order and can be reliably referenced)
{
	cout << "finalizing..." << endl;
	list<MTree*> bfs;
	bfs.push_back(root);
	int len, count = 0;
	BTimer benchmark;
	benchmark.Start();
	MTree* next;
	//bfs traverse set ids of trees
	while (!bfs.empty())
	{	
		next = bfs.front();
		next->fileId = count++;	
		len = next->nodes.size();
		MTreeNode* current;
		for (int i = 0; i < len; i++)
		{
			current= next->nodes[i];
			if (current->treeChild != nullptr)
			{
				bfs.push_back(current->treeChild);
			}
		}
		bfs.pop_front();
	}
	SetIds(root); 
	cout << "finalized!" << endl;
	TIME(benchmark.GetDeltaTime());
}

void MTree::SetIds(MTree* t) 
//this back-sets id references (setting ids of parents) 
{
	int len = t->nodes.size();
	for(int i = 0; i < len; i++)
	{
		if (t->nodes[i]->treeChild != nullptr)
		{
			t->nodes[i]->treeChildId = t->nodes[i]->treeChild->fileId;
			SetIds(t->nodes[i]->treeChild);
		}
		
	}
}


void MTree::SplitTree(MTreeNode* newNode) //split tree to support newNodes
{
	nodes.push_back(newNode); //for heap cleanup
	MTree* newTree = new MTree();
	trees.push_back(newTree); //for heap cleanup
	newTree->isLeaf = isLeaf; //if calling tree was a leaf, this is now a leaf (and vice versa) 

	vector<MTreeNode*> tree1, tree2; //temp/new tree data

	//this following randomization much like quick sort allows for better picks regardless of sortedness etc.
	int fpos = rand() % nodes.size(); 
	MTreeNode* node1 = nodes[fpos], *node2 = nullptr;
	int pos = rand() % nodes.size();

	MTreeNode* tempNode = nodes[pos];
	//make sure the random indexes are unique
	if (node1 != tempNode) 
	{
		node2 = tempNode;
	}
	else
	{
		pos = pos > 0 ? pos - 1 : pos + 1;
		node2 = nodes[pos];
	}

	//adding new (duplicated) connector nodes...
	node1 = new MTreeNode(node1->content, node1->assigned_id);
	node2 = new MTreeNode(node2->content, node2->assigned_id);
	connectors.push_back(node1);
	connectors.push_back(node2);

	//splitting tree nodes between the trees based on the best distance matches
	int len = nodes.size();
	MTreeNode* current_node;
	for (int i = 0; i < len; i++)
	{
		current_node = nodes[i];
		int node_distance1 = calculate_node_distance(current_node->content, node1->content);
		int node_distance2 = calculate_node_distance(current_node->content, node2->content);
		if (node_distance1 < node_distance2) // if node[i] is closer to split-node1
		{
			MoveToTree(current_node, node1, this, tree1, node_distance1);
		}
		else
		{
			MoveToTree(current_node, node2, newTree, tree2, node_distance2);
		}
	}

	//set new node lists for trees
	nodes = tree1;
	newTree->nodes = tree2;

	node1->treeChild = this;
	node2->treeChild = newTree;

	//special case for if calling object was root 
	if (isRoot)
	{
		SplitRoot(node1, node2);
	}
	else
	{
		UpdateParent(node1, node2);
	}
	isRoot = false;
	parent = node1;
	newTree->parent = node2;
}

void MTree::UpdateParent(MTreeNode* n1, MTreeNode* n2)
//this updates the parent's information about the child, and some child info about the parent
{
	MTree* parentTree = parent->treeSelf;
	parentTree->UpdateSplitNode(parent, n1); //update the connected node in the parent
	n1->treeSelf = parentTree;
	if (!parentTree->isRoot) //if not root node
	{
		n1->distance_to_parent = calculate_node_distance(n1->content, parentTree->parent->content);;
	}
	if (parent->treeSelf->nodes.size() >= max_tree_size)
	{
		parent->treeSelf->SplitTree(n2); //split tree to support n2
	}
	else
	{
		parentTree->nodes.push_back(n2);
		n2->treeSelf = parentTree;
		if (!parentTree->isRoot)
		{
			n2->distance_to_parent = calculate_node_distance(n2->content, parentTree->parent->content);
		}
	}
}

void MTree::SplitRoot(MTreeNode* n1, MTreeNode* n2)
{
	MTree* newRoot = new MTree();
	trees.push_back(newRoot);
	root = newRoot;
	root->nodes.push_back(n1);
	root->nodes.push_back(n2);
	root->isLeaf = false;
	root->isRoot = true;
	n1->treeSelf = n2->treeSelf = root;
}

void MTree::MoveToTree(MTreeNode* child_node, MTreeNode* parent_node, MTree* containingTree, vector<MTreeNode*>& tree, int distance)
//moves the node to this tree
{
	if (distance > parent_node->radius_cover){ // if node[i]'s distance to split-node1 is farther than the split-node1 radius_cover
		parent_node->radius_cover = distance;
	}
	child_node->distance_to_parent = distance; // update info about node
	child_node->treeSelf = containingTree;  // update info about node
	tree.push_back(child_node);  // add to new tree list for split-node1
}


void MTree::UpdateSplitNode(MTreeNode* oldNode, MTreeNode* newNode)
{
	int len = nodes.size();
	for (int i = 0; i < len; i++)
	{
		if (nodes[i] == oldNode)
		{
			nodes[i] = newNode;
			return;
		}
	}

}

/*
this function adds the node to the proper portion of the tree, performs a split if at capacity
otherwise uses basic min-algorithm functionality when setting distances
*/
void MTree::AddNode(MTreeNode* newNode)
{
	int len = nodes.size();
	if (isLeaf)
	{
		if (len < max_tree_size)
		{
			nodes.push_back(newNode);
			newNode->treeSelf = this;
			if (!isRoot) {
				newNode->distance_to_parent = calculate_node_distance(newNode->content, parent->content);
			}
		}
		else
		{
			SplitTree(newNode);
		}
	}
	else
	{
		int min_distance = INT_MAX, node_distance = 0;
		MTreeNode* current_best_node = nullptr;
		for (int i = 0; i < len; i++)
		{
			node_distance = calculate_node_distance(newNode->content, nodes[i]->content);
			if (node_distance < min_distance)
			{
				//get minimum distance in the tree
				min_distance = node_distance;
				current_best_node = nodes[i];
			}
		}
		if (min_distance > current_best_node->radius_cover)
		{
			//update covering distance
			current_best_node->radius_cover = min_distance;
		}
		current_best_node->treeChild->AddNode(newNode);
	}
}



