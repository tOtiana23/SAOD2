//�������� �������, ���-22

#include <iostream>
#include <vector>
#include <iomanip> // ��� setw
#include <functional>

using namespace std;

/// <summary>
/// ��������� ����� ���� ������
/// </summary>
template <typename Type>
class TreeNode {
public:
	Type data;				//������, ������� �������� � ���� ���� ������
	TreeNode<Type>* left;	//��������� �� ���������� ���� ������
	TreeNode<Type>* right;	//��������� �� ��������� ���� ������

	/// <summary>
	/// ����������� ��� ����������
	/// </summary>
	TreeNode(): left(nullptr), right(nullptr), data(Type()) {}

	/// <summary>
	/// ����������� � �����������
	/// </summary>
	/// <param name="data_">������, ������� �������� � ���� ���� ������</param>
	/// <param name="prev_">��������� �� ���������� ���� ������</param>
	/// <param name="next_">��������� �� ��������� ���� ������</param>
	TreeNode(const Type &data_): data(data_), left(nullptr), right(nullptr){}
};


/// <summary>
/// ��������� ����� ��������� ������ ������
/// </summary>
/// <typeparam name="Type"></typeparam>
template <typename Type>
class BinSearchTree{
private:

	TreeNode<Type>* root; //������ 

public:

	/// <summary>
	/// ����������� ��� ����������
	/// </summary>
	BinSearchTree() : root(nullptr) {};

