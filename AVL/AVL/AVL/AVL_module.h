//Бусыгина Татьяна, ИВТ-22

#include <iostream>
#include "BinSearchTreeHeader.h"
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/// <summary>
/// Шаблонный класс узла AVL дерева, наследуется от класса TreeNode
/// </summary>
template <typename Type>
class AVLTreeNode : public TreeNode<Type> {
public:
	int balance; //коэффициент баланса узла - разница между глубиной правого и левого поддеревьев
	
	/// <summary>
	/// Конструктор по умолчанию
	/// </summary>
	AVLTreeNode(): TreeNode<Type>(), balance(0) {}

	/// <summary>
	/// Конструктор с данными
	/// </summary>
	/// <param name="data">данные</param>
	AVLTreeNode(const Type& data) : TreeNode<Type>(data), balance(0) {}

	/// <summary>
	/// Конструктор с данными и указателями на предыдущий и текущий узел
	/// </summary>
	/// <param name="data">данные</param>
	/// <param name="left">указатель на предыдущий узел</param>
	/// <param name="right">указатель на следующий узел</param>
	AVLTreeNode(const Type& data, TreeNode<Type>* left, TreeNode<Type>* right) : TreeNode<Type>(data, left, right), balance(0) {}

	///разобраться!!!!!

	//Преобразователь указателя на (на левый) TreeNode в указатель на AVLTreeNode
	AVLTreeNode<Type>* getLeft() {
		return static_cast<AVLTreeNode<Type>*>(this->left);
	}

	//Преобразователь указателя на (на правый) TreeNode в указатель на AVLTreeNode
	AVLTreeNode<Type>* getRight() {
		return static_cast<AVLTreeNode<Type>*>(this->right);
	}

};

/// <summary>
/// Класс AVL дерева
/// </summary>
/// АВЛ-дерево — сбалансированное двоичное дерево поиска, в котором поддерживается следующее свойство: 
/// для каждой его вершины высота её двух поддеревьев различается не более чем на 1
template <typename Type>
class AVLTree {
private:
	AVLTreeNode<Type>* root; //указатель на корень дерева

	/// <summary>
	/// Обновление баланса
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
	/// Получение высоты
	/// </summary>
	/// <param name="node"></param>
	/// <returns>высота дерева</returns>
	size_t getHeight(AVLTreeNode<Type>* node) {
		if (node == nullptr) {
			return 0;
		}
		return 1 + max(getHeight(node->getLeft()), getHeight(node->getRight()));

	}

	/// <summary>
	/// Левый поворот дерева
	/// </summary>
	/// <param name="node">узел, вокруг которого нужно выполнить поворот</param>
	/// <returns>повёрнутое дерево</returns>
	AVLTreeNode<Type>* rotateLeft(AVLTreeNode<Type>* node) {
		AVLTreeNode<Type>* temp = node->getRight(); //получаем правого потомка узла
		node->right = temp->getLeft(); //левое поддерево temp становится правым поддеревом node
		temp->left = node; //узел node становится левым поддеревом temp

		newBalance(node);
		newBalance(temp);

		return temp;
	}

	/// <summary>
	/// Правый поворот дерева
	/// </summary>
	/// <param name="node">узел, вокруг которого нужно выполнить поворот</param>
	/// <returns>повёрнутое дерево</returns>
	AVLTreeNode<Type>* rotateRight(AVLTreeNode<Type>* node) {
		AVLTreeNode<Type>* temp = node->getLeft();
		node->left = temp->getRight();
		temp->right = node;

		newBalance(node);
		newBalance(temp);

		return temp;
	}

	/// <summary>
	/// Балансировка дерева
	/// </summary>
	/// <param name="node"></param>
	/// <returns></returns>
	AVLTreeNode<Type>* balanceTree(AVLTreeNode<Type>* node) {
		if (node == nullptr) {
			return nullptr;
		}

		newBalance(node);

		//если баланс больше 1, то делаем правый поворот
		if (node->balance > 1) {
			if (getHeight(node->getLeft()->getLeft()) >= getHeight(node->getLeft()->getRight())) {
				//Одинарный правый поворот
				node = rotateRight(node); //маленький поворот
			}
			else {
				//Большой правый поворот
				node->left = rotateLeft(node->getLeft());
				node = rotateRight(node);
			}
		}
		else if (node->balance < -1) {
			if (getHeight(node->getRight()->getRight()) >= getHeight(node->getRight()->getLeft())) {
				//Одинарный левый поворот
				node = rotateLeft(node);
			}
			else {
				//Большой левый поворот
				node->right = rotateRight(node->getRight());
				node = rotateLeft(node);
			}
		}

		return node;
	}

