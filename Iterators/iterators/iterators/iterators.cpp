//Бусыгина Татьяна, ИВТ-22

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    vector<int> numbers = {7, 10, 8, 11, 36};

    cout << "Изначальный массив: ";
    //for_each: выводим каждый элемент вектора
    for_each(numbers.begin(), numbers.end(), [](int n) {
        cout << n << " ";
    });
    
    //any_of: проверяем, есть ли хотя бы одно число равное 7. Останавливается на первом элементе, который удовлетворяет заданному условию
    bool has_even = any_of(numbers.begin(), numbers.end(), [](int n) {
        return n == 7;
    });
    cout << endl << "Есть ли числа равные 7? " << (has_even ? "Да" : "Нет") << endl;

    //all_of: поверяем, все ли числа отрицательные
    bool all_negative = all_of(numbers.begin(), numbers.end(), [](int n) {
        return n < 0;
    });
    cout << "Все числа отрицательные? " << (all_negative ? "Да" : "Нет") << endl;

    //none_of: проверяем, нет ли отрицательных чисел
    bool no_negative = none_of(numbers.begin(), numbers.end(), [](int n) {
        return  n < 0;
    });
    cout << "Есть отрицательные числа? " << (no_negative ? "Нет" : "Да") << endl;

    //transform: умножаем каждое число на 5. Применяет заданную функцию к каждому элементу диапазона и записывает результат в другой диапазон
    vector<int> numbers2(numbers.size());
    transform(numbers.begin(), numbers.end(), numbers2.begin(), [] (int n) {
        return n * 5;
    });
    cout << "Числа после умножения на 5: ";
    for (int n : numbers2) {
        cout << n << " ";
    }
    cout << endl;

    //copy_if: копируем четные числа в новый вектор
    //back_inserter это специальный итератор, который позволяет добавлять элементы в конец контейнера even_numbers. Он создает 
    //объект, который будет вызывать метод push_back у even_numbers каждый раз, когда в него будет записан элемент
    vector<int> even_numbers;
    copy_if(numbers.begin(), numbers.end(), back_inserter(even_numbers), [](int n) {
        return n % 2 == 0;
        });
    cout << "Четные числа: ";
    for (int n : even_numbers) {
        cout << n << " ";
    }
    cout << endl;





}