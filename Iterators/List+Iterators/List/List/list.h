//Бусыгина Татьян, ИВТ-22

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//Правило пяти гласит, что если в классе или структуре определен хотя бы один из следующих методов:

// 1. Конструктор копирования
// 2. Оператор присваивания
// 3. Деструктор
// 4. Конструктор перемещения
// 5. Оператор перемещения

// то, вероятно, стоит определить все пять методов для обеспечения правильного управления ресурсами и предотвращения утечек памяти или 
//других проблем с управлением ресурсами. 

///Класс узел двусвязного списка
template <typename T>
class Node
{
public:
    T data; 			//данные узла
    Node<T>* prev;		//указатель на предыдущей узел
    Node<T>* next;		//указатель на следующий узел

    ///Конструктор без параметров
    Node() : prev(nullptr), next(nullptr), data(T()) {}

    ///Конструктор с параметрами, data_- данные узла prev_ - указатель на предыдущий узел, next_ - указатель на следующий узел
    Node(const T& data_, Node<T>* prev_, Node<T>* next_) : data(data_), prev(prev_), next(next_) {}

    ///Конструктор с данными, указатели prev и next указывают на nullptrll, data_ - данные узла
    Node(const T& data_) : data(data_), prev(nullptr), next(nullptr) {}

    ///Конструктор копирования, node то, что копируем
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

    ///Конструктор перемещения, node то, что перемещаем
    Node(Node<T>&& node) : data(node.data), prev(node.prev), next(node.next) //перемещаем указатели
    {
        //предотвращаем утечку памяти при уничтожении временного объекта
        node.prev = nullptr;
        node.next = nullptr;
    }

