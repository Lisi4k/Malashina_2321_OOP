#include <iostream>
#include "vect.h"
#include "exceptions.h"

using namespace std;

void menu() {
    cout << "\nМеню:\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Вывести элемент по индексу\n";
    cout << "3. Показать размер коллекции\n";
    cout << "4. Очистить коллекцию\n";
    cout << "5. Пройтись по коллекции (слева направо)\n";
    cout << "6. Пройтись по коллекции (справа налево)\n";
    cout << "7. Выход\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(0, "RU");
    Vect<int> vect; // класс Vect для хранения чисел
    int choice;

    do {
        menu();
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Некорректный ввод. Попробуйте снова.\n";
            continue;
        }

        try {
            switch (choice) {
            case 1: { 
                int value;
                cout << "Введите значение: ";
                cin >> value;
                vect.push_back(value);
                cout << "Элемент добавлен.\n";
                break;
            }
            case 2: { 
                size_t index;
                cout << "Введите индекс: ";
                cin >> index;
                cout << "Элемент: " << vect[index] << "\n";
                break;
            }
            case 3: 
                cout << "Размер коллекции: " << vect.get_size() << "\n";
                break;
            case 4: 
                vect.clear();
                cout << "Коллекция очищена.\n";
                break;
            case 5: {
                cout << "Коллекция (слева направо): ";
                auto iterator = vect.forward_iterator();
                while (iterator.has_next()) {
                    cout << iterator.next() << " ";
                }
                cout << "\n";
                break;
            }
            case 6: { 
                cout << "Коллекция (справа налево): ";
                auto iterator = vect.reverse_iterator();
                while (iterator.has_next()) {
                    cout << iterator.next() << " ";
                }
                cout << "\n";
                break;
            }
            case 7: 
                cout << "Выход из программы.\n";
                break;
            default:
                cerr << "Некорректный выбор. Попробуйте снова.\n";
            }
        }
        catch (const VectException& e) {
            cerr << "Ошибка: " << e.what() << "\n";
        }
        catch (const exception& e) {
            cerr << "Непредвиденная ошибка: " << e.what() << "\n";
        }

    } while (choice != 7);

    return 0;
}
