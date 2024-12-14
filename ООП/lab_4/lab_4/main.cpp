#include <iostream>
#include "vect.h"
#include "exceptions.h"
using namespace std;

void menu() {
    cout << "Menu:\n";
    cout << "1. Add element\n";
    cout << "2. Get element by index\n";
    cout << "3. Display size\n";
    cout << "4. Clear\n";
    cout << "5. Exit\n";
}

int main() {
    try {
        Vect<std::string> vect; 
        int choice;

        do {
            menu();
            cout << "Enter choice: ";
            cin >> choice;

            // Проверка ввода для выбора пункта меню
            if (!std::cin) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cerr << "Invalid input. Please enter a valid choice.\n";
                continue;
            }

            switch (choice) {
            case 1: {
                string value;
                cin.ignore(); // Убираем остаток символов
                cout << "Enter string: ";
                getline(std::cin, value); // Корректно вводим строку
                vect.push_back(value);
                cout << "Added.\n";
                break;
            }
            case 2: {
                size_t index;
                cout << "Enter index: ";
                cin >> index;
                if (!cin) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cerr << "Invalid input. Try again.\n";
                    break;
                }
                try {
                    cout << "Element: " << vect[index] << "\n";
                }
                catch (const VectException& e) {
                    cerr << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 3:
                cout << "Size: " << vect.get_size() << "\n";
                break;
            case 4:
                vect.clear();
                cout << "Vect cleared.\n";
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cerr << "Invalid choice. Try again.\n";
            }
        } while (choice != 5);

    }
    catch (const VectException& e) {
        cerr << "Error: " << e.what() << "\n";
    }
    catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << "\n";
    }

    return 0;
}
