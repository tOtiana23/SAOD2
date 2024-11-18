//�������� �������, ���-22

#include <iostream>
#include <vector>
#include <iomanip> // ��� setw
#include <functional>
#include <stack>
#include <cassert>
#include <algorithm>

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
		return countRecursive(root);
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

	void clear() {
		deleteTree(root);   // ������� ������
		root = nullptr; // �������� ������ ������
	}

	/// <summary>
	/// ����������
	/// </summary>
	~BinSearchTree() {
		deleteTree(root);
	}

	//����� ��������� ��� ������ ������. ����� LNR
	class Iterator {
	private:
		TreeNode<Type>* current;
		stack<TreeNode<Type>*> s_node;

	public:

		//����������� ���������
		Iterator(TreeNode<Type>* root) {
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
			push_left(current->right);
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
		void push_left(TreeNode<Type>* node) {
			while (node) {
				s_node.push(node);
				node = node->left;
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

template<typename Type>
void inorder_stack(TreeNode<Type>* node, stack<TreeNode<Type>*>& stack)
{
	if (node == nullptr) return;
	inorder_stack(node->right, stack);
	stack.push(node);
	inorder_stack(node->left, stack);
}

void test_insert_and_iterator() {
	BinSearchTree<int> tree;

	//��������� �������� � ������
	tree.insert(4);
	tree.insert(2);
	tree.insert(6);
	tree.insert(1);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);

	//��������� ������� ������
	auto it = tree.begin();

	assert(*it == 1);

	++it;
	assert(*it == 2);

	++it;
	assert(*it == 3);

	++it;
	assert(*it == 4);

	++it; 
	assert(*it == 5);

	++it;
	assert(*it == 6);

	++it;
	assert(*it == 7);

	assert(*it != 8);
	
	assert(it.data() == 7);
	assert(!it.has_next());
	
	//��������, ��� ������ ��� ���������
	try {
		++it;
		assert(false);
	}
	catch (const out_of_range&) {
		assert(true);
	}
	
	for_each(tree.begin(), tree.end(), [](int& element)
		{ cout << (element < 4) << " "; });

	cout << endl;


	//�� ���������
	// ������ ��� ��� for (BinSearchTree<int>::Iterator it = tree.begin(); it != tree.end(); ++it)
	for (int value : tree)
	{
		cout << (value == 4) << ' ' << endl;
	}

	//��������� � ����������� ������ �������� � �������� ������ BinSearchTree<int>::Iterator
	for (BinSearchTree<int>::Iterator it = tree.begin(); it != tree.end(); ++it)
	{
		cout << (*it == 4) << ' ' << endl;
	}

	cout << endl;
}

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
		tree.insert(node->data); // ��������������, ��� � ��� ���� ����� insert
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
		return nullptr; // ���� ���� ������, ���������� nullptr
	}

	if (node->data == key) {
		return node; // ���������� ��������� �� ����, � �� data
	}

	else if (key < node->data) {
		return searchRecoursive(node->left, key); // ���� � ����� ���������
	}

	else {
		return searchRecoursive(node->right, key); // ���� � ������ ���������
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

//����� ��� ������ BinSearchTree
void test() {
	//������� ������
	BinSearchTree<int> tree;
	tree.insert(5);
	tree.insert(9);
	tree.insert(2);
	tree.insert(6);
	tree.insert(1);

	//�����
	assert(tree.search(9) != nullptr); //��������� �����
	assert(tree.search(8) == nullptr); //��������� �����

	//���������� �����
	assert(tree.count() == 5);

	//�������
	assert(tree.depth() == 2);

	//������ � apply
	vector<int> postorderArray = tree.postorder();
	vector<int> postorderArray2 = { 1, 2, 6, 9, 5 };
	assert(postorderArray == postorderArray2);

	vector<int> inorderArray = tree.inorder();
	vector<int> inorderArray2 = { 1, 2, 5, 6, 9 };
	assert(inorderArray == inorderArray2);

	vector<int> preorderArray = tree.preorder();
	vector<int> preorderArray2 = { 5, 2, 1, 9, 6 };
	assert(preorderArray == preorderArray2);

	tree.applyInorder([](int& val) { val *= 3; });
	vector<int> applyInorder2 = tree.inorder();
	vector<int> inorderArray3 = { 3, 6, 15, 18, 27 };
	assert(applyInorder2 == inorderArray3);

	//��������
	tree.remove(3);
	assert(tree.count() == 4);
	vector<int> removeTree = tree.inorder();
	vector<int> removeTree2 = { 6, 15, 18, 27 };
	assert(removeTree == removeTree2);

	//�������
	tree.clear();
	assert(tree.count() == 0);

	BinSearchTree<int> tree2;
	tree2.insert(5);
	tree2.insert(9);
	tree2.insert(2);
	tree2.insert(6);
	tree2.insert(1);

	tree2.applyPreorder([](int& val) { val *= 3; });
	vector<int> applyPreorder2 = tree2.preorder();
	vector<int> preorderArray3 = { 15, 6, 3, 27, 18 };
	assert(applyPreorder2 == preorderArray3);

	BinSearchTree<int> tree3;
	tree3.insert(5);
	tree3.insert(9);
	tree3.insert(2);
	tree3.insert(6);
	tree3.insert(1);

	tree3.applyPostorder([](int& val) { val *= 3; });
	vector<int> applyPostorder2 = tree2.postorder();
	vector<int> postorderArray3 = { 3, 6, 18, 27, 15 };
	assert(applyPostorder2 == postorderArray3);

	//�����������
	BinSearchTree<int> copy_tree = tree2.copy();
	vector<int> copyTree1 = tree2.postorder();
	vector<int> copyTree2 = copy_tree.postorder();
	assert(copyTree1 == copyTree2);

	//������, ����������� ������
	BinSearchTree<int> rightDegenerateTree;
	rightDegenerateTree.insert(1);
	rightDegenerateTree.insert(2);
	rightDegenerateTree.insert(3);
	rightDegenerateTree.insert(4);
	rightDegenerateTree.insert(5);

	//�����
	assert(rightDegenerateTree.search(3) != nullptr); // �������� �����
	assert(rightDegenerateTree.search(0) == nullptr); // ��������� �����

	//���������� �����
	assert(rightDegenerateTree.count() == 5);

	//�������
	assert(rightDegenerateTree.depth() == 4); // ������� ����� ����� ���������� ����� - 1

	//������ � apply
	vector<int> rightPostorderArray = rightDegenerateTree.postorder();
	vector<int> rightPostorderArray2 = { 5, 4, 3, 2, 1 };
	assert(rightPostorderArray == rightPostorderArray2);

	vector<int> rightInorderArray = rightDegenerateTree.inorder();
	vector<int> rightInorderArray2 = { 1, 2, 3, 4, 5 };
	assert(rightInorderArray == rightInorderArray2);

	vector<int> rightPreorderArray = rightDegenerateTree.preorder();
	vector<int> rightPreorderArray2 = { 1, 2, 3, 4, 5 };
	assert(rightPreorderArray == rightPreorderArray2);

	rightDegenerateTree.applyInorder([](int& val) { val *= 3; });
	vector<int> rightApplyInorder2 = rightDegenerateTree.inorder();
	vector<int> rightInorderArray3 = { 3, 6, 9, 12, 15 };
	assert(rightApplyInorder2 == rightInorderArray3);

	//��������
	rightDegenerateTree.remove(6);
	assert(rightDegenerateTree.count() == 4);
	vector<int> rightRemoveTree = rightDegenerateTree.inorder();
	vector<int> rightRemoveTree2 = { 3, 9, 12, 15 };
	assert(rightRemoveTree == rightRemoveTree2);

	//�������
	rightDegenerateTree.clear();
	assert(rightDegenerateTree.count() == 0);


	//������, ����������� �����
	BinSearchTree<int> leftDegenerateTree;
	leftDegenerateTree.insert(5);
	leftDegenerateTree.insert(4);
	leftDegenerateTree.insert(3);
	leftDegenerateTree.insert(2);
	leftDegenerateTree.insert(1);

	//�����
	assert(leftDegenerateTree.search(3) != nullptr); // �������� �����
	assert(leftDegenerateTree.search(6) == nullptr); // ��������� �����

	//���������� �����
	assert(leftDegenerateTree.count() == 5);

	//�������
	assert(leftDegenerateTree.depth() == 4); // ������� ����� ����� ���������� ����� - 1

	//������ � apply
	vector<int> leftPostorderArray = leftDegenerateTree.postorder();
	vector<int> leftPostorderArray2 = { 1, 2, 3, 4, 5 };
	assert(leftPostorderArray == leftPostorderArray2);

	vector<int> leftInorderArray = leftDegenerateTree.inorder();
	vector<int> leftInorderArray2 = { 1, 2, 3, 4, 5 };
	assert(leftInorderArray == leftInorderArray2);

	vector<int> leftPreorderArray = leftDegenerateTree.preorder();
	vector<int> leftPreorderArray2 = { 5, 4, 3, 2, 1 };
	assert(leftPreorderArray == leftPreorderArray2);

	leftDegenerateTree.applyInorder([](int& val) { val *= 3; });
	vector<int> leftApplyInorder2 = leftDegenerateTree.inorder();
	vector<int> leftInorderArray3 = { 3, 6, 9, 12, 15 };
	assert(leftApplyInorder2 == leftInorderArray3);

	//��������
	leftDegenerateTree.remove(3);
	assert(leftDegenerateTree.count() == 4);
	vector<int> leftRemoveTree = leftDegenerateTree.inorder();
	vector<int> leftRemoveTree2 = { 6, 9, 12, 15 };
	assert(leftRemoveTree == leftRemoveTree2);

	//�������
	leftDegenerateTree.clear();
	assert(leftDegenerateTree.count() == 0);


	//������ ������
	BinSearchTree<int> emptyTree;

	//�����
	assert(emptyTree.search(1) == nullptr); // ��������� �����

	//���������� �����
	assert(emptyTree.count() == 0);

	//�������
	assert(emptyTree.depth() == -1);

	//������ � apply
	vector<int> emptyPostorderArray = emptyTree.postorder();
	vector<int> emptyPostorderArray2 = {};
	assert(emptyPostorderArray == emptyPostorderArray2);

	vector<int> emptyInorderArray = emptyTree.inorder();
	vector<int> emptyInorderArray2 = {};
	assert(emptyInorderArray == emptyInorderArray2);

	vector<int> emptyPreorderArray = emptyTree.preorder();
	vector<int> emptyPreorderArray2 = {};
	assert(emptyPreorderArray == emptyPreorderArray2);

	//��������
	emptyTree.remove(1);
	assert(emptyTree.count() == 0);

	//�������
	emptyTree.clear();


	TreeNode<int> root;
	root.data = 12;

	//��������� ����
	insertRecursive(&root, 3);
	insertRecursive(&root, 14);
	insertRecursive(&root, 2);
	insertRecursive(&root, 5);
	insertRecursive(&root, 13);
	insertRecursive(&root, 16);

	//���������� �������
	assert(countRecursive(&root) == 7);

	//�������
	assert(depthRecursive(&root) == 2);

	//������
	vector<int> postOrderResult;
	postorderRecursive(&root, postOrderResult);
	assert((postOrderResult == vector<int>{2, 5, 3, 13, 16, 14, 12}));

	vector<int> preOrderResult;
	preorderRecursive(&root, preOrderResult);
	assert((preOrderResult == vector<int>{12, 3, 2, 5, 14, 13, 16}));

	vector<int> inOrderResult;
	inorderRecursive(&root, inOrderResult);
	assert((inOrderResult == vector<int>{2, 3, 5, 12, 13, 14, 16}));

	//��������
	removeRecoursive(&root, 2);
	assert(countRecursive(&root) == 6);
	vector<int> removeTr = {};

	//deleteTree(&root);



}