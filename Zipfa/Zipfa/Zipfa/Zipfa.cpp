#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <codecvt>

using namespace std;

// Функция для обработки слов (удаление пунктуации, приведение к нижнему регистру)
wstring preprocess(const wstring& word) {
    wstring result;
    for (wchar_t ch : word) {
        if (iswalpha(ch)) {
            result += towlower(ch);
        }
    }
    return result;
}

// Функция для чтения файла и подсчета частоты слов
map<wstring, size_t> countWordFrequency(const wstring& file_name) {
    wifstream file(file_name);
    file.imbue(locale("ru_RU.UTF-8"));
    if (!file.is_open()) {
        wcerr << L"Не удалось открыть файл" << endl;
        exit(1);
    }

    map<wstring, size_t> word_frequency;
    wstring word;

    while (file >> word) {
        word = preprocess(word);
        if (!word.empty()) {
            word_frequency[word]++;
        }
    }
    file.close();
    return word_frequency;
}

// Функция для сортировки слов по частоте
vector<pair<wstring, size_t>> sortWordFrequency(const map<wstring, size_t>& word_frequency) {
    vector<pair<wstring, size_t>> word_vector(word_frequency.begin(), word_frequency.end());

    sort(word_vector.begin(), word_vector.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Сортируем по убыванию частоты
        });

    return word_vector;
}

// Функция для вывода результатов на экран
void printWordFrequency(const vector<pair<wstring, size_t>>& word_vector) {
    wcout << setw(10) << L"Ранг" << setw(20) << L"Слово" << setw(20) << L"Частота" << endl;
    size_t rank = 1;
    for (size_t i = 0; i < word_vector.size(); ++i) {
        wcout << setw(10) << rank << setw(20) << word_vector[i].first << setw(20) << word_vector[i].second << endl;
        rank++;
    }
}

// Функция для записи результатов в CSV файл
void writeWordFrequencyToCSV(const vector<pair<wstring, size_t>>& word_vector) {
    wofstream output_file("word_frequency.csv");
    output_file.imbue(locale("ru_RU.UTF-8"));
    output_file << L"Rank,Word,Frequency\n"; // Заголовки столбцов
    size_t rank = 1;
    for (const auto& entry : word_vector) {
        output_file << rank << L"," << entry.first << L"," << to_wstring(entry.second) << L"\n"; // Записываем данные
        rank++;
    }
    output_file.close();
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wstring file_name;

    wcout << L"Введите имя файла (.txt): ";
    wcin >> file_name;

    // Подсчет частоты слов
    auto word_frequency = countWordFrequency(file_name);

    // Сортировка слов по частоте
    auto sorted_word_vector = sortWordFrequency(word_frequency);

    // Вывод результатов на экран
    printWordFrequency(sorted_word_vector);

    // Запись результатов в CSV файл
    writeWordFrequencyToCSV(sorted_word_vector);

    return 0;
}
