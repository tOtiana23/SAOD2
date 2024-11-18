//Бусыгина Татьяна, ИВТ-22

#include <iostream>
#include <vector>
#include <iomanip> // Для setw
#include <functional>

using namespace std;

/// <summary>
/// Шаблонный класс узла дерева
/// </summary>
template <typename Type>
class TreeNode {
public:
	Type data;				//данные, которые содержит в себе узел дерева
	TreeNode<Type>* left;	//указатель на предыдущий узел дерева
	TreeNode<Type>* right;	//указатель на следующий узел дерева

	/// <summary>
	/// Конструктор без параметров
	/// </summary>
	TreeNode(): left(nullptr), right(nullptr), data(Type()) {}

	/// <summary>
	/// Конструктор с параметрами
	/// </summary>
	/// <param name="data_">данные, которые содержит в себе узел дерева</param>
	/// <param name="prev_">указатель на предыдущий узел дерева</param>
	/// <param name="next_">указатель на следующий узел дерева</param>
	TreeNode(const Type &data_): data(data_), left(nullptr), right(nullptr){}
};


/// <summary>
/// Шаблонный класс бинарного дерева поиска
/// </summary>
/// <typeparam name="Type"></typeparam>
template <typename Type>
class BinSearchTree{
private:

	TreeNode<Type>* root; //корень 

public:

	/// <summary>
	/// Конструктор без параметров
	/// </summary>
	BinSearchTree() : root(nullptr) {};

	/// <summary>
	/// Метод вставки узла в дерево
	/// </summary>
	/// <param name="data">данные, которые содержит в себе узел дерева</param>
	void insert(const Type& data) {
		root = insertRecursive(root, data);  //рекурсивный процесс вставки, начиная с корня дерева
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

	/// <summary>
	/// Метод прямого обхода дерева (NLR)
	/// </summary>
	//Сложность O(n)
	//Прямой обход - способ посещения узлов дерева, при котором сначала обрабатывается корень, а затем поддеревья
	vector <Type> preorder() {
		vector<Type> result;
		preorderRecursive(root, result); //рекурсивный процесс обхода
		return result;
	}

	/// <summary>
	/// Метод обратного обхода дерева (LRN)
	/// </summary>
	//Сложность O(n)
	//Обратный обход - способ посещения узлов дерева, при котором сначала обрабатываются поддеревья, затем корень
	vector<Type> postorder() {
		vector<Type> result;
		postorderRecursive(root, result); //рекурсивный процесс обхода
		return result;
	}

	/// <summary>
	/// Метод для вывод дерева (сначала выводится правое поддерево, затем левое)
	/// </summary>
	void print() const {
		printTree(root, 0);
	}

	/// <summary>
	/// Метод для применения функции ко всем узлам дерева (LNR)
	/// </summary>
	/// <param name="func"></param>
	void applyInorder(const function<void(Type&)>& func) {
		inorderApply(root, func);
	}

	/// <summary>
	/// Метод для применения функции ко всем узлам дерева (LRN)
	/// </summary>
	/// <param name="func"></param>
	void applyPostorder(const function<void(Type&)>& func) {
		postorderApply(root, func);
	}

	/// <summary>
	/// Метод для применения функции ко всем узлам дерева (NLR)
	/// </summary>
	/// <param name="func"></param>
	void applyPreorder(const function<void(Type&)>& func) {
		preorderApply(root, func);
	}

	/// <summary>
	/// Метод для определения глубины дерева (inorder)
	/// </summary>
	/// <returns>глубина дерева</returns>
	int depth() const {
		return depthRecursive(root);
	}

	/// <summary>
	/// Метод для подсчета количества узлов в дереве
	/// </summary>
	/// <returns>количество узлов</returns>
	size_t count() const {
		return countRecoursive(root);
	}

	/// <summary>
	/// Метод для копирования дерева
	/// </summary>
	/// <returns>дерево</returns>
	BinSearchTree copy() {
		BinSearchTree tree;
		copyRecoursive(root, tree);
		return tree;
	}

	/// <summary>
	/// Метод для поиска узла в дереве
	/// </summary>
	/// <param name="key">то, что нужно найти</param>
	/// <returns>найденный узел</returns>
	TreeNode<Type>* search(const Type& key) const{
		return searchRecoursive(root, key);
	}

	/// <summary>
	/// Метод вывода инордерного массива
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
	/// Метод вывода постордерного массива
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
	/// Метод вывода преордерного массива
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
	/// Метод удаления узла по значению
	/// </summary>
	/// <param name="data">значение узла, который нужно удалить</param>
	void remove(const Type& data) {
		removeRecoursive(root, data);
	}

	/// <summary>
	/// Деструктор
	/// </summary>
	~BinSearchTree() {
		deleteTree(root);
	}

	//Класс итератора для дерева поиска
	class Iterator {
	private:
		TreeNode<Type>* current;

	public:
		//Конструктор итератора
		Iterator(TreeNode<Type>* node) : current(node) {}

		//Оператор инкремента
		Iterator& operator++() {
			if (current == nullptr) {
				return *this;
			}
			//Если есть левый потомок, то переходим к нему
			if (current->left != nullptr) {
				current = current->left;
				while (current->right != nullptr) {
					current = current->right;
				}
				return *this;
			}
			//Иначе поднимаемся вверх по дереву до тех пор, 
			//пока не найдем узел, который является правым потомком своего предка
			TreeNode<Type>* parent = current->right;
			while (parent != nullptr && current == parent->left) {
				current = parent;
				parent = parent->right;
			}

			current = parent;
			return *this;
		}

		// Метод next
		Iterator next() {
			return ++(*this);
		}

		//Оператор разыменования
		Type& operator*() {
			return current->data;
		}

		//Возвращает ссылку на данные текущего узла
		Type& data()
		{
			return current->data;
		}

		//Оператор присваивания, копирует состояние другого итератора
		bool operator=(const Iterator& other) const {
			if (this != &other)
			{
				current = other.current;
			}
			return *this;
		}

		//Оператор сравнения
		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}

		bool end_of_list() const
		{
			return current == nullptr;
		}

	};

