//Бусыгина Татьяна, ИВТ-22

//    12
//    / \
//   3   14
//  / \  / \
// 2  5 13 16

using namespace std;

#include <iostream>
#include "BinSearchTreeHeader.h"

int main()
{
	BinSearchTree<int> tree;
	tree.insert(12);
	tree.insert(3);
	tree.insert(14);
	tree.insert(2);
	tree.insert(5);
	tree.insert(13);
	tree.insert(16);

	tree.printInorder();
	tree.printPostorder();
	tree.printPreorder();


	//tree.print();

	tree.remove(12);

	tree.print();

	TreeNode<int> root;
	root.data = 12;

	//левая веточка
	TreeNode<int>* left_node = new TreeNode<int>(3);
	TreeNode<int>* left_left_node = new TreeNode<int>(2);
	TreeNode<int>* left_right_node = new TreeNode<int>(5);
	left_node->left = left_left_node;
	left_node->right = left_right_node;

	//правая веточка
	TreeNode<int>* right_node = new TreeNode<int>(14);
	TreeNode<int>* right_left_node = new TreeNode<int>(13);
	TreeNode<int>* right_right_node = new TreeNode<int>(16);
	right_node->left = right_left_node;
	right_node->right = right_right_node;

	root.left = left_node;
	root.right = right_node;

	//printTree(&root, 0);

	cout << root.left->left->data;

	delete left_right_node;
	delete left_left_node;
	delete left_node;
	delete right_right_node;
	delete right_left_node;
	delete right_node;
	root.~TreeNode();
}
