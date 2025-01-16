//�������� �������, ���-22
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <functional>
#include <algorithm>
#include <string>

using namespace std;

/// <summary>
/// ������� ����������� FNV-1a
/// </summary>
/// <typeparam name="Key"></typeparam>
/// <param name="key"></param>
/// <returns></returns>
template <typename Key>
size_t fnv1aHash(const Key& key) {
	size_t hash = 2166136261; //����������� �������� ��� 32-��������� ������
	auto key_hash = std::hash<Key>{}(key); //�������� ��������� ����������� ���-������� � ����������� ��� ��� �����
	hash = (hash ^ key_hash) * 16777219; //�������� ��� ������������� �����
	return hash;
}


/// <summary>
/// ��������� ����� ���-�������. ������� �������� - ����� �������
/// </summary>
/// <typeparam name="Key"></typeparam>
template <typename Key>
class HashTable {
private:
	vector<list<Key>> table; //������ ������� ��� �������� ������
	function<size_t(const Key&)> hash_function; //��� �������
	size_t size; //������ �������
	double load; //������� ������������� �������
	double max_load; //������������ ������� ������������� �������
	double min_load; //����������� ������� ������������� �������
public:

	/// <summary>
	/// ����������� ��� �������
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	//static size_t hashFunction(const Key& value) {
	//	return fnv1aHash(value);
	//}



	//� hash_function_argument �� ����������� ���-������� �� ���������, � hash_function(hash_function_argument) �������������� ���� ������ �������� ���������
	HashTable(size_t table_size, function<size_t(const Key&)> hash_function_argument = fnv1aHash<Key>, double max_load = 0.7, double min_load = 0.2) :
		table(table_size), size(0), hash_function(hash_function_argument), load(0.0), max_load(max_load), min_load(min_load){}

	/// <summary>
	/// ������� ����� � �������
	/// ��������� �(1) - ������; O(2n) - ������� � ������.
	/// </summary>
	/// <param name="value">�������� �����, ������� ���������� ��������</param>
	void insert(const Key& value) {
		size_t index = hash_function(value) % table.size();
		//�������� �� ��������. �������� ��������� ������ ������ � �������, ���� ������ ���, �� ��������� ��� � ������, ����� ������ �� ������
		if (find(table[index].begin(), table[index].end(), value) == table[index].end()) {
			table[index].push_back(value); //��������� �������� � ������
		}
		size++;
		load = (double) size / table.size();
		if (load > max_load) { //���� ����������� �������� ��������� ������������, �� ������ �������������
			rehash();
		}
	}

	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	/// 
	/// ����� ������ ��������� ���-�������, ����� ���������
	/// size_t hash(const Key& key) const {
	//	return fnv1aHash(key);
	//}
	size_t hash(const Key& key) const {
		return hash_function(key);
	}

	/// <summary>
	/// �������� ����� �� �������. ���������� ���� ���� �� ������
	/// ��������� �(1) - ������; O(n) - ������� � ������.
	/// </summary>
	/// <param name="value">�������� �����, ������� ���������� �������</param>
	void remove(const Key& value) {
		size_t index = hash_function(value) % table.size();
		auto it = find(table[index].begin(), table[index].end(), value); //����. it ��� ���������
		if (it != table[index].end()) { //���������, ��� �����
			table[index].erase(it); //������� � ����������� � ������������� ��������
			size--;
			load = (double)size / table.size();
			if (load < min_load) { //���� ����������� �������� ������ ������������, �� ������ �������������
				rehash_decrease();
			}
		}
		else {
			throw runtime_error("Key not found");
		}
	}

	/// <summary>
	/// �������������. ������� ��� ����������
	/// </summary>
	void rehash() {
		vector<list<Key>> newTable(table.size() * 2);
		for (const auto& list : table) {
			for (const auto& key : list) {
				size_t index = hash_function(key) % table.size();
				newTable[index].push_back(key);
			}
		}
		table.swap(newTable); //��������� ������ �� �������
		load = (double)size / table.size();
	}

	void rehash_decrease() {
		if (table.size() > 1) { // ��������� ������ ���� ������ ������ 1
			vector<list<Key>> newTable(table.size() / 2);
			for (const auto& list : table) {
				for (const auto& key : list) {
					size_t index = hash_function(key) % newTable.size();
					newTable[index].push_back(key);
				}
			}
			table.swap(newTable); //��������� ������ �� �������
			load = (double)size / table.size();
		}
	}

	
	/// <summary>
	/// �������� ������� ����� � �������
	/// ��������� �(1) - ������; O(n) - ������� � ������.
	/// </summary>
	/// <param name="key"></param>
	/// <returns>True - ���� ���� ����, False - ���� ���</returns>
	bool contains(const Key& key) const {
		size_t index = hash_function(key) % table.size();
		return find(table[index].begin(), table[index].end(), key) != table[index].end();
	}

	/// <summary>
	/// ���������� ������ � �������
	/// </summary>
	size_t sizes() const {
		return size;
	}

	/// <summary>
	/// ���������� ��������� � �������
	/// </summary>
	size_t capacity() const {
		return table.size();
	}

	/// <summary>
	/// ������� �������� �������
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
	//���� � �������-��������
	HashTable<string> stringTable(5);
	stringTable.insert("apple");
	stringTable.insert("banana");
	stringTable.insert("cherry");
	assert(stringTable.contains("apple"));
	assert(stringTable.contains("banana"));
	assert(!stringTable.contains("date"));
	stringTable.remove("banana");
	assert(!stringTable.contains("banana"));

	//���� � �������-�������
	HashTable<int> intTable(5);
	intTable.insert(10);
	intTable.insert(20);
	intTable.insert(30);
	assert(intTable.contains(10));
	assert(intTable.contains(20));
	assert(!intTable.contains(40));
	intTable.remove(20);
	assert(!intTable.contains(20));


	//���� �������
	intTable.clear();
	assert(intTable.sizes() == 0);
	assert(!intTable.contains(10));
	assert(!intTable.contains(30));

	HashTable<int> collision(5, easy_hash<int>);
	collision.insert(10); // hash(10) % 5 = 0
	collision.insert(15); // hash(15) % 5 = 0 (��������)
	collision.insert(20); // hash(20) % 5 = 0 (��������)

	assert(collision.contains(10));
	assert(collision.contains(15));
	assert(collision.contains(20));

	collision.print();
}

//��� ��������� ������� ��� ������ ���-������� ��������� �������� ���� ���� ��������