	//Получение итератора на начало (самый левый узел)
	Iterator begin() {
		TreeNode<Type>* node = root;
		while (node != nullptr && node->left != nullptr) {
			node = node->left;
		}
		return Iterator(node);
	}

	//Получение итератора на конец (пустой узел)
	Iterator end() {
		return Iterator(nullptr);
	}
};

/// <summary>
/// Метод ищет следующий узел для заданного узла в бинарном дереве поиска
/// </summary>
/// <param name="node">указатель на узел, с которым мы работаем</param>
/// <returns></returns>
/// если нет потомков, то вернуть родителя
template <typename Type>
TreeNode<Type>* succ(TreeNode<Type>* node) {
	if (node == nullptr || node->right == nullptr) {
		return nullptr; // Если узел пустой или у него нет правого поддерева
	}

	TreeNode<Type>* current = node->right; // Начинаем с правого поддерева
	while (current->left != nullptr) { // Ищем самый левый узел
		current = current->left;
	}
	return current; // Возвращаем найденный узел
}

/// <summary>
/// Вспомогательная функция для удаления узла по значению
/// </summary>
/// <param name="node">указатель на узел, с которым мы работаем</param>
/// <param name="data">значение узла, который нужно удалить</param>
/// <returns></returns>
template <typename Type>
TreeNode<Type>* removeRecoursive(TreeNode<Type>* node, const Type& data) {
	if (!node) {
		return node; //если узел не найден
	}

	//ищем узел для удаления
	if (data < node->data) {
		node->left = removeRecoursive(node->left, data);
	}
	else if (data > node->data) {
		node->right = removeRecoursive(node->right, data);
	}

	//нашли узел для удаления
	else {
		//нет детей, отец одиночка
		if (!node->left && !node->right) {
			delete node;
			return nullptr;
		}

		//один детёныш
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

		//два детёныша (почти многодетный отец)
		else {
			TreeNode<Type>* successor = succ(node);
			node->data = successor->data;
			node->right = removeRecoursive(node->right, successor->data);
		}
	}

	return node;
}

/// <summary>
/// Вспомогательная функция для копирования дерева (NLR)
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void copyRecoursive(TreeNode<Type>* node, BinSearchTree<Type>& tree) {
	if (node != nullptr) {
		tree.insert(node->data);
		copyRecoursive(node->left, tree);
		copyRecoursive(node->right, tree);
	}
}

/// <summary>
/// Вспомогательная функция для поиска узла
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
/// <param name="key">то, что мы ищем</param>
/// <returns>результат поиска</returns>
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
/// Вспомогательная функция для подсчета количества узлов в дереве
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
/// <returns>количество узлов в дереве</returns>
template <typename Type>
size_t countRecursive(const TreeNode<Type>* node) {
	if (node == nullptr) return 0;
	int leftCount = countRecursive(node->left);
	int rightCount = countRecursive(node->right);
	return 1 + leftCount + rightCount;
}

/// <summary>
/// Вспомогательная функция для определения глубины дерева (inorder), если дерево пустое возвращается -1
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
/// <returns>глубину дерева</returns>
template <typename Type>
int depthRecursive(const TreeNode<Type>* node) {
	if (node == nullptr) return -1;
	int leftDepth = depthRecursive(node->left);
	int rightDepth = depthRecursive(node->right);
	return 1 + max(leftDepth, rightDepth);
}

/// <summary>
/// Вспомогательная функция для вывода дерева
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
/// <param name="space">пространство</param>
template <typename Type>
void printTree(TreeNode<Type>* node, int space) {
	if (node == nullptr) return;

	space += 10; //увеличиваем отступ для следующего уровня

	printTree(node->right, space); //выводим правое поддерево

	cout << endl;
	cout << setw(space) << node->data << endl; //setw — это манипулятор, который используется для установки ширины поля при выводе данных на стандартный поток вывода

	printTree(node->left, space); //выводим левое поддерево
}

