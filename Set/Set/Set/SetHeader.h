//Бусыгина Татьяна, ИВТ-22

#include "HashHeader.h"

/// <summary>
/// Шаблонный класс множества
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename Type>
class Set {
private:
    HashTable<Type> table; //хеш-таблица для хранения ключей

public:
    
    Set(size_t capacity = 10, function<size_t(const Type&)> hashFunction = [](const Type& val) { return fnv1aHash(val); }, double maxLoadFactor = 0.7) : table(capacity, hashFunction, maxLoadFactor) {}

    /// <summary>
    /// добавление элемента
    /// </summary>
    /// <param name="value"></param>
    void insert(const Type& value) {
        if (contains(value))
            return;
        table.insert(value);
    }

    /// <summary>
    /// удаление элемента
    /// </summary>
    /// <param name="value"></param>
    void remove(const Type& value) {
        table.remove(value);
    }

    /// <summary>
    /// проверка на наличие элемента
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    bool contains(const Type& value) const {
        return table.contains(value);
    }

    /// <summary>
    /// размер
    /// </summary>
    /// <returns></returns>
    size_t size() const {
        return table.sizes();
    }
    
    /// <summary>
    /// проверка на пустоту
    /// </summary>
    /// <returns></returns>
    bool empty() const {
        return size() == 0;
    }

};

void testAllMethods() {

    //Test insert, contains, size
    Set<int> s1;
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    assert(s1.size() == 3);
    assert(s1.contains(1));
    assert(s1.contains(2));
    assert(s1.contains(3));
    s1.insert(1);
    assert(s1.size() == 3);


    //Test remove
    Set<int> s2;
    s2.insert(1);
    s2.insert(2);
    s2.insert(3);
    s2.remove(2);
    assert(s2.size() == 2);
    assert(s2.contains(1));
    assert(!s2.contains(2));
    assert(s2.contains(3));


    //Test empty
    Set<int> s3;
    assert(s3.empty());
    s3.insert(1);
    assert(!s3.empty());
}