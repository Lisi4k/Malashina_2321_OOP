#include <iostream>
#include <string>
#include <vector>
using namespace std;

    template <typename T>
    class UPtr {
    private:
        T* ptr;

    public:
        UPtr() : ptr(nullptr) {}

        explicit UPtr(T* p) : ptr(p) {}// с параметром

        UPtr(const UPtr&) = delete;
        UPtr& operator=(const UPtr&) = delete;//присваивания

        UPtr(UPtr&& other) noexcept : ptr(other.ptr) {//перемещения
            other.ptr = nullptr;
        }

        UPtr& operator=(UPtr&& other) noexcept {
            if (this != &other) {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        ~UPtr() {
            delete ptr;
        }

        T* get() const {
            return ptr;
        }

        T* release() {
            T* temp = ptr;
            ptr = nullptr;
            return temp;//уже сырой
        }

        void reset(T* p = nullptr) {
            if (ptr != p) {
                delete ptr;
                ptr = p;
            }
        }

        void swap(UPtr& other) noexcept {
            T* temp = ptr;
            ptr = other.ptr;
            other.ptr = temp;
        }

        T& operator*() const {//оператор доступа(удобно для методов)
            return *ptr;
        }

        T* operator->() const {//Разыменовывание(2 сем)
            return ptr;
        }

        bool is_null() const {
            return ptr == nullptr;
        }
    };



void demo_menu() {
    int choice;
    do {
       cout << "\nМеню:\n"
            << "1. Работа с int\n"
            << "2. Работа с double\n"
            << "3. Работа с string\n"
            << "4. Выход\n"
            << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            UPtr<int> ptr1(new int(42));
            cout << "Указатель ptr1 указывает на: " << *ptr1 << "\n";

            UPtr<int> ptr2 = move(ptr1);
            cout << "После перемещения ptr2 указывает на: " << *ptr2 << "\n";

            ptr2.reset(new int(100));
            cout << "После reset ptr2 указывает на: " << *ptr2 << "\n";

            int* raw = ptr2.release();
            cout << "После release сырой указатель указывает на: " << *raw << "\n";
            delete raw;
            break;
        }
        case 2: {
            UPtr<double> ptr1(new double(3.14));
            cout << "Указатель ptr1 указывает на: " << *ptr1 << "\n";

            UPtr<double> ptr2;
            ptr2.swap(ptr1);
            cout << "После swap ptr2 указывает на: " << *ptr2 << "\n";

            ptr2.reset();
            cout << "После reset ptr2 пустой: " << boolalpha << ptr2.is_null() << "\n";
            break;
        }

        case 3: {
            UPtr<string> ptr1(new string("Привет, мир!"));
            cout << "Указатель ptr1 указывает на: " << *ptr1 << "\n";

            ptr1.reset(new std::string("Уникальный указатель работает!"));
            cout << "После reset ptr1 указывает на: " << *ptr1 << "\n";
            break;
        }
        case 4:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 4);
}

int main() {
    setlocale(0, "RU");
    demo_menu();
    return 0;
}