    ///Оператор копирования, node то, что копируем
    Node<T>& operator=(const Node<T>& node)
    {
        if (this != &node) //проверяем чтобы не было самоприсваивания
        {
            delete prev;
            delete next;

            //копируем всё
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

    ///Оператор перемещения
    Node<T>& operator=(Node<T>&& node)
    {
        if (this != &node) //проверяем чтобы не было самоприсваивания
        {
            data = node.data;
            prev = node.prev;
            next = node.next;

            node.prev = nullptr;
            node.next = nullptr;
        }
        return *this;
    }

    ///Деструктор
    ~Node()
    {
        //Удаляем указатели на предыдущий и следующий узлы
        if (prev != nullptr && next != nullptr)
        {
            prev = nullptr;
            next = nullptr;
        }
    }
};


///Класс двусвязный список
template <typename T>
class List
{
private:
    //Указатель на голову списка
    Node<T>* head;
    //Указатель на конец списка
    Node<T>* tail;
    //Размер списка
    size_t size;
    ///Устанавливает значения в никуда
    void forget() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

public:

    ///Конструктор по умолчанию
    List()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ///Конструктор, заполняющий список
    List(size_t size_, const T& data_) {
        for (size_t i = 0; i < size_; i++) {
            add_last(data_);
        }
    }

    ///Конструктор копирования
    List(const List& other) {
        head = nullptr;
        tail = nullptr;
        size = 0;
        //Копируем элементы из другого списка
        copy(other);
    }

    ///Конструктор перемещения
    List(List&& other) {
        //Перемещаем элементы из другого списка
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
        // Проверка
        if (place < 0 || place >= size)
        {
            throw out_of_range("Invalid index");
        }

        Node<T>* current = head;

        for (size_t i = 0; i < place; i++)
        {
            current = current->next;
        }
        // Просматриваем и возращаем
        return current;
    }

    ///Очищение списка
    void clear() {
        //Удаляем все узлы из списка
        while (head != nullptr) {
            Node<T>* next_node = head->next;
            delete head;
            head = next_node;
        }
        forget();
    }

    //Копирование списка (глубокое)
    void copy(const List<T>& other) {
        clear();

        Node<T>* current = other.head;
        while (current != nullptr) {
            add_last(current->data);
            current = current->next;
        }
    }

    ///Оператор присваивания копированием
    List& operator=(const List& other) {
        if (this == &other) {
            return *this;
        }

        //очищаем текущий список
        clear();

        //копируем элементы из другого списка
        copy(other);

        return *this;
    }

    ///Оператор присваивания перемещением
    List& operator=(List&& other) {
        if (this == &other) {
            return *this;
        }
        //Очищаем текущий список
        clear();
        //Перемещаем элементы из другого списка
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.forget();
        return *this;
    }

    ///Деструктор
    ~List() {
        clear();//очищаем список
    }

    ///Добавление элемента в начало списка
    //Сложность O(1)
    void add_first(const T& data) {
        //Создаем новый узел
        Node<T>* new_node = new Node<T>(data);

        //Если список пуст, то новый узел становится головным и хвостовым
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        }
        else {
            //Иначе добавляем новый узел в начало списка
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        //Увеличиваем размер списка
        size++;
    }

    ///Добавляет элемент в конец списка
    //Сложность O(1)
    void add_last(const T& data) {
        //Создаем новый узел
        Node<T>* new_node = new Node<T>(data);
        //Если список пуст, то новый узел становится головным и хвостовым
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        }
        else {
            //Иначе добавляем новый узел в конец списка
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        //Увеличиваем размер списка
        size++;
    }


    ///Удаляет последний элемент из списка
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

    ///Удаляет первый элемент из списка
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

    ///Находит узел со значением, равным key
    //Сложность O(n)
    Node<T>* find(const T& key)
    {
        //ищем узел со значением, равным key
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    ///Возвращает размер списка
    //Сложность O(1)
    size_t sizes() const {
        return size;
    }


    ///Сортировка списка пузырьком по возрастанию
    //Сложность O(n^2)
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

    ///Конкатенация (объединение) двух списков, other - список, который добавляем
    //Сложность О(n)
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

    //Класс Итератор для прохождения по элементам списка и удобного доступа к их данным.
    class Iterator {
    private:
        Node<T>* current; //указатель на текущий узел в списке
    public: 
        Iterator(Node<T>* head):
            current(head) {}

        //Оператор для сравнения текущего узла итератора с другим итератором. True - указывают на разные узлы.
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        //Оператор для получения доступа к данным текущего узла, на который указывает итератор
        T& operator*() const {
            return current->data;
        }

        //Метод проверяет, есть ли следующий элемент в списке
        bool hasNext() {
            return current != nullptr;
        }

        //Метод перемещает итератор на следующий узел. Если нет узла, то кидается исключение.
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

        //Инкременция итератора
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

        //Возвращает итератор на начало списка
        Iterator begin() { return Iterator(head); }

        //Возвращает итератор на конец списка
        Iterator end() { return Iterator(nullptr); }
    
};

///Тест итератора
void test_iterator() {
    List<int> list;
    list.add_last(1);
    list.add_last(2);
    list.add_last(3);

    auto it = list.begin();
    assert(*it == 1); // Проверка первого элемента
    ++it; // Переход к следующему элементу
    assert(*it == 2); // Проверка второго элемента
    ++it; // Переход к следующему элементу
    assert(*it == 3); // Проверка третьего элемента
    ++it; // Переход к следующему элементу

    try
    {
        ++it;
        assert(false); // Должно произойти исключение
    }
    catch (const std::out_of_range& e)
    {
        // Исключение должно быть поймано
        assert(true);
    }

    for_each(list.begin(), list.end(), [](int& element)
        { cout << element << " "; });

    cout << endl;

    // For по коллекции 
    for (int value : list) {
        cout << value << ' ' << endl;
    }

    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << ' ' << endl;
    }

    cout << endl;
}

///Тест конкатенации
void test_concatenate() {
    List<int> list1;
    List<int> list2;

    //добавляем элементы в оба списка
    list1.add_last(1);
    list1.add_last(2);
    list2.add_last(3);
    list2.add_last(4);

    //тестирование конкатенации непустых списков
    list1.concatenate(list2);
    assert(list1.sizes() == 4);
    assert(list1.find(1)->data == 1);
    assert(list1.find(2)->data == 2);
    assert(list1.find(3)->data == 3);
    assert(list1.find(4)->data == 4);

    //проверка, что второй список стал пустым после конкатенации
    assert(list2.sizes() == 0);
}


///Тест добавления узла в начало списка
void test_add_first() {
    List<int> list;

    // Тестирование добавления элемента в пустой список
    list.add_first(1);
    assert(list.sizes() == 1);
    assert(list.get_head()->data == 1);
    assert(list.get_tail()->data == 1);

    // Добавляем еще элементы в список
    list.add_first(2);
    list.add_first(3);

    // Тестирование добавления элементов в начало списка
    assert(list.sizes() == 3);
    assert(list.get_head()->data == 3);
    assert(list.get_tail()->data == 1);
    assert(list.get_head()->next->data == 2);
    assert(list.get_tail()->prev->data == 2);
}


///Тест добавления узла в конец списка
void test_add_last() {
    List<int> list;

    // Тестирование добавления элемента в пустой список
    list.add_last(5);
    assert(list.get_head() != nullptr);
    assert(list.get_tail() != nullptr);
    assert(list.get_tail()->data == 5);
    assert(list.sizes() == 1);

    // Тестирование добавления элемента в непустой список
    list.add_last(10);
    assert(list.get_tail()->data == 10);
    assert(list.get_tail()->prev->data == 5);
    assert(list.get_tail()->prev->next == list.get_tail());
    assert(list.sizes() == 2);
}

///Тест удаления последнего узла из списка
void test_del_last() {
    List<int> list;

    // Тестирование удаления из пустого списка
    assert(list.del_last() == 0);

    // Добавляем элементы в список
    list.add_last(1);
    list.add_last(2);
    list.add_last(3);

    // Тестирование удаления последнего элемента
    assert(list.del_last() == 3);
    assert(list.sizes() == 2);

    // Повторное удаление последнего элемента
    assert(list.del_last() == 2);
    assert(list.sizes() == 1);

    // Удаление последнего элемента из списка с одним элементом
    assert(list.del_last() == 1);
    assert(list.sizes() == 0);

    // Попытка удаления из пустого списка
    assert(list.del_last() == 0);
}

///Тест удаления первого узла из списка
void test_del_first() {
    List<int> list;

    // Тестирование удаления из пустого списка
    assert(list.del_first() == 0);

    // Добавляем элементы в список
    list.add_last(1);
    list.add_last(2);
    list.add_last(3);

    // Тестирование удаления первого элемента
    assert(list.del_first() == 1);
    assert(list.sizes() == 2);

    // Повторное удаление первого элемента
    assert(list.del_first() == 2);
    assert(list.sizes() == 1);

    // Удаление первого элемента из списка с одним элементом
    assert(list.del_first() == 3);
    assert(list.sizes() == 0);

    // Попытка удаления из пустого списка
    assert(list.del_first() == 0);
}

///Тест поиска узла в списке
void test_find() {
    List<int> list;

    //Добавляем элементы в список
    list.add_last(1);
    list.add_last(2);
    list.add_last(3);

    // Тестирование поиска существующего элемента
    assert(list.find(2) != nullptr);

    // Тестирование поиска несуществующего элемента
    assert(list.find(5) == nullptr);

    List<int> list1;

    //Добавляем элементы в список
    list1.add_last(1.3);
    list1.add_last(2.5);
    list1.add_last(3.2);

    // Тестирование поиска существующего элемента
    assert(list1.find(2.5) != nullptr);

    // Тестирование поиска несуществующего элемента
    assert(list1.find(5) == nullptr);


}

///Тест сортировки пузырьком
void test_sort() {
    List<int> list;

    //Добавляем элементы в список
    list.add_last(3);
    list.add_last(1);
    list.add_last(2);

    //Тестирование сортировки списка
    list.sort();
    assert(list.find(1)->data == 1);
    assert(list.find(2)->data == 2);
    assert(list.find(3)->data == 3);

    List<double> list1;

    //Добавляем элементы в список
    list1.add_last(3.2);
    list1.add_last(1.3);
    list1.add_last(2.4);

    //Тестирование сортировки списка
    list1.sort();
    assert(list1.find(1)->data == 1.3);
    assert(list1.find(2)->data == 2.4);
    assert(list1.find(3)->data == 3.2);
}