	/// <summary>
	/// ����� ������� ���� � ������
	/// </summary>
	/// <param name="data">������, ������� �������� � ���� ���� ������</param>
	void insert(const Type& data) {
		root = insertRecursive(root, data);  //����������� ������� �������, ������� � ����� ������
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

	/// <summary>
	/// ����� ������� ������ ������ (NLR)
	/// </summary>
	//��������� O(n)
	//������ ����� - ������ ��������� ����� ������, ��� ������� ������� �������������� ������, � ����� ����������
	vector <Type> preorder() {
		vector<Type> result;
		preorderRecursive(root, result); //����������� ������� ������
		return result;
	}

	/// <summary>
	/// ����� ��������� ������ ������ (LRN)
	/// </summary>
	//��������� O(n)
	//�������� ����� - ������ ��������� ����� ������, ��� ������� ������� �������������� ����������, ����� ������
	vector<Type> postorder() {
		vector<Type> result;
		postorderRecursive(root, result); //����������� ������� ������
		return result;
	}

	/// <summary>
	/// ����� ��� ����� ������ (������� ��������� ������ ���������, ����� �����)
	/// </summary>
	void print() const {
		printTree(root, 0);
	}

	/// <summary>
	/// ����� ��� ���������� ������� �� ���� ����� ������ (LNR)
	/// </summary>
	/// <param name="func"></param>
	void applyInorder(const function<void(Type&)>& func) {
		inorderApply(root, func);
	}

	/// <summary>
	/// ����� ��� ���������� ������� �� ���� ����� ������ (LRN)
	/// </summary>
	/// <param name="func"></param>
	void applyPostorder(const function<void(Type&)>& func) {
		postorderApply(root, func);
	}

	/// <summary>
	/// ����� ��� ���������� ������� �� ���� ����� ������ (NLR)
	/// </summary>
	/// <param name="func"></param>
	void applyPreorder(const function<void(Type&)>& func) {
		preorderApply(root, func);
	}

	/// <summary>
	/// ����� ��� ����������� ������� ������ (inorder)
	/// </summary>
	/// <returns>������� ������</returns>
	int depth() const {
		return depthRecursive(root);
	}

	/// <summary>
	/// ����� ��� �������� ���������� ����� � ������
	/// </summary>
	/// <returns>���������� �����</returns>
	size_t count() const {
		return countRecoursive(root);
	}

	/// <summary>
	/// ����� ��� ����������� ������
	/// </summary>
	/// <returns>������</returns>
	BinSearchTree copy() {
		BinSearchTree tree;
		copyRecoursive(root, tree);
		return tree;
	}

	/// <summary>
	/// ����� ��� ������ ���� � ������
	/// </summary>
	/// <param name="key">��, ��� ����� �����</param>
	/// <returns>��������� ����</returns>
	TreeNode<Type>* search(const Type& key) const{
		return searchRecoursive(root, key);
	}

	/// <summary>
	/// ����� ������ ����������� �������
	/// </summary>
	void printInorder() {
		vector<Type> result = inorder();
		cout << "Inorder bypass" << endl;
		for (size_t i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << endl;
	}

	/// <summary>
	/// ����� ������ ������������� �������
	/// </summary>
	void printPostorder() {
		vector<Type> result = postorder();
		cout << "Postorder bypass" << endl;
		for (size_t i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << endl;
	}

	/// <summary>
	/// ����� ������ ������������ �������
	/// </summary>
	void printPreorder() {
		vector<Type> result = preorder();
		cout << "Preorder bypass" << endl;
		for (size_t i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << endl;
	}

	/// <summary>
	/// ����� �������� ���� �� ��������
	/// </summary>
	/// <param name="data">�������� ����, ������� ����� �������</param>
	void remove(const Type& data) {
		removeRecoursive(root, data);
	}

	/// <summary>
	/// ����������
	/// </summary>
	~BinSearchTree() {
		deleteTree(root);
	}
};

/// <summary>
/// ����� ���� ��������� ���� ��� ��������� ���� � �������� ������ ������
/// </summary>
/// <param name="node">��������� �� ����, � ������� �� ��������</param>
/// <returns></returns>


/// ���� ��� ��������, �� ������� ��������
template <typename Type>
TreeNode<Type>* succ(TreeNode<Type>* node) {
	if (node == nullptr || node->right == nullptr) {
		return nullptr; // ���� ���� ������ ��� � ���� ��� ������� ���������
	}

	TreeNode<Type>* current = node->right; // �������� � ������� ���������
	while (current->left != nullptr) { // ���� ����� ����� ����
		current = current->left;
	}
	return current; // ���������� ��������� ����
}

/// <summary>
/// ��������������� ������� ��� �������� ���� �� ��������
/// </summary>
/// <param name="node">��������� �� ����, � ������� �� ��������</param>
/// <param name="data">�������� ����, ������� ����� �������</param>
/// <returns></returns>
template <typename Type>
TreeNode<Type>* removeRecoursive(TreeNode<Type>* node, const Type& data) {
	if (!node) {
		return node; //���� ���� �� ������
	}

	//���� ���� ��� ��������
	if (data < node->data) {
		node->left = removeRecoursive(node->left, data);
	}
	else if (data > node->data) {
		node->right = removeRecoursive(node->right, data);
	}

	//����� ���� ��� ��������
	else {
		//��� �����, ���� ��������
		if (!node->left && !node->right) {
			delete node;
			return nullptr;
		}

		//���� ������
		else if (!node->left) {
			TreeNode<Type>* temp = node->right;
			delete node;
			return temp;
		}
		else if (!node->right) {
			TreeNode<Type>* temp = node->left;
			delete node;
			return temp;
		}

		//��� ������� (����� ����������� ����)
		else {
			TreeNode<Type>* successor = succ(node);
			node->data = successor->data;
			node->right = removeRecoursive(node->right, successor->data);
		}
	}

	return node;
}

/// <summary>
/// ��������������� ������� ��� ����������� ������ (NLR)
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void copyRecoursive(TreeNode<Type>* node, BinSearchTree<Type>& tree) {
	if (node != nullptr) {
		tree.insert(node->data);
		copyRecoursive(node->left, tree);
		copyRecoursive(node->right, tree);
	}
}

/// <summary>
/// ��������������� ������� ��� ������ ����
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
/// <param name="key">��, ��� �� ����</param>
/// <returns>��������� ������</returns>
template <typename Type>
TreeNode<Type>* searchRecoursive(TreeNode<Type>* node, const Type& key) {
	if (node == nullptr) {
		return nullptr;
	}

	if (node->data == key) {
		return data;
	}

	else if (key < node->data) {
		return searchRecoursive(node->left, key);
	}

	else {
		return searchRecoursive(node->right, key);
	}
}

/// <summary>
/// ��������������� ������� ��� �������� ���������� ����� � ������
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
/// <returns>���������� ����� � ������</returns>
template <typename Type>
size_t countRecursive(const TreeNode<Type>* node) {
	if (node == nullptr) return 0;
	int leftCount = countRecursive(node->left);
	int rightCount = countRecursive(node->right);
	return 1 + leftCount + rightCount;
}

/// <summary>
/// ��������������� ������� ��� ����������� ������� ������ (inorder), ���� ������ ������ ������������ -1
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
/// <returns>������� ������</returns>
template <typename Type>
int depthRecursive(const TreeNode<Type>* node) {
	if (node == nullptr) return -1;
	int leftDepth = depthRecursive(node->left);
	int rightDepth = depthRecursive(node->right);
	return 1 + max(leftDepth, rightDepth);
}

/// <summary>
/// ��������������� ������� ��� ������ ������
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
/// <param name="space">������������</param>
template <typename Type>
void printTree(TreeNode<Type>* node, int space) {
	if (node == nullptr) return;

	space += 10; //����������� ������ ��� ���������� ������

	printTree(node->right, space); //������� ������ ���������

	cout << endl;
	cout << setw(space) << node->data << endl; //setw � ��� �����������, ������� ������������ ��� ��������� ������ ���� ��� ������ ������ �� ����������� ����� ������

	printTree(node->left, space); //������� ����� ���������
}

/// <summary>
/// ��������������� ������� ��� ���������� �-��� �� ���� ����� ������ (LNR)
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void inorderApply(TreeNode<Type>* node, const function<void(Type&)>& func) {
	if (node != nullptr) { //���������, ��� ��������� �� ����� nullptr, ���� �����, �� ������ �� ����� �� ����� ������
		inorderApply(node->left, func); //������� ������ ����� ������ ��������� ����, �� ��� ���, ���� �� ��������� �����
		func(node->data);
		inorderApply(node->right, func); //��������� � ������ ��������� � ���������� �����, ���� �� ����� �� �����
	}
}

/// <summary>
/// ��������������� ������� ��� ���������� �-��� �� ���� ����� ������ (LRN)
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void postorderApply(TreeNode<Type>* node, const function<void(Type&)>& func) {
	if (node != nullptr) { //���������, ��� ��������� �� ����� nullptr, ���� �����, �� ������ �� ����� �� ����� ������
		postorderApply(node->left, func); //������� ������ ����� ������ ��������� ����, �� ��� ���, ���� �� ��������� �����
		postorderApply(node->right, func); //��������� � ������ ��������� � ���������� �����, ���� �� ����� �� �����
		func(node->data);
	}
}

/// <summary>
/// ��������������� ������� ��� ���������� �-��� �� ���� ����� ������ (NLR)
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void preorderApply(TreeNode<Type>* node, const function<void(Type&)>& func) {
	if (node != nullptr) { //���������, ��� ��������� �� ����� nullptr, ���� �����, �� ������ �� ����� �� ����� ������
		func(node->data);
		preorderApply(node->left, func); //������� ������ ����� ������ ��������� ����, �� ��� ���, ���� �� ��������� �����
		preorderApply(node->right, func); //��������� � ������ ��������� � ���������� �����, ���� �� ����� �� �����
	}
}

/// <summary>
/// ��������������� ������� ��� ������������� ������ (LNR), ��������� ������ � ������
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void inorderRecursive(TreeNode<Type>* node, vector<Type>& result) {
	if (node != nullptr) { //���������, ��� ��������� �� ����� nullptr, ���� �����, �� ������ �� ����� �� ����� ������
		inorderRecursive(node->left, result); //������� ������ ����� ������ ��������� ����, �� ��� ���, ���� �� ��������� �����
		result.push_back(node->data);
		inorderRecursive(node->right, result); //��������� � ������ ��������� � ���������� �����, ���� �� ����� �� �����
	}
}

/// <summary>
/// ��������������� ������� ��� ������� ������ (NLR), ��������� ������ � ������
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void preorderRecursive(TreeNode<Type>* node, vector<Type>& result) {
	if (node != nullptr) { //���������, ��� ��������� �� ����� nullptr, ���� �����, �� ������ �� ����� �� ����� ������
		result.push_back(node->data);
		preorderRecursive(node->left, result); //������� ������ ����� ������ ��������� ����, �� ��� ���, ���� �� ��������� �����		
		preorderRecursive(node->right, result); //��������� � ������ ��������� � ���������� �����, ���� �� ����� �� �����
	}
}

/// <summary>
/// ��������������� ������� ��� ��������� ������ (LRN), ��������� ������ � ������
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void postorderRecursive(TreeNode<Type>* node, vector<Type>& result) {
	if (node != nullptr) { //���������, ��� ��������� �� ����� nullptr, ���� �����, �� ������ �� ����� �� ����� ������			
		postorderRecursive(node->left, result); //������� ������ ����� ������ ��������� ����, �� ��� ���, ���� �� ��������� �����		
		postorderRecursive(node->right, result); //��������� � ������ ��������� � ���������� �����, ���� �� ����� �� �����
		result.push_back(node->data);
	}
}

/// <summary>
/// ��������������� ������� ��� ������������ ������ (LRN)
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� �� ��������</param>
template <typename Type>
void deleteTree(TreeNode<Type>* node) {
	if (node != nullptr) {
		deleteTree(node->left); //��������� � ������ ���������
		deleteTree(node->right); //��������� � ����� ���������
		delete node; //������� ������� ����
	}
}

/// <summary>
/// ��������������� ������� ��� ������� ���� � ������ �� �������� ��������� ������ ������
/// </summary>
/// <param name="node">��������� �� ������� ����, � ������� ��������</param>
/// <param name="data">������, ������� �������� � ���� ���� ������</param>
/// <returns>������� ����</returns>
template <typename Type>
TreeNode<Type>* insertRecursive(TreeNode<Type>* node, const Type& data) {
	if (node == nullptr) { //���� ���, �� ��� ������, ��� �� �������� �����, ���� ����� �������� ����
		return new TreeNode<Type>(data); //������ ����� ���� � ���������� ���, �� ������ �������� ��� ����, � ������� �� ��������
	}
	//���������� ������, ������� ����� ��������, � ������� �������� ����
	if (data < node->data) { //���� ����������� ������ ������ �������
		node->left = insertRecursive(node->left, data); //�� ��������� ����� ���� � ����� ���������
	}
	else {
		node->right = insertRecursive(node->right, data); //����� ��������� ����� ���� � ������ ���������
	}
	return node; //���������� ������� ����
}

