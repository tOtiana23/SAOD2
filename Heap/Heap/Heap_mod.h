//Бусыгина Татьяна, ИВТ-22

#include <iostream>
#include <vector>
#include <cassert>


using namespace std;

/// <summary>
/// Шаблонный класс min-heap
/// </summary>
/// <typeparam name="Type"></typeparam>
template <typename Type>
class MinHeap {
public:

	MinHeap() {};

	MinHeap(const vector<int>& data) : heap(data) {
		buildMinHeap();
	}

	/// <summary>
	/// Метод вставки элемента в кучу. Сложность O(log n) - в среднем и худшем, O(1) - в лучшем
	/// </summary>
	/// <param name="value">значение, которое мы вставляем</param>
	void insert(int value) {
		heap.push_back(value);
		filterUp(heap.size() - 1); //поднимаем элемент на нужное место
	}

	/// <summary>
	/// Поиск элемента в куче, возврает индекс искомого элемента, если элемент не найден, то -1
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	size_t search(const Type& value) const {
		return find(value, 0);
	}

	/// <summary>
	/// Доступ к элементу по индексу
	/// </summary>
	/// <param name="index">индекс элемента</param>
	/// <returns>значение элемента</returns>
	size_t operator[](size_t index) const {
		if (index > heap.size()) {
			throw out_of_range("Tried to access to index out of array size");

		}
		else {
			return heap[index];
		}
	}

	/// <summary>
	/// Оператор присваивания
	/// </summary>
	/// <param name="other">что хотим присвоить</param>
	/// <returns>ссылка на текущий объект</returns>
	MinHeap& operator=(const MinHeap& other) {
		if (this != &other) {
			heap = other.heap;
			buildMinHeap();
		}
		return *this;
	}

	/// <summary>
	/// Метод для проверки, пуста ли куча
	/// </summary>
	/// <returns></returns>
	bool isEmpty() const {
		return heap.empty();
	}

	void remove(size_t index) {
		if (isEmpty())
			throw out_of_range("Tried to access empty heap");
		if (index >= heap.size())
			throw out_of_range("Index out of range");

		// Удаление последнего элемента
		if (index == heap.size() - 1) {
			heap.pop_back();
			return;
		}

		// Иначе заменяем удаляемый элемент последним элементом кучи
		swap(heap[index], heap[heap.size() - 1]);
		heap.pop_back();

		// Восстанавливаем свойство минимальной кучи
		if (index == 0 || heap[index] > heap[(index - 1) / 2]) {
			filterDown(index);
		}
		else {
			filterUp(index);
		}
	}


	/// <summary>
	/// Сортировка кучей в порядке возрастания
	/// </summary>
	/// <param name="data"></param>
	//Кучей сортировка по убыванию
	//static void sort(vector<Type>& arr)
	//{
	//	MinHeap heap;
	//	for (int value : arr)
	//	{
	//		heap.push(value);
	//	}
	//	for (size_t i = 0; i < arr.size(); i++)
	//	{
	//		arr[i] = heap.pop();
	//	}
	//}


private:
	vector<int> heap; //вектор для хранения элементов кучи

	int extractMin() {
		if (isEmpty()) {
			throw out_of_range("Heap is empty");
		}
		int minValue = heap[0];
		heap[0] = heap.back();
		heap.pop_back();
		filterDown(0);
		return minValue;
	}

	/// <summary>
	/// Метод для поднятия элемента вверх по куче. Сложность O(n) - в среднем и худшем случае, O(1) - в лучшем
	/// </summary>
	/// <param name="index">текущий элемент</param>
	void filterUp(size_t index) {
		while (index > 0){
			size_t parentIndex = (index - 1) / 2; //Находим индекс родителя
			if (heap[index] < heap[parentIndex]) {
				swap(heap[index], heap[parentIndex]); //Меняем местами с родителем
				index = parentIndex; //Переходим к родителю
			}
			else {
				break; // Если элемент не меньше родителя, выходим из цикла
			}
		}
	}

	/// <summary>
	/// Метод для опускания элемента вниз по куче. Сложность O(n) - в среднем и худшем случае, O(1) - в лучшем
	/// </summary>
	/// <param name="index">текущий элемент</param>
	void filterDown(int index) {
		size_t leftChild, rightChild, smallest;
		while (true) {
			leftChild = 2 * index + 1;
			rightChild = 2 * index + 2;
			smallest = index;

			if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
				smallest = leftChild;
			}
			if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
				smallest = rightChild;
			}
			if (smallest != index) {
				swap(heap[index], heap[smallest]);
				index = smallest;
			}
			else {
				break;
			}
		}
	
	}

	/// <summary>
	/// Построение min-heap
	/// </summary>
	void buildMinHeap() {
		for (int i = heap.size() / 2 - 1; i >= 0; --i) {
			filterDown(i);
		}
	}

	/// <summary>
	/// Поиск элемента, в случае неудачи возврается размер кучи
	/// </summary>
	/// <param name="value">значение искомого элемента</param>
	/// <param name="index">индекс найденного элемента</param>
	size_t find(const Type& value, size_t index) const{
		if (index >= heap.size())
		{
			return heap.size();
		}

		if (heap[index] == value) {
			return index;
		}

		size_t leftIndex = 2 * index + 1;
		size_t rightIndex = 2 * index + 2;
		size_t leftResult = find(value, leftIndex);
		size_t rightResult = find(value, rightIndex);

		if (leftResult < heap.size()) {
			return leftResult;
		}
		else if (rightResult < heap.size()) {
			return rightResult;
		}
		else {
			return heap.size();
		}
	}
};

void testMinHeap() {
	//Тестирование вставки
	MinHeap<int> minHeap;
	minHeap.insert(7);
	minHeap.insert(5);
	minHeap.insert(3);

	assert(minHeap[0] == 3); 

	//Удаление
	minHeap.remove(0);
	assert(minHeap[0] == 5);

	//Поиск
	assert(minHeap.search(7) == 1); //удачный
	assert(minHeap.search(5) == 0); //неудачный
	

	minHeap.insert(1);
	assert(minHeap[0] == 1);

	//Доступ по индексу
	try {
		minHeap[10];
		assert(false); 
	}
	catch (const out_of_range&) {
	}

	//Тестирование пустоты
	assert(!minHeap.isEmpty());

	//minHeap.remove(0); // Удаляем последний элемент
	//assert(minHeap.isEmpty()); // Теперь куча должна быть пустой

	// Тестирование сортировки


	//MinHeap<int> minHeap2;
	//minHeap2.insert(7);
	//minHeap2.insert(5);
	//minHeap2.insert(3);

	//minHeap2.sort();
	//cout << minHeap2[0];
	//cout << minHeap2[1];
	//cout << minHeap2[2];


	//assert(minHeap2[0] == 3);
	//assert(minHeap2[1] == 5);
	//assert(minHeap2[2] == 7);
}
