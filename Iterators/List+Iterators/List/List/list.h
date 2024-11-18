//�������� ������, ���-22

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//������� ���� ������, ��� ���� � ������ ��� ��������� ��������� ���� �� ���� �� ��������� �������:

// 1. ����������� �����������
// 2. �������� ������������
// 3. ����������
// 4. ����������� �����������
// 5. �������� �����������

// ��, ��������, ����� ���������� ��� ���� ������� ��� ����������� ����������� ���������� ��������� � �������������� ������ ������ ��� 
//������ ������� � ����������� ���������. 

///����� ���� ����������� ������
template <typename T>
class Node
{
public:
    T data; 			//������ ����
    Node<T>* prev;		//��������� �� ���������� ����
    Node<T>* next;		//��������� �� ��������� ����

    ///����������� ��� ����������
    Node() : prev(nullptr), next(nullptr), data(T()) {}

    ///����������� � �����������, data_- ������ ���� prev_ - ��������� �� ���������� ����, next_ - ��������� �� ��������� ����
    Node(const T& data_, Node<T>* prev_, Node<T>* next_) : data(data_), prev(prev_), next(next_) {}

    ///����������� � �������, ��������� prev � next ��������� �� nullptrll, data_ - ������ ����
    Node(const T& data_) : data(data_), prev(nullptr), next(nullptr) {}

    ///����������� �����������, node ��, ��� ��������
    Node(const Node<T>& node) : data(node.data), prev(nullptr), next(nullptr)
    {
        if (node.prev != nullptr)
        {
            prev = new Node(node.prev->data);
        }
        if (node.next != nullptr)
        {
            next = new Node(node.next->data);
        }
    }

    ///����������� �����������, node ��, ��� ����������
    Node(Node<T>&& node) : data(node.data), prev(node.prev), next(node.next) //���������� ���������
    {
        //������������� ������ ������ ��� ����������� ���������� �������
        node.prev = nullptr;
        node.next = nullptr;
    }

    ///�������� �����������, node ��, ��� ��������
    Node<T>& operator=(const Node<T>& node)
    {
        if (this != &node) //��������� ����� �� ���� ����������������
        {
            delete prev;
            delete next;

            //�������� ��
            data = node.data;
            if (node.prev != nullptr)
            {
                prev = new Node(node.prev->data);
            }
            if (node.next != nullptr)
            {
                next = new Node(node.next->data);
            }
        }
        return *this;
    }

    ///�������� �����������
    Node<T>& operator=(Node<T>&& node)
    {
        if (this != &node) //��������� ����� �� ���� ����������������
        {
            data = node.data;
            prev = node.prev;
            next = node.next;

            node.prev = nullptr;
            node.next = nullptr;
        }
        return *this;
    }

    ///����������
    ~Node()
    {
        //������� ��������� �� ���������� � ��������� ����
        if (prev != nullptr && next != nullptr)
        {
            prev = nullptr;
            next = nullptr;
        }
    }
};


///����� ���������� ������
template <typename T>
class List
{
private:
    //��������� �� ������ ������
    Node<T>* head;
    //��������� �� ����� ������
    Node<T>* tail;
    //������ ������
    size_t size;
    ///������������� �������� � ������
    void forget() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

public:

    ///����������� �� ���������
    List()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ///�����������, ����������� ������
    List(size_t size_, const T& data_) {
        for (size_t i = 0; i < size_; i++) {
            add_last(data_);
        }
    }

    ///����������� �����������
    List(const List& other) {
        head = nullptr;
        tail = nullptr;
        size = 0;
        //�������� �������� �� ������� ������
        copy(other);
    }

    ///����������� �����������
    List(List&& other) {
        //���������� �������� �� ������� ������
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.forget();
    }

    Node<T>* get_head() const {
        return head;
    }

    Node<T>* get_tail() const {
        return tail;
    }

    Node<T>* get_node(size_t place)
    {
        // ��������
        if (place < 0 || place >= size)
        {
            throw out_of_range("Invalid index");
        }

        Node<T>* current = head;

        for (size_t i = 0; i < place; i++)
        {
            current = current->next;
        }
        // ������������� � ���������
        return current;
    }

    ///�������� ������
    void clear() {
        //������� ��� ���� �� ������
        while (head != nullptr) {
            Node<T>* next_node = head->next;
            delete head;
            head = next_node;
        }
        forget();
    }

    //����������� ������ (��������)
    void copy(const List<T>& other) {
        clear();

        Node<T>* current = other.head;
        while (current != nullptr) {
            add_last(current->data);
            current = current->next;
        }
    }

    ///�������� ������������ ������������
    List& operator=(const List& other) {
        if (this == &other) {
            return *this;
        }

        //������� ������� ������
        clear();

        //�������� �������� �� ������� ������
        copy(other);

        return *this;
    }

