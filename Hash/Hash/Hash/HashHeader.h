//Бусыгина Татьяна, ИВТ-22
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <functional>
#include <algorithm>
#include <string>

using namespace std;

/// <summary>
/// Сложность O(k), где k - размер key
/// </summary>
/// <typeparam name="Key"></typeparam>
/// <param name="key"></param>
/// <returns></returns>
template <typename Key>
size_t complexHash(const Key& key) {
	const size_t prime1 = 73856093;
	const size_t prime2 = 19349663;
	const size_t prime3 = 83492791;
	size_t hash = 0;

	for (size_t i = 0; i < key.size(); ++i) {
		hash ^= (hash << 5) + (hash >> 2) + key[i] * prime1; 
		//hash << 5 сдвиг значения hash влево на 5 бит. Это эквивалентно умножению на 32.
		//hash >> 2 — сдвиг значения hash вправо на 2 бита.Это эквивалентно делению на 4.
		//key[i] * prime1 — умножение текущего символа ключа на первое простое число.
		//Все эти значения комбинируются с помощью операции XOR
		hash += prime2; //добавляем простое число
		hash ^= (hash << 13) + (hash >> 7) + key[i] * prime3;
	}

	return hash;
}

/// <summary>
/// Функция хэширования FNV-1a
/// </summary>
/// <typeparam name="Key"></typeparam>
/// <param name="key"></param>
/// <returns></returns>
template <typename Key>
size_t fnv1aHash(const Key& key) {
	size_t hash = 2166136261; //стандартное значение для 32-разрядной версии
	auto key_hash = hash<Key>{}(key);
	hash = (hash ^ key_hash) * 16777219; //умножаем для перемешивания битов
	return hash;
}


/// <summary>
/// Шаблонный класс хэш-таблицы. Решение коллизий - метод цепочек
/// </summary>
/// <typeparam name="Key"></typeparam>
template <typename Key>
class HashTable {
private:
	vector<list<Key>> table; //массив списков для хранения ключей
	function<size_t(const Key&)> hash_function; //хэш функция
	size_t size; //размер таблицы
	double load; //степень загруженности таблицы
	double max_load; //максимальная степень загруженности таблицы
public:

	/// <summary>
	/// Стандартная хэш функция
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	static size_t hashFunction(const Key& value) {
		return fnv1aHash(value);
	}

	HashTable(size_t table_size, function<size_t(const Key&)> hash_function = hashFunction, double max_load = 0.7) :
		table(table_size), size(0), hash_function(hashFunction), load(0.0), max_load(max_load) {}

	/// <summary>
	/// Вставка ключа в таблицу
	/// Сложность О(1) - лучшая; O(2n) - средняя и худшая.
	/// </summary>
	/// <param name="value">Значение ключа, который необходимо вставить</param>
	void insert(const Key& value) {
		size_t index = hash_function(value) % table.size();
		//проверка на коллизию. Итератор проверяет каждый индекс в таблице, если такого нет, то добавляем его в список, иначе ничего не делаем
		if (find(table[index].begin(), table[index].end(), value) == table[index].end()) {
			table[index].push_back(value); //добавляем значение в список
		}
		size++;
		load = (double) size / table.size();
		if (load > max_load) { //если коэффициент загрузки превышает максимальный, то делаем рехэширование
			rehash();
		}
	}

	/// <summary>
	/// Хэширование
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	size_t hash(const Key& key) const {
		return hash_function(key);
	}

	/// <summary>
	/// Удаление ключа из таблицы
	/// Сложность О(1) - лучшая; O(n) - средняя и худшая.
	/// </summary>
	/// <param name="value">Значение ключа, который необходимо удалить</param>
	void remove(const Key& value) {
		size_t index = hash_function(value) % table.size();
		auto it = find(table[index].begin(), table[index].end(), value); //ищем
		if (it != table[index].end()) { //проверяем, что нашли
			table[index].erase(it); //удаляем и разбираемся с последствиями удаления
			size--;
			load = (double)size / table.size();
		}
		else {
			throw runtime_error("Key not found");
		}
	}

	/// <summary>
	/// Рехэширование. 
	/// </summary>
	void rehash() {
		vector<list<Key>> newTable(table.size() * 2);
		for (const auto& list : table) {
			for (const auto& key : list) {
				size_t index = hash_function(key) % table.size();
				newTable[index].push_back(key);
			}
		}
		table = newTable; //обновляем ссылку на таблицу
		load = (double)size / table.size();
	}

	/// <summary>
	/// Проверка наличия ключа в таблице
	/// Сложность О(1) - лучшая; O(n) - средняя и худшая.
	/// </summary>
	/// <param name="key"></param>
	/// <returns>True - если ключ есть, False - если нет</returns>
	bool contains(const Key& key) const {
		size_t index = hash_function(key) % table.size();
		return find(table[index].begin(), table[index].end(), key) != table[index].end();
	}

	/// <summary>
	/// Количество ключей в таблице
	/// </summary>
	size_t sizes() const {
		return size;
	}

	/// <summary>
	/// Количество элементов в таблице
	/// </summary>
	size_t capacity() const {
		return table.size();
	}

	/// <summary>
	/// Очистка значений таблицы
	/// </summary>
	void clear() {
		for (auto& list : table) {
			list.clear();
		}
		size = 0;
		load = 0.0;
	}
};


void testHashTable() {
	//Тест с ключами-строками
	HashTable<string> stringTable(5);
	stringTable.insert("apple");
	stringTable.insert("banana");
	stringTable.insert("cherry");
	assert(stringTable.contains("apple"));
	assert(stringTable.contains("banana"));
	assert(!stringTable.contains("date"));
	stringTable.remove("banana");
	assert(!stringTable.contains("banana"));

	//Тест с ключами-числами
	HashTable<int> intTable(5);
	intTable.insert(10);
	intTable.insert(20);
	intTable.insert(30);
	assert(intTable.contains(10));
	assert(intTable.contains(20));
	assert(!intTable.contains(40));
	intTable.remove(20);
	assert(!intTable.contains(20));


	//Тест очистки
	intTable.clear();
	assert(intTable.sizes() == 0);
	assert(!intTable.contains(10));
	assert(!intTable.contains(30));
}