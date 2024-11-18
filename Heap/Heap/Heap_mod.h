//�������� �������, ���-22

#include <iostream>
#include <vector>
#include <cassert>


using namespace std;

/// <summary>
/// ��������� ����� min-heap
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
	/// ����� ������� �������� � ����. ��������� O(log n) - � ������� � ������, O(1) - � ������
	/// </summary>
	/// <param name="value">��������, ������� �� ���������</param>
	void insert(int value) {
		heap.push_back(value);
		filterUp(heap.size() - 1); //��������� ������� �� ������ �����
	}

	/// <summary>
	/// ����� �������� � ����, �������� ������ �������� ��������, ���� ������� �� ������, �� -1
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	size_t search(const Type& value) const {
		return find(value, 0);
	}

	/// <summary>
	/// ������ � �������� �� �������
	/// </summary>
	/// <param name="index">������ ��������</param>
	/// <returns>�������� ��������</returns>
	size_t operator[](size_t index) const {
		if (index > heap.size()) {
			throw out_of_range("Tried to access to index out of array size");

		}
		else {
			return heap[index];
		}
	}

	/// <summary>
	/// �������� ������������
	/// </summary>
	/// <param name="other">��� ����� ���������</param>
	/// <returns>������ �� ������� ������</returns>
	MinHeap& operator=(const MinHeap& other) {
		if (this != &other) {
			heap = other.heap;
			buildMinHeap();
		}
		return *this;
	}

	/// <summary>
	/// ����� ��� ��������, ����� �� ����
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

		// �������� ���������� ��������
		if (index == heap.size() - 1) {
			heap.pop_back();
			return;
		}

		// ����� �������� ��������� ������� ��������� ��������� ����
		swap(heap[index], heap[heap.size() - 1]);
		heap.pop_back();

		// ��������������� �������� ����������� ����
		if (index == 0 || heap[index] > heap[(index - 1) / 2]) {
			filterDown(index);
		}
		else {
			filterUp(index);
		}
	}


	/// <summary>
	/// ���������� ����� � ������� �����������
	/// </summary>
	/// <param name="data"></param>
	//����� ���������� �� ��������
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
	vector<int> heap; //������ ��� �������� ��������� ����

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
	/// ����� ��� �������� �������� ����� �� ����. ��������� O(n) - � ������� � ������ ������, O(1) - � ������
	/// </summary>
	/// <param name="index">������� �������</param>
	void filterUp(size_t index) {
		while (index > 0){
			size_t parentIndex = (index - 1) / 2; //������� ������ ��������
			if (heap[index] < heap[parentIndex]) {
				swap(heap[index], heap[parentIndex]); //������ ������� � ���������
				index = parentIndex; //��������� � ��������
			}
			else {
				break; // ���� ������� �� ������ ��������, ������� �� �����
			}
		}
	}

	/// <summary>
	/// ����� ��� ��������� �������� ���� �� ����. ��������� O(n) - � ������� � ������ ������, O(1) - � ������
	/// </summary>
	/// <param name="index">������� �������</param>
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
	/// ���������� min-heap
	/// </summary>
	void buildMinHeap() {
		for (int i = heap.size() / 2 - 1; i >= 0; --i) {
			filterDown(i);
		}
	}

	/// <summary>
	/// ����� ��������, � ������ ������� ���������� ������ ����
	/// </summary>
	/// <param name="value">�������� �������� ��������</param>
	/// <param name="index">������ ���������� ��������</param>
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
	//������������ �������
	MinHeap<int> minHeap;
	minHeap.insert(7);
	minHeap.insert(5);
	minHeap.insert(3);

	assert(minHeap[0] == 3); 

	//��������
	minHeap.remove(0);
	assert(minHeap[0] == 5);

	//�����
	assert(minHeap.search(7) == 1); //�������
	assert(minHeap.search(5) == 0); //���������
	

	minHeap.insert(1);
	assert(minHeap[0] == 1);

	//������ �� �������
	try {
		minHeap[10];
		assert(false); 
	}
	catch (const out_of_range&) {
	}

	//������������ �������
	assert(!minHeap.isEmpty());

	//minHeap.remove(0); // ������� ��������� �������
	//assert(minHeap.isEmpty()); // ������ ���� ������ ���� ������

	// ������������ ����������


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
