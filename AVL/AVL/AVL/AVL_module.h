//�������� �������, ���-22

#include <iostream>
#include "BinSearchTreeHeader.h"
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/// <summary>
/// ��������� ����� ���� AVL ������, ����������� �� ������ TreeNode
/// </summary>
template <typename Type>
class AVLTreeNode : public TreeNode<Type> {
public:
	int balance; //����������� ������� ���� - ������� ����� �������� ������� � ������ �����������
	
	/// <summary>
	/// ����������� �� ���������
	/// </summary>
	AVLTreeNode(): TreeNode<Type>(), balance(0) {}

	/// <summary>
	/// ����������� � �������
	/// </summary>
	/// <param name="data">������</param>
	AVLTreeNode(const Type& data) : TreeNode<Type>(data), balance(0) {}

	/// <summary>
	/// ����������� � ������� � ����������� �� ���������� � ������� ����
	/// </summary>
	/// <param name="data">������</param>
	/// <param name="left">��������� �� ���������� ����</param>
	/// <param name="right">��������� �� ��������� ����</param>
	AVLTreeNode(const Type& data, TreeNode<Type>* left, TreeNode<Type>* right) : TreeNode<Type>(data, left, right), balance(0) {}

	///�����������!!!!!

	//��������������� ��������� �� (�� �����) TreeNode � ��������� �� AVLTreeNode
	AVLTreeNode<Type>* getLeft() {
		return static_cast<AVLTreeNode<Type>*>(this->left);
	}

	//��������������� ��������� �� (�� ������) TreeNode � ��������� �� AVLTreeNode
	AVLTreeNode<Type>* getRight() {
		return static_cast<AVLTreeNode<Type>*>(this->right);
	}

};

/// <summary>
/// ����� AVL ������
/// </summary>
/// ���-������ � ���������������� �������� ������ ������, � ������� �������������� ��������� ��������: 
/// ��� ������ ��� ������� ������ � ���� ����������� ����������� �� ����� ��� �� 1
template <typename Type>
class AVLTree {
private:
	AVLTreeNode<Type>* root; //��������� �� ������ ������

	/// <summary>
	/// ���������� �������
	/// </summary>
	/// <param name="node"></param>
	void newBalance(AVLTreeNode<Type>* node) {
		if (node == nullptr)
		{
			return;
		}

		size_t left_heigth = getHeight(node->getLeft());
		size_t right_heigth = getHeight(node->getRight());
		node->balance = left_heigth - right_heigth;
	}

	/// <summary>
	/// ��������� ������
	/// </summary>
	/// <param name="node"></param>
	/// <returns>������ ������</returns>
	size_t getHeight(AVLTreeNode<Type>* node) {
		if (node == nullptr) {
			return 0;
		}
		return 1 + max(getHeight(node->getLeft()), getHeight(node->getRight()));

	}

	/// <summary>
	/// ����� ������� ������
	/// </summary>
	/// <param name="node">����, ������ �������� ����� ��������� �������</param>
	/// <returns>��������� ������</returns>
	AVLTreeNode<Type>* rotateLeft(AVLTreeNode<Type>* node) {
		AVLTreeNode<Type>* temp = node->getRight(); //�������� ������� ������� ����
		node->right = temp->getLeft(); //����� ��������� temp ���������� ������ ���������� node
		temp->left = node; //���� node ���������� ����� ���������� temp

		newBalance(node);
		newBalance(temp);

		return temp;
	}

	/// <summary>
	/// ������ ������� ������
	/// </summary>
	/// <param name="node">����, ������ �������� ����� ��������� �������</param>
	/// <returns>��������� ������</returns>
	AVLTreeNode<Type>* rotateRight(AVLTreeNode<Type>* node) {
		AVLTreeNode<Type>* temp = node->getLeft();
		node->left = temp->getRight();
		temp->right = node;

		newBalance(node);
		newBalance(temp);

		return temp;
	}

	/// <summary>
	/// ������������ ������
	/// </summary>
	/// <param name="node"></param>
	/// <returns></returns>
	AVLTreeNode<Type>* balanceTree(AVLTreeNode<Type>* node) {
		if (node == nullptr) {
			return nullptr;
		}

		newBalance(node);

		//���� ������ ������ 1, �� ������ ������ �������
		if (node->balance > 1) {
			if (getHeight(node->getLeft()->getLeft()) >= getHeight(node->getLeft()->getRight())) {
				//��������� ������ �������
				node = rotateRight(node); //��������� �������
			}
			else {
				//������� ������ �������
				node->left = rotateLeft(node->getLeft());
				node = rotateRight(node);
			}
		}
		else if (node->balance < -1) {
			if (getHeight(node->getRight()->getRight()) >= getHeight(node->getRight()->getLeft())) {
				//��������� ����� �������
				node = rotateLeft(node);
			}
			else {
				//������� ����� �������
				node->right = rotateRight(node->getRight());
				node = rotateLeft(node);
			}
		}

		return node;
	}

