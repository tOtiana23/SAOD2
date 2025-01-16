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
/// Функция хэширования FNV-1a
/// </summary>
/// <typeparam name="Key"></typeparam>
/// <param name="key"></param>
/// <returns></returns>
template <typename Key>
size_t fnv1aHash(const Key& key) {
	size_t hash = 2166136261; //стандартное значение для 32-разрядной версии
	auto key_hash = std::hash<Key>{}(key); //создаётся экземпляр стандартной хэш-функции и вычилсяется хэш для ключа
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
	double min_load; //минимальная степень загруженности таблицы
public:

	/// <summary>
	/// Стандартная хэш функция
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	//static size_t hashFunction(const Key& value) {
	//	return fnv1aHash(value);
	//}



	//в hash_function_argument мы присваиваем хэш-функцию по умолчанию, а hash_function(hash_function_argument) инициализируем поле класса заданным значением
	HashTable(size_t table_size, function<size_t(const Key&)> hash_function_argument = fnv1aHash<Key>, double max_load = 0.7, double min_load = 0.2) :
		table(table_size), size(0), hash_function(hash_function_argument), load(0.0), max_load(max_load), min_load(min_load){}

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
	/// 
	/// Можно задать конкертно хэш-функцию, тогда получится
	/// size_t hash(const Key& key) const {
	//	return fnv1aHash(key);
	//}
	size_t hash(const Key& key) const {
		return hash_function(key);
	}

	/// <summary>
	/// Удаление ключа из таблицы. Исключение если ключ не найден
	/// Сложность О(1) - лучшая; O(n) - средняя и худшая.
	/// </summary>
	/// <param name="value">Значение ключа, который необходимо удалить</param>
	void remove(const Key& value) {
		size_t index = hash_function(value) % table.size();
		auto it = find(table[index].begin(), table[index].end(), value); //ищем. it тип итератора
		if (it != table[index].end()) { //проверяем, что нашли
			table[index].erase(it); //удаляем и разбираемся с последствиями удаления
			size--;
			load = (double)size / table.size();
			if (load < min_load) { //если коэффициент загрузки меньше минимального, то делаем рехэширование
				rehash_decrease();
			}
		}
		else {
			throw runtime_error("Key not found");
		}
	}

	/// <summary>
	/// Рехэширование. Сделать еще уменьшение
	/// </summary>
	void rehash() {
		vector<list<Key>> newTable(table.size() * 2);
		for (const auto& list : table) {
			for (const auto& key : list) {
				size_t index = hash_function(key) % table.size();
				newTable[index].push_back(key);
			}
		}
		table.swap(newTable); //обновляем ссылку на таблицу
		load = (double)size / table.size();
	}

	void rehash_decrease() {
		if (table.size() > 1) { // Уменьшаем только если размер больше 1
			vector<list<Key>> newTable(table.size() / 2);
			for (const auto& list : table) {
				for (const auto& key : list) {
					size_t index = hash_function(key) % newTable.size();
					newTable[index].push_back(key);
				}
			}
			table.swap(newTable); //обновляем ссылку на таблицу
			load = (double)size / table.size();
		}
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

	void print() {
		for (size_t i = 0; i < table.size(); ++i) {
			std::cout << "Index " << i << ": ";
			for (const auto& item : table[i]) {
				std::cout << item << " ";
			}
			std::cout << "\n";
		}
	}
};

template <typename Key>
size_t easy_hash(const Key& key) {
	return key%5;
}

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

	HashTable<int> collision(5, easy_hash<int>);
	collision.insert(10); // hash(10) % 5 = 0
	collision.insert(15); // hash(15) % 5 = 0 (коллизия)
	collision.insert(20); // hash(20) % 5 = 0 (коллизия)

	assert(collision.contains(10));
	assert(collision.contains(15));
	assert(collision.contains(20));

	collision.print();
}

//для небольшой таблицы или легкой хэш-функции подобрать значения чтоб была коллизия