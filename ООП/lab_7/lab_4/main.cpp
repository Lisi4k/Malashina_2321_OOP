#include <iostream>
#include "vect.h"
#include "exceptions.h"

using namespace std;

void menu() {
    cout << "\n����:\n";
    cout << "1. �������� �������\n";
    cout << "2. ������� ������� �� �������\n";
    cout << "3. �������� ������ ���������\n";
    cout << "4. �������� ���������\n";
    cout << "5. �������� �� ��������� (����� �������)\n";
    cout << "6. �������� �� ��������� (������ ������)\n";
    cout << "7. �����\n";
    cout << "��� �����: ";
}

int main() {
    setlocale(0, "RU");
    Vect<int> vect; // ����� Vect ��� �������� �����
    int choice;

    do {
        menu();
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "������������ ����. ���������� �����.\n";
            continue;
        }

        try {
            switch (choice) {
            case 1: { 
                int value;
                cout << "������� ��������: ";
                cin >> value;
                vect.push_back(value);
                cout << "������� ��������.\n";
                break;
            }
            case 2: { 
                size_t index;
                cout << "������� ������: ";
                cin >> index;
                cout << "�������: " << vect[index] << "\n";
                break;
            }
            case 3: 
                cout << "������ ���������: " << vect.get_size() << "\n";
                break;
            case 4: 
                vect.clear();
                cout << "��������� �������.\n";
                break;
            case 5: {
                cout << "��������� (����� �������): ";
                auto iterator = vect.forward_iterator();
                while (iterator.has_next()) {
                    cout << iterator.next() << " ";
                }
                cout << "\n";
                break;
            }
            case 6: { 
                cout << "��������� (������ ������): ";
                auto iterator = vect.reverse_iterator();
                while (iterator.has_next()) {
                    cout << iterator.next() << " ";
                }
                cout << "\n";
                break;
            }
            case 7: 
                cout << "����� �� ���������.\n";
                break;
            default:
                cerr << "������������ �����. ���������� �����.\n";
            }
        }
        catch (const VectException& e) {
            cerr << "������: " << e.what() << "\n";
        }
        catch (const exception& e) {
            cerr << "�������������� ������: " << e.what() << "\n";
        }

    } while (choice != 7);

    return 0;
}