	/// <summary>
	/// ������� ���� � ������
	/// </summary>
	/// <param name="node"></param>
	/// <param name="data">������ ����, ������� ���������</param>
	/// <returns></returns>
	AVLTreeNode<Type>* insertRecoursive(AVLTreeNode<Type>* node, const Type& data) {
		//���� ����� ����� �����, ���� ���� �������� ����
		if (node == nullptr) {
			return new AVLTreeNode<Type>(data);
		}

		if (data < node->data) {
			node->left = insertRecoursive(node->getLeft(), data);
		}
		else if (data > node->data) {
			node->right = insertRecoursive(node->getRight(), data);
		}

		return balanceTree(node);
	}

	/// <summary>
	/// �������� ���� �� ������
	/// </summary>
	/// <param name="node"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	AVLTreeNode<Type>* removeRecoursive(AVLTreeNode<Type>* node, const Type& data) {
		
		if (node == nullptr) {
			return nullptr;
		}

		if (data < node->data) {
			node->left = removeRecoursive(node->getLeft(), data);
		}
		else if (data > node->data) {
			node->right = removeRecoursive(node->getRight(), data);
		}
		else {
			if (node->getLeft() == nullptr) {
				AVLTreeNode<Type>* temp = node->getRight();
				delete node;
				return temp;
			}
			else if (node->getRight() == nullptr) {
				AVLTreeNode<Type>* temp = node->getLeft();
				delete node;
				return temp;
			}

			AVLTreeNode<Type>* temp = node->getRight();
			while (temp->getLeft() != nullptr) {
				temp = temp->getLeft();
			}

			node->data = temp->data;
			node->right = removeRecoursive(node->getRight(), temp->data);
		}

		return balanceTree(node);
	}

public:

	AVLTree() : root(nullptr) {}

	/// <summary>
	/// ���������� �������� � ������
	/// </summary>
	/// <param name="data"></param>
	void insert(const Type& data) {
		root = insertRecoursive(root, data);
	}

	// <summary>
	/// �������� ������
	/// </summary>
	void clear() {
		if (root)
		{
			clearNode(root);
			root = nullptr;
		}
	}

	/// <summary>
	/// �������� �������� �� ������
	/// </summary>
	/// <param name="data"></param>
	void remove(const Type& data) {
		root = removeRecoursive(root, data);
	}

	/// <summary>
	/// ����� ���� � ������
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	AVLTreeNode<Type>* search(const Type& key) {
		return searchRecoursive(root, key);
	}

	/// <summary>
	/// ����� ������������� ������ ������ (LNR)
	/// </summary>
	//��������� O(n)
	//��������� ����� - ������ ��������� ����� ������, ��� ������� ������� �������������� ����� ���������, ����� �������������� ������� ����, � ����� �������������� ������ ���������
	vector <Type> inorder() {
		vector<Type> result;
		inorderRecursive(root, result); //����������� ������� ������
		return result;
	}

	int getBalanceFactorNode(AVLTreeNode<Type>* node) {
		if (node == nullptr) {
			return 0;
		}

		return node->balance;
	}

	int getBalanceFactor(Type val) {
		AVLTreeNode<Type>* node = search(val);
		if (node)
		{
			return getBalanceFactorNode(node);
		}
		else
			throw out_of_range("Value not found");
	}


	/// <summary>
	/// ����������
	/// </summary>
	~AVLTree() {
		clearNode(root);
	}

	//����� ��������� ��� ������ ������. ����� LNR
	class Iterator {
	private:
		AVLTreeNode<Type>* current;
		stack<AVLTreeNode<Type>*> s_node;

	public:

		//����������� ���������
		Iterator(AVLTreeNode<Type>* root) {
			current = nullptr; //���������� ������� ������� ����
			push_left(root); //��������� ����
			if (!s_node.empty()) { //���������, �� ���� �� ����
				current = s_node.top();
				s_node.pop();
			}
		}

		//�������� ����������
		Iterator& operator++() {
			return next();
		}

		//����� next
		Iterator& next() {
			if (!has_next()) {
				throw out_of_range("No more elements");
			}
			current = s_node.top();
			s_node.pop();
			push_left(current->getRight());
			return *this;
		}

		//�������� �������������
		Type& operator*() const {
			return current->data;
		}

		//���������� ������ �� ������ �������� ����
		Type& data() const {
			return current->data;
		}

		//�������� ���������
		bool operator!=(const Iterator& other) const {
			return (s_node.empty() != other.s_node.empty()) || (current != other.current);
		}

		bool has_next() const {
			return !s_node.empty();
		}

		//���������� ��������
		void reset() {
			while (!s_node.empty())
				s_node.pop();
			inorder_stack(root, s_node);
		}

		//���������. True - ���� ������
		bool operator==(const Iterator& other) const
		{
			return current == other.current;
		}

	private:
		void push_left(AVLTreeNode<Type>* node) {
			while (node) {
				s_node.push(node);
				node = node->getLeft();
			}
		}

	};

	//��������� ��������� �� ������ (����� ����� ����)
	Iterator begin() {
		return Iterator(root);
	}

	//��������� ��������� �� ����� (������ ����)
	Iterator end() {
		return Iterator(nullptr);
	}
};