    ///�������� ������������ ������������
    List& operator=(List&& other) {
        if (this == &other) {
            return *this;
        }
        //������� ������� ������
        clear();
        //���������� �������� �� ������� ������
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.forget();
        return *this;
    }

    ///����������
    ~List() {
        clear();//������� ������
    }

    ///���������� �������� � ������ ������
    //��������� O(1)
    void add_first(const T& data) {
        //������� ����� ����
        Node<T>* new_node = new Node<T>(data);

        //���� ������ ����, �� ����� ���� ���������� �������� � ���������
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        }
        else {
            //����� ��������� ����� ���� � ������ ������
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        //����������� ������ ������
        size++;
    }

    ///��������� ������� � ����� ������
    //��������� O(1)
    void add_last(const T& data) {
        //������� ����� ����
        Node<T>* new_node = new Node<T>(data);
        //���� ������ ����, �� ����� ���� ���������� �������� � ���������
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        }
        else {
            //����� ��������� ����� ���� � ����� ������
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        //����������� ������ ������
        size++;
    }


    ///������� ��������� ������� �� ������
    T del_last() {
        if (tail == nullptr) {
            return T();
        }
        T value = tail->data;
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node<T>* new_tail = tail->prev;
            delete tail;
            tail = new_tail;
            tail->next = nullptr;
        }
        size--;
        return value;
    }

    ///������� ������ ������� �� ������
    T del_first() {
        if (head == nullptr) {
            return T();
        }
        T value = head->data;
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node<T>* new_head = head->next;
            delete head;
            head = new_head;
            head->prev = nullptr;
        }
        size--;
        return value;
    }

    ///������� ���� �� ���������, ������ key
    //��������� O(n)
    Node<T>* find(const T& key)
    {
        //���� ���� �� ���������, ������ key
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    ///���������� ������ ������
    //��������� O(1)
    size_t sizes() const {
        return size;
    }


    ///���������� ������ ��������� �� �����������
    //��������� O(n^2)
    void sort()
    {
        if (size < 2)
        {
            return;
        }

        Node<T>* current = head;
        Node<T>* index = nullptr;
        T temp;

        while (current != nullptr)
        {
            index = current->next;

            while (index != nullptr)
            {
                if (current->data > index->data)
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }

    ///������������ (�����������) ���� �������, other - ������, ������� ���������
    //��������� �(n)
    void concatenate(List<T>& other, bool cut = false) {
        if (other.get_head() == nullptr) {
            return;
        }

        if (head == nullptr) {
            *this = other;
            return;
        }

        this->tail->next = other.head;
        other.head->prev = this->tail;
        this->tail = other.tail;
        this->size += other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    //����� �������� ��� ����������� �� ��������� ������ � �������� ������� � �� ������.
    class Iterator {
    private:
        Node<T>* current; //��������� �� ������� ���� � ������
    public: 
        Iterator(Node<T>* head):
            current(head) {}

        //�������� ��� ��������� �������� ���� ��������� � ������ ����������. True - ��������� �� ������ ����.
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        //�������� ��� ��������� ������� � ������ �������� ����, �� ������� ��������� ��������
        T& operator*() const {
            return current->data;
        }

        //����� ���������, ���� �� ��������� ������� � ������
        bool hasNext() {
            return current != nullptr;
        }

        //����� ���������� �������� �� ��������� ����. ���� ��� ����, �� �������� ����������.
        Iterator& next() {
            if (!hasNext()) {
                throw out_of_range("No more elements in the iterator");
            }
            current = current->next;
            return *this;
        }

        T& data() {
            return current->data;
        }

        //����������� ���������
        Iterator& operator++() {
            return next();
        }

        void reset() {
            current = head;
        }

        bool end_of_list() const {
            return current == nullptr;
        }

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                current = other.current;
            }
            return *this;
        }

    };

        //���������� �������� �� ������ ������
        Iterator begin() { return Iterator(head); }

        //���������� �������� �� ����� ������
        Iterator end() { return Iterator(nullptr); }
    
};

///���� ���������
void test_iterator() {
    List<int> list;
    list.add_last(1);
    list.add_last(2);
    list.add_last(3);

    auto it = list.begin();
    assert(*it == 1); // �������� ������� ��������
    ++it; // ������� � ���������� ��������
    assert(*it == 2); // �������� ������� ��������
    ++it; // ������� � ���������� ��������
    assert(*it == 3); // �������� �������� ��������
    ++it; // ������� � ���������� ��������

    try
    {
        ++it;
        assert(false); // ������ ��������� ����������
    }
    catch (const std::out_of_range& e)
    {
        // ���������� ������ ���� �������
        assert(true);
    }

    for_each(list.begin(), list.end(), [](int& element)
        { cout << element << " "; });

    cout << endl;

    // For �� ��������� 
    for (int value : list) {
        cout << value << ' ' << endl;
    }

    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << ' ' << endl;
    }

    cout << endl;
}