/// <summary>
/// Вспомогательная функция для применения ф-ции ко всем узлам дерева (LNR)
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void inorderApply(TreeNode<Type>* node, const function<void(Type&)>& func) {
	if (node != nullptr) { //проверяем, что указатель не равен nullptr, если равен, то значит мы дошли до конца дерева
		inorderApply(node->left, func); //сначала делаем обход левого дочернего узла, до тех пор, пока не достигнем конца
		func(node->data);
		inorderApply(node->right, func); //переходим в правое поддерево и продолжаем обход, пока не дойдём до конца
	}
}

/// <summary>
/// Вспомогательная функция для применения ф-ции ко всем узлам дерева (LRN)
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void postorderApply(TreeNode<Type>* node, const function<void(Type&)>& func) {
	if (node != nullptr) { //проверяем, что указатель не равен nullptr, если равен, то значит мы дошли до конца дерева
		postorderApply(node->left, func); //сначала делаем обход левого дочернего узла, до тех пор, пока не достигнем конца
		postorderApply(node->right, func); //переходим в правое поддерево и продолжаем обход, пока не дойдём до конца
		func(node->data);
	}
}

/// <summary>
/// Вспомогательная функция для применения ф-ции ко всем узлам дерева (NLR)
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void preorderApply(TreeNode<Type>* node, const function<void(Type&)>& func) {
	if (node != nullptr) { //проверяем, что указатель не равен nullptr, если равен, то значит мы дошли до конца дерева
		func(node->data);
		preorderApply(node->left, func); //сначала делаем обход левого дочернего узла, до тех пор, пока не достигнем конца
		preorderApply(node->right, func); //переходим в правое поддерево и продолжаем обход, пока не дойдём до конца
	}
}

/// <summary>
/// Вспомогательная функция для симметричного обхода (LNR), результат обхода в массив
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void inorderRecursive(TreeNode<Type>* node, vector<Type>& result) {
	if (node != nullptr) { //проверяем, что указатель не равен nullptr, если равен, то значит мы дошли до конца дерева
		inorderRecursive(node->left, result); //сначала делаем обход левого дочернего узла, до тех пор, пока не достигнем конца
		result.push_back(node->data);
		inorderRecursive(node->right, result); //переходим в правое поддерево и продолжаем обход, пока не дойдём до конца
	}
}

/// <summary>
/// Вспомогательная функция для прямого обхода (NLR), результат обхода в массив
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void preorderRecursive(TreeNode<Type>* node, vector<Type>& result) {
	if (node != nullptr) { //проверяем, что указатель не равен nullptr, если равен, то значит мы дошли до конца дерева
		result.push_back(node->data);
		preorderRecursive(node->left, result); //сначала делаем обход левого дочернего узла, до тех пор, пока не достигнем конца		
		preorderRecursive(node->right, result); //переходим в правое поддерево и продолжаем обход, пока не дойдём до конца
	}
}

/// <summary>
/// Вспомогательная функция для обратного обхода (LRN), результат обхода в массив
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void postorderRecursive(TreeNode<Type>* node, vector<Type>& result) {
	if (node != nullptr) { //проверяем, что указатель не равен nullptr, если равен, то значит мы дошли до конца дерева			
		postorderRecursive(node->left, result); //сначала делаем обход левого дочернего узла, до тех пор, пока не достигнем конца		
		postorderRecursive(node->right, result); //переходим в правое поддерево и продолжаем обход, пока не дойдём до конца
		result.push_back(node->data);
	}
}

/// <summary>
/// Вспомогательная функция для освобождения памяти (LRN)
/// </summary>
/// <param name="node">указатель на текущий узел, с которым мы работаем</param>
template <typename Type>
void deleteTree(TreeNode<Type>* node) {
	if (node != nullptr) {
		deleteTree(node->left); //переходим в правое поддерево
		deleteTree(node->right); //переходим в левое поддерево
		delete node; //удаляем текущий узел
	}
}

/// <summary>
/// Вспомогательная функция для вставки узла в дерево по правилам бинарного дерева поиска
/// </summary>
/// <param name="node">указатель на текущий узел, с которым работаем</param>
/// <param name="data">данные, которые содержит в себе узел дерева</param>
/// <returns>текущий узел</returns>
template <typename Type>
TreeNode<Type>* insertRecursive(TreeNode<Type>* node, const Type& data) {
	if (node == nullptr) { //если так, то это значит, что мы достигли места, куда можем вставить узел
		return new TreeNode<Type>(data); //создаём новый узел и возвращаем его, он станет дочерним для узла, с которым мы работали
	}
	//сравниваем данные, которые хотим вставить, с данными текущего узла
	if (data < node->data) { //если вставляемые данные меньше текущих
		node->left = insertRecursive(node->left, data); //то вставляем новый узел в левое поддерево
	}
	else {
		node->right = insertRecursive(node->right, data); //иначе вставляем новый узел в правое поддерево
	}
	return node; //возвращаем текущий узел
}

