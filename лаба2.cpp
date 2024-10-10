#include <iostream>            
#include <vector>             
#include <deque>              
#include <list>               
#include <fstream>            
#include <iterator>           
#include <algorithm>          
#include <stdexcept>          
#include <string>             
#include <limits>            

using namespace std;          

// Функция для ввода целых чисел с проверкой
int inputInteger(const string& prompt = "Введите целое число: ", bool showPrompt = true) {
    int number;  
    while (true) {  
        if (showPrompt) {  // Если нужно показать подсказку
            cout << prompt;  
        }
        if (cin >> number) {  // Если ввод успешен
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем оставшийся ввод в буфере
            return number;  
        } else {  
            cout << "Ошибка: введено не целое число. Пожалуйста, попробуйте снова." << endl;  
            cin.clear();  // Сбрасываем состояние потока ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем буфер
        }
    }
}

// Задание 1
void task1(const string& filename) {
    ifstream infile(filename); 
    if (!infile.is_open()) {  
        cout << "Ошибка открытия файла." << endl;  
        return;  
    }

    vector<int> V;  // Создаем вектор 
    int num;  
    while (infile >> num) {  
        V.push_back(num);  // Добавляем прочитанное число в вектор
    }

    if (!infile.eof()) {  // достигнут ли конец файла
        cout << "Ошибка: файл содержит неверный формат данных." << endl; 
        infile.close();  // 
        return;  // 
    }

    infile.close();  

    cout << "Содержимое вектора в порядке ввода: ";  
    for (const auto& elem : V) {  // Проходим по всем элементам вектора
        cout << elem << " ";  // Выводим каждый элемент
    }
    cout << endl;  
}

// Задание 2
void task2() {
    int nV = inputInteger("Введите количество элементов для вектора: ");  

    if (nV % 2 != 0) {  
        cout << "Ошибка: введено нечетное количество элементов для вектора." << endl;  
        return;  
    }

    vector<int> V(nV);  // Создаем вектор фиксированной длины
    cout << "Введите элементы вектора: ";  
    for (int i = 0; i < nV; i++) {  // Цикл для ввода элементов
        V[i] = inputInteger("", false); 
    }

    vector<int> originalV = V;  // Сохраняем оригинальные элементы вектора

    int nD = inputInteger("Введите количество элементов для дека: "); 

    if (nD % 2 != 0) {
        cout << "Ошибка: введено нечетное количество элементов для дека." << endl;  
        return;  
    }

    deque<int> D(nD);  // Создаем дек фиксированной длины
    cout << "Введите элементы дека: ";  
    for (int i = 0; i < nD; i++) {  // Цикл для ввода элементов
        D[i] = inputInteger("", false);  
    }

    size_t halfSizeV = V.size() / 2;  // Вычисляем половину размера вектора
    size_t halfSizeD = D.size() / 2;  // Вычисляем половину размера дека

    V.insert(V.end(), D.begin(), D.begin() + halfSizeD);  // Добавляем первую половину дека в конец вектора
    D.insert(D.begin(), originalV.rbegin(), originalV.rbegin() + halfSizeV);  // Добавляем реверс оригинального вектора в начало дека

    cout << "Обновленный вектор: ";  
    for (const auto& elem : V) {  // Проходим по всем элементам вектора
        cout << elem << " ";  // Выводим каждый элемент
    }
    cout << endl;  // Переход на новую строку

    cout << "Обновленный дек: ";  
    for (const auto& elem : D) {  // Проходим по всем элементам дека
        cout << elem << " ";  
    }
    cout << endl;  // Переход на новую строку
}

// Задание 3
void task3() {
    int n = inputInteger("Введите количество целых чисел для вектора: ");  

    vector<int> V;  // Создаем вектор для хранения чисел
    cout << "Введите " << n << " целых чисел: "; 
    for (int i = 0; i < n; ++i) {  
        V.push_back(inputInteger("", false));  // Вводим числа и добавляем их в вектор
    }

    auto it = V.begin();  // Инициализируем итератор для вектора
    int index = 1;  // Счетчик для определения нечетных номеров

    
    while (it != V.end()) {  // Пока не достигнут конец вектора
        if (index % 2 != 0) {  
            it = V.erase(it);  // Удаляем элемент и обновляем итератор
        } else {  // Если индекс четный
            ++it;  // Просто перемещаем итератор вперед
        }
        ++index;  // Увеличиваем индекс
    }

    cout << "Вектор после удаления элементов с нечетными порядковыми номерами: ";  
    for (const auto& elem : V) {  // Проходим по всем элементам вектора
        cout << elem << " ";  
    }
    cout << endl;  
}