///���� ������������
void test_concatenate() {
    List<int> list1;
    List<int> list2;

    //��������� �������� � ��� ������
    list1.add_last(1);
    list1.add_last(2);
    list2.add_last(3);
    list2.add_last(4);

    //������������ ������������ �������� �������
    list1.concatenate(list2);
    assert(list1.sizes() == 4);
    assert(list1.find(1)->data == 1);
    assert(list1.find(2)->data == 2);
    assert(list1.find(3)->data == 3);
    assert(list1.find(4)->data == 4);

    //��������, ��� ������ ������ ���� ������ ����� ������������
    assert(list2.sizes() == 0);
}


///���� ���������� ���� � ������ ������
void test_add_first() {
    List<int> list;

    // ������������ ���������� �������� � ������ ������
    list.add_first(1);
    assert(list.sizes() == 1);
    assert(list.get_head()->data == 1);
    assert(list.get_tail()->data == 1);

    // ��������� ��� �������� � ������
    list.add_first(2);
    list.add_first(3);

    // ������������ ���������� ��������� � ������ ������
    assert(list.sizes() == 3);
    assert(list.get_head()->data == 3);
    assert(list.get_tail()->data == 1);
    assert(list.get_head()->next->data == 2);
    assert(list.get_tail()->prev->data == 2);
}


///���� ���������� ���� � ����� ������
void test_add_last() {
    List<int> list;

    // ������������ ���������� �������� � ������ ������
    list.add_last(5);
    assert(list.get_head() != nullptr);
    assert(list.get_tail() != nullptr);
    assert(list.get_tail()->data == 5);
    assert(list.sizes() == 1);

    // ������������ ���������� �������� � �������� ������
    list.add_last(10);
    assert(list.get_tail()->data == 10);
    assert(list.get_tail()->prev->data == 5);
    assert(list.get_tail()->prev->next == list.get_tail());
    assert(list.sizes() == 2);
}

///���� �������� ���������� ���� �� ������
void test_del_last() {
    List<int> list;

    // ������������ �������� �� ������� ������
    assert(list.del_last() == 0);

    // ��������� �������� � ������
    list.add_last(1);
    list.add_last(2);
    list.add_last(3);

    // ������������ �������� ���������� ��������
    assert(list.del_last() == 3);
    assert(list.sizes() == 2);

    // ��������� �������� ���������� ��������
    assert(list.del_last() == 2);
    assert(list.sizes() == 1);

    // �������� ���������� �������� �� ������ � ����� ���������
    assert(list.del_last() == 1);
    assert(list.sizes() == 0);

    // ������� �������� �� ������� ������
    assert(list.del_last() == 0);
}

///���� �������� ������� ���� �� ������
void test_del_first() {
    List<int> list;

    // ������������ �������� �� ������� ������
    assert(list.del_first() == 0);

    // ��������� �������� � ������
    list.add_last(1);
    list.add_last(2);
    list.add_last(3);

    // ������������ �������� ������� ��������
    assert(list.del_first() == 1);
    assert(list.sizes() == 2);

    // ��������� �������� ������� ��������
    assert(list.del_first() == 2);
    assert(list.sizes() == 1);

    // �������� ������� �������� �� ������ � ����� ���������
    assert(list.del_first() == 3);
    assert(list.sizes() == 0);

    // ������� �������� �� ������� ������
    assert(list.del_first() == 0);
}

///���� ������ ���� � ������
void test_find() {
    List<int> list;

    //��������� �������� � ������
    list.add_last(1);
    list.add_last(2);
    list.add_last(3);

    // ������������ ������ ������������� ��������
    assert(list.find(2) != nullptr);

    // ������������ ������ ��������������� ��������
    assert(list.find(5) == nullptr);

    List<int> list1;

    //��������� �������� � ������
    list1.add_last(1.3);
    list1.add_last(2.5);
    list1.add_last(3.2);

    // ������������ ������ ������������� ��������
    assert(list1.find(2.5) != nullptr);

    // ������������ ������ ��������������� ��������
    assert(list1.find(5) == nullptr);


}

///���� ���������� ���������
void test_sort() {
    List<int> list;

    //��������� �������� � ������
    list.add_last(3);
    list.add_last(1);
    list.add_last(2);

    //������������ ���������� ������
    list.sort();
    assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    assert(list.find(3)->data == 3);

    List<double> list1;

    //��������� �������� � ������
    list1.add_last(3.2);
    list1.add_last(1.3);
    list1.add_last(2.4);

    //������������ ���������� ������
    list1.sort();
    assert(list1.find(1)->data == 1.3);
    assert(list1.find(2)->data == 2.4);
    assert(list1.find(3)->data == 3.2);
}