	/// <summary>
	/// Вставка узла в дерево
	/// </summary>
	/// <param name="node"></param>
	/// <param name="data">данные узла, который вставляем</param>
	/// <returns></returns>
	AVLTreeNode<Type>* insertRecoursive(AVLTreeNode<Type>* node, const Type& data) {
		//если сразу нашли место, куда надо вставить узел
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
	/// Удаление узла из дерева
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
	/// Добавление элемента в дерево
	/// </summary>
	/// <param name="data"></param>
	void insert(const Type& data) {
		root = insertRecoursive(root, data);
	}

	// <summary>
	/// Удаление дерева
	/// </summary>
	void clear() {
		if (root)
		{
			clearNode(root);
			root = nullptr;
		}
	}

	/// <summary>
	/// Удаление элемента из дерева
	/// </summary>
	/// <param name="data"></param>
	void remove(const Type& data) {
		root = removeRecoursive(root, data);
	}

	/// <summary>
	/// Поиск узла в дереве
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	AVLTreeNode<Type>* search(const Type& key) {
		return searchRecoursive(root, key);
	}

	/// <summary>
	/// Метод симметричного обхода дерева (LNR)
	/// </summary>
	//Сложность O(n)
	//Инфиксный обход - способ посещения узлов дерева, при котором сначала обрабатывается левое поддерево, затем обрабатывается текущий узел, и потом обрабатывается правое поддерево
	vector <Type> inorder() {
		vector<Type> result;
		inorderRecursive(root, result); //рекурсивный процесс обхода
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
	/// Деструктор
	/// </summary>
	~AVLTree() {
		clearNode(root);
	}

	//Класс итератора для дерева поиска. Обход LNR
	class Iterator {
	private:
		AVLTreeNode<Type>* current;
		stack<AVLTreeNode<Type>*> s_node;

	public:

		//Конструктор итератора
		Iterator(AVLTreeNode<Type>* root) {
			current = nullptr; //Изначально текущий элемент пуст
			push_left(root); //Заполняем стек
			if (!s_node.empty()) { //Проверяем, не пуст ли стек
				current = s_node.top();
				s_node.pop();
			}
		}

		//Оператор инкремента
		Iterator& operator++() {
			return next();
		}

		//Метод next
		Iterator& next() {
			if (!has_next()) {
				throw out_of_range("No more elements");
			}
			current = s_node.top();
			s_node.pop();
			push_left(current->getRight());
			return *this;
		}

		//Оператор разыменования
		Type& operator*() const {
			return current->data;
		}

		//Возвращает ссылку на данные текущего узла
		Type& data() const {
			return current->data;
		}

		//Оператор сравнения
		bool operator!=(const Iterator& other) const {
			return (s_node.empty() != other.s_node.empty()) || (current != other.current);
		}

		bool has_next() const {
			return !s_node.empty();
		}

		//Сбрасывает итератор
		void reset() {
			while (!s_node.empty())
				s_node.pop();
			inorder_stack(root, s_node);
		}

		//Сравнение. True - если равные
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

	//Получение итератора на начало (самый левый узел)
	Iterator begin() {
		return Iterator(root);
	}

	//Получение итератора на конец (пустой узел)
	Iterator end() {
		return Iterator(nullptr);
	}
};

/// <summary>
/// Поиск узла в дереве
/// </summary>
/// <param name="node"></param>
/// <param name="key"></param>
/// <returns></returns>
template <typename Type>
AVLTreeNode<Type>* searchRecoursive(AVLTreeNode<Type>* node, const Type& key) {
	if (node == nullptr) {
		return nullptr; //Если узел пустой, возвращаем nullptr
	}

	if (node->data == key) {
		return node; //Возвращаем указатель на узел, а не data
	}

	else if (key < node->data) {
		return searchRecoursive(node->getLeft(), key); //Ищем в левом поддереве
	}

	else {
		return searchRecoursive(node->getRight(), key); //Ищем в правом поддереве
	}
}

/// <summary>
/// Удаление дерева
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
/// Вспомогательная функция для симметричного обхода (LNR), результат обхода в массив
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void inorderRecursive(AVLTreeNode<Type>* node, vector<Type>& result) {
	if (node != nullptr) { //проверяем, что указатель не равен nullptr, если равен, то значит мы дошли до конца дерева
		inorderRecursive(node->left, result); //сначала делаем обход левого дочернего узла, до тех пор, пока не достигнем конца
		result.push_back(node->data);
		inorderRecursive(node->right, result); //переходим в правое поддерево и продолжаем обход, пока не дойдём до конца
	}
}

void test1() {
	//Обычное дерево
	AVLTree<int> tree;
	tree.insert(5);
	tree.insert(9);
	tree.insert(2);
	tree.insert(6);
	tree.insert(1);

	//Поиск
	assert(tree.search(9) != nullptr); //удачный поиск
	assert(tree.search(8) == nullptr); //неудачный поиск

	////Глубина
	//assert(tree.getHeigth() == 2);

	vector<int> inorderArray = tree.inorder();
	vector<int> inorderArray2 = { 1, 2, 5, 6, 9 };
	assert(inorderArray == inorderArray2);

	//Удаление
	tree.remove(2);
	assert(tree.search(2) == nullptr);
	vector<int> removeTree = tree.inorder();
	vector<int> removeTree2 = { 1, 5, 6, 9 };
	assert(removeTree == removeTree2);

	tree.remove(45); //ничего не произойдет

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


	//// Поворот лево лево (малый левый поворот)
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

	//// Поворот право лево
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

	//// Поворот лево право
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