// Задание 4
void task4(const string& filename) {
    ifstream infile(filename);  
    if (!infile.is_open()) { 
        cerr << "Ошибка открытия файла." << endl;  
        return;  // 
    }

    // Считываем целые числа из файла в вектор
    vector<int> numbers((istream_iterator<int>(infile)), istream_iterator<int>());  // Используем итераторы для чтения чисел
    infile.close();  

    // Проверяем, есть ли хотя бы одно число для вывода
    if (numbers.empty()) {  // Если вектор пуст
        cout << "Файл пуст или не содержит чисел." << endl; 
        return;  
    }

    // Выводим числа с нечетными порядковыми номерами 
    cout << "Числа с нечетными порядковыми номерами: ";  
    for (size_t i = 0; i < numbers.size(); i += 2) {  // Проходим по всем нечетным индексам
        cout << numbers[i] << " ";  // Выводим элемент с нечетным индексом
    }
    cout << endl;  
}

// Задание 5
void task5() {
    int N = inputInteger("Введите количество элементов в векторе: ");  
    vector<int> V(N);  // Создаем вектор фиксированной длины
    
    cout << "Введите " << N << " элементов вектора: ";  
    for (int i = 0; i < N; ++i) {  // Цикл для ввода элементов
        cin >> V[i];  // Вводим элемент
    }

    int K = inputInteger("Введите K (количество элементов для дублирования): ");  
    
    if (K <= 0 || K > V.size()) {  // Проверяем, корректно ли введено значение K
        cout << "Некорректное значение K." << endl;  
        return;  
    }

    vector<int> sequence(V.begin(), V.begin() + K);  // Копируем первые K элементов в новый вектор
    

    V.insert(V.end(), sequence.begin(), sequence.end());  // Добавляем скопированные элементы в конец вектора

    cout << "Вектор после дублирования: ";  
    for (const auto& elem : V) {  
        cout << elem << " ";  
    }
    cout << endl;  
}

// Задание 6
void task6() {
    int n, input;  // Переменные для хранения количества элементов и введенных значений
    
    // Список 1
    cout << "Введите количество элементов в первом списке (четное): ";  
    cin >> n;  // Вводим количество элементов
    
    if (n % 2 != 0) {  
        cout << "Ошибка: количество элементов должно быть четным." << endl;  
        return;  
    }
    
    list<int> L1;  // Создаем первый список
    cout << "Введите " << n << " элементов для первого списка: ";  
    for (int i = 0; i < n; ++i) {  // Цикл для ввода элементов
        cin >> input;  // Вводим элемент
        L1.push_back(input);  // Добавляем элемент в список
    }
    
    auto mid1 = next(L1.begin(), n / 2);  // Нахождение середины списка
    list<int> L1_copy(n / 2);  // Создание временного списка для хранения копии первой половины
    reverse_copy(L1.begin(), mid1, L1_copy.begin());  // Копируем и реверсируем первую половину в L1_copy
    L1.insert(L1.end(), L1_copy.begin(), L1_copy.end());  // Вставляем реверсированную половину в конец первого списка
    
    // Список 2
    cout << "Введите количество элементов во втором списке (четное): ";  
    cin >> n; 
    
    if (n % 2 != 0) {  
        cout << "Ошибка: количество элементов должно быть четным." << endl;  
        return; 
    }
    
    list<int> L2;  // Создаем второй список
    cout << "Введите " << n << " элементов для второго списка: ";  
    for (int i = 0; i < n; ++i) {  // Цикл для ввода элементов
        cin >> input;  // Вводим элемент
        L2.push_back(input);  // Добавляем элемент в список
    }
    
    auto mid2 = next(L2.begin(), n / 2);  // Нахождение середины второго списка
    L2.insert(L2.end(), make_reverse_iterator(mid2), make_reverse_iterator(L2.begin()));  // Добавляем реверсированную первую половину в конец второго списка
    
    
    cout << "Первый список после дублирования: ";  
    for (const auto& elem : L1) {  
        cout << elem << " ";  
    }
    cout << endl;  

    cout << "Второй список после дублирования: ";  
    for (const auto& elem : L2) {  // Проходим по всем элементам второго списка
        cout << elem << " ";  
    }
    cout << endl;  
}

// Главная функция
int main() {
    while (true) {
        int taskNumber = inputInteger("Выберите задачу (1-6) или 0 для выхода: ");

        
        if (taskNumber < 0 || taskNumber > 6) {
            cout << "Неверный выбор, пожалуйста, попробуйте снова." << endl;
            continue; // Переходим к следующей итерации цикла
        }

        switch (taskNumber) {
            case 1: 
                task1("name"); 
                break; 

            case 2: 
                task2(); 
                break; 

            case 3: 
                task3(); 
                break; 

            case 4: 
                task4("name"); 
                break; 

            case 5: 
                task5(); 
                break; 

            case 6: 
                task6(); 
                break; 

            case 0:  
                cout << "Выход из программы." << endl;
                return 0; 
        }
    }
}
 