/// <summary>
/// ����� ���� � ������
/// </summary>
/// <param name="node"></param>
/// <param name="key"></param>
/// <returns></returns>
template <typename Type>
AVLTreeNode<Type>* searchRecoursive(AVLTreeNode<Type>* node, const Type& key) {
	if (node == nullptr) {
		return nullptr; //���� ���� ������, ���������� nullptr
	}

	if (node->data == key) {
		return node; //���������� ��������� �� ����, � �� data
	}

	else if (key < node->data) {
		return searchRecoursive(node->getLeft(), key); //���� � ����� ���������
	}

	else {
		return searchRecoursive(node->getRight(), key); //���� � ������ ���������
	}
}

/// <summary>
/// �������� ������
/// </summary>
template<typename Type>
void clearNode(AVLTreeNode<Type>* node) {
	if (node == nullptr) {
		return;
	}

	clearNode(node->getLeft());
	clearNode(node->getRight());
	delete node;
}

/// <summary>
/// ��������������� ������� ��� ������������� ������ (LNR), ��������� ������ � ������
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void inorderRecursive(AVLTreeNode<Type>* node, vector<Type>& result) {
	if (node != nullptr) { //���������, ��� ��������� �� ����� nullptr, ���� �����, �� ������ �� ����� �� ����� ������
		inorderRecursive(node->left, result); //������� ������ ����� ������ ��������� ����, �� ��� ���, ���� �� ��������� �����
		result.push_back(node->data);
		inorderRecursive(node->right, result); //��������� � ������ ��������� � ���������� �����, ���� �� ����� �� �����
	}
}

void test1() {
	//������� ������
	AVLTree<int> tree;
	tree.insert(5);
	tree.insert(9);
	tree.insert(2);
	tree.insert(6);
	tree.insert(1);

	//�����
	assert(tree.search(9) != nullptr); //������� �����
	assert(tree.search(8) == nullptr); //��������� �����

	////�������
	//assert(tree.getHeigth() == 2);

	vector<int> inorderArray = tree.inorder();
	vector<int> inorderArray2 = { 1, 2, 5, 6, 9 };
	assert(inorderArray == inorderArray2);

	//��������
	tree.remove(2);
	assert(tree.search(2) == nullptr);
	vector<int> removeTree = tree.inorder();
	vector<int> removeTree2 = { 1, 5, 6, 9 };
	assert(removeTree == removeTree2);

	tree.remove(45); //������ �� ����������

	tree.clear();
	vector<int> right;

	vector<int> removeTree5 = tree.inorder();
	for (int j = 0; j < removeTree5.size(); j++) {
		cout << removeTree5[j] << endl;
	}

	tree.insert(7);
	tree.insert(8);
	tree.insert(5);
	tree.insert(6);
	tree.insert(3);
	tree.insert(4);
	tree.insert(9);
	right = { 3, 4, 5, 6, 7, 8, 9 };
	int i = 0;
	for (int value : tree)
	{
		assert(abs(tree.getBalanceFactor(value)) < 2);
		i++;
	}
	tree.clear();
	//tree.clear();


	//// ������� ���� ���� (����� ����� �������)
	//tree.insert(2);
	//tree.insert(1);
	//tree.insert(4);
	//tree.insert(3);
	//tree.insert(6);
	//tree.insert(5);
	//tree.insert(7);
	//right.clear();
	//right = { 1, 2, 3, 4, 5, 6, 7 };
	//i = 0;
	//for (int value : tree)
	//{
	//	assert(abs(tree.getBalanceFactor(value)) < 2);
	//	i++;
	//}
	//tree.clear();

	//// ������� ����� ����
	//tree.insert(6);
	//tree.insert(7);
	//tree.insert(2);
	//tree.insert(1);
	//tree.insert(4);
	//tree.insert(3);
	//tree.insert(5);
	//right.clear();
	//right = { 1, 2, 3, 4, 5, 6, 7 };
	//i = 0;
	//for (int value : tree)
	//{
	//	assert(abs(tree.getBalanceFactor(value)) < 2);
	//	i++;
	//}
	//tree.clear();

	//// ������� ���� �����
	//tree.insert(2);
	//tree.insert(1);
	//tree.insert(6);
	//tree.insert(4);
	//tree.insert(3);
	//tree.insert(5);
	//tree.insert(7);
	//AVLTree<int>::Iterator it5 = tree.begin();
	//right.clear();
	//right = { 1, 2, 3, 4, 5, 6, 7 };
	//i = 0;
	//for (int value : tree)
	//{
	//	assert(*it5 == right[i]);
	//	++it5;
	//	i++;
	//}
	//tree.clear();

	//std::cout << "All tests passed successfully!" << std::endl;
}



