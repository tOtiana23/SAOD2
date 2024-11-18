//Бусыгина Татьяна, ИВТ-22

#include <iostream>
#include <vector>
#include <iomanip> // Для setw
#include <functional>
#include <stack>
#include <cassert>
#include <algorithm>

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
		return countRecursive(root);
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

	void clear() {
		deleteTree(root);   // Очищаем дерево
		root = nullptr; // Обнуляем корень дерева
	}

	/// <summary>
	/// Деструктор
	/// </summary>
	~BinSearchTree() {
		deleteTree(root);
	}

	//Класс итератора для дерева поиска. Обход LNR
	class Iterator {
	private:
		TreeNode<Type>* current;
		stack<TreeNode<Type>*> s_node;

	public:

		//Конструктор итератора
		Iterator(TreeNode<Type>* root) {
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
			push_left(current->right);
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
		void push_left(TreeNode<Type>* node) {
			while (node) {
				s_node.push(node);
				node = node->left;
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

	//Вставляем элементы в дерево
	tree.insert(4);
	tree.insert(2);
	tree.insert(6);
	tree.insert(1);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);

	//Проверяем порядок обхода
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
	
	//Проверка, что больше нет элементов
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


	//по коллекции
	// внутри как это for (BinSearchTree<int>::Iterator it = tree.begin(); it != tree.end(); ++it)
	for (int value : tree)
	{
		cout << (value == 4) << ' ' << endl;
	}

	//Обращение к вложенноему классу итератор в бинарном дереве BinSearchTree<int>::Iterator
	for (BinSearchTree<int>::Iterator it = tree.begin(); it != tree.end(); ++it)
	{
		cout << (*it == 4) << ' ' << endl;
	}

	cout << endl;
}

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
		tree.insert(node->data); // Предполагается, что у вас есть метод insert
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
		return nullptr; // Если узел пустой, возвращаем nullptr
	}

	if (node->data == key) {
		return node; // Возвращаем указатель на узел, а не data
	}

	else if (key < node->data) {
		return searchRecoursive(node->left, key); // Ищем в левом поддереве
	}

	else {
		return searchRecoursive(node->right, key); // Ищем в правом поддереве
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

//Тесты для класса BinSearchTree
void test() {
	//Обычное дерево
	BinSearchTree<int> tree;
	tree.insert(5);
	tree.insert(9);
	tree.insert(2);
	tree.insert(6);
	tree.insert(1);

	//Поиск
	assert(tree.search(9) != nullptr); //неудачный поиск
	assert(tree.search(8) == nullptr); //неудачный поиск

	//Количество узлов
	assert(tree.count() == 5);

	//Глубина
	assert(tree.depth() == 2);

	//Обходы и apply
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

	//Удаление
	tree.remove(3);
	assert(tree.count() == 4);
	vector<int> removeTree = tree.inorder();
	vector<int> removeTree2 = { 6, 15, 18, 27 };
	assert(removeTree == removeTree2);

	//Очистка
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

	//Копирование
	BinSearchTree<int> copy_tree = tree2.copy();
	vector<int> copyTree1 = tree2.postorder();
	vector<int> copyTree2 = copy_tree.postorder();
	assert(copyTree1 == copyTree2);

	//Дерево, вырожденное вправо
	BinSearchTree<int> rightDegenerateTree;
	rightDegenerateTree.insert(1);
	rightDegenerateTree.insert(2);
	rightDegenerateTree.insert(3);
	rightDegenerateTree.insert(4);
	rightDegenerateTree.insert(5);

	//Поиск
	assert(rightDegenerateTree.search(3) != nullptr); // Успешный поиск
	assert(rightDegenerateTree.search(0) == nullptr); // Неудачный поиск

	//Количество узлов
	assert(rightDegenerateTree.count() == 5);

	//Глубина
	assert(rightDegenerateTree.depth() == 4); // Глубина будет равна количеству узлов - 1

	//Обходы и apply
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

	//Удаление
	rightDegenerateTree.remove(6);
	assert(rightDegenerateTree.count() == 4);
	vector<int> rightRemoveTree = rightDegenerateTree.inorder();
	vector<int> rightRemoveTree2 = { 3, 9, 12, 15 };
	assert(rightRemoveTree == rightRemoveTree2);

	//Очистка
	rightDegenerateTree.clear();
	assert(rightDegenerateTree.count() == 0);


	//Дерево, вырожденное влево
	BinSearchTree<int> leftDegenerateTree;
	leftDegenerateTree.insert(5);
	leftDegenerateTree.insert(4);
	leftDegenerateTree.insert(3);
	leftDegenerateTree.insert(2);
	leftDegenerateTree.insert(1);

	//Поиск
	assert(leftDegenerateTree.search(3) != nullptr); // Успешный поиск
	assert(leftDegenerateTree.search(6) == nullptr); // Неудачный поиск

	//Количество узлов
	assert(leftDegenerateTree.count() == 5);

	//Глубина
	assert(leftDegenerateTree.depth() == 4); // Глубина будет равна количеству узлов - 1

	//Обходы и apply
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

	//Удаление
	leftDegenerateTree.remove(3);
	assert(leftDegenerateTree.count() == 4);
	vector<int> leftRemoveTree = leftDegenerateTree.inorder();
	vector<int> leftRemoveTree2 = { 6, 9, 12, 15 };
	assert(leftRemoveTree == leftRemoveTree2);

	//Очистка
	leftDegenerateTree.clear();
	assert(leftDegenerateTree.count() == 0);


	//Пустое дерево
	BinSearchTree<int> emptyTree;

	//Поиск
	assert(emptyTree.search(1) == nullptr); // Неудачный поиск

	//Количество узлов
	assert(emptyTree.count() == 0);

	//Глубина
	assert(emptyTree.depth() == -1);

	//Обходы и apply
	vector<int> emptyPostorderArray = emptyTree.postorder();
	vector<int> emptyPostorderArray2 = {};
	assert(emptyPostorderArray == emptyPostorderArray2);

	vector<int> emptyInorderArray = emptyTree.inorder();
	vector<int> emptyInorderArray2 = {};
	assert(emptyInorderArray == emptyInorderArray2);

	vector<int> emptyPreorderArray = emptyTree.preorder();
	vector<int> emptyPreorderArray2 = {};
	assert(emptyPreorderArray == emptyPreorderArray2);

	//Удаление
	emptyTree.remove(1);
	assert(emptyTree.count() == 0);

	//Очистка
	emptyTree.clear();


	TreeNode<int> root;
	root.data = 12;

	//Вставляем узлы
	insertRecursive(&root, 3);
	insertRecursive(&root, 14);
	insertRecursive(&root, 2);
	insertRecursive(&root, 5);
	insertRecursive(&root, 13);
	insertRecursive(&root, 16);

	//Количество узелков
	assert(countRecursive(&root) == 7);

	//Глубина
	assert(depthRecursive(&root) == 2);

	//Обходы
	vector<int> postOrderResult;
	postorderRecursive(&root, postOrderResult);
	assert((postOrderResult == vector<int>{2, 5, 3, 13, 16, 14, 12}));

	vector<int> preOrderResult;
	preorderRecursive(&root, preOrderResult);
	assert((preOrderResult == vector<int>{12, 3, 2, 5, 14, 13, 16}));

	vector<int> inOrderResult;
	inorderRecursive(&root, inOrderResult);
	assert((inOrderResult == vector<int>{2, 3, 5, 12, 13, 14, 16}));

	//Удаление
	removeRecoursive(&root, 2);
	assert(countRecursive(&root) == 6);
	vector<int> removeTr = {};

	//deleteTree(&root);



}