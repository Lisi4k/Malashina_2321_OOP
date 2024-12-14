#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

class CustomException : public exception {
private:
    string message;
    double value;
    int errorCode;
public:
    CustomException(string msg, double val, int code) : message(msg), value(val), errorCode(code) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
    double getValue() const {
        return value;
    }
    int getErrorCode() const {
        return errorCode;
    }
};


double calculatez1(double b) {
    if (b * b - 4 < 0) { //мегаважная формула на отрицательные числа
        throw CustomException("Отрицательное значение под корнем в Z1", b, 1);
    }
    double numerator = sqrt(2 * b + 2 * sqrt(b * b - 4));
    double denominator = sqrt(b * b - 4) + b + 2;

    if (denominator == 0) {
        throw CustomException("Деление на ноль в Z1", denominator, 1);
    }

    return numerator / denominator;
}


double calculatez2(double b) {
    if (b + 2 < 0) { //мегаважная формула на знаменатель
        throw CustomException("Отрицательное значение под корнем в Z2", b, 2);
    }
    double denominator = sqrt(b + 2);
    if (denominator == 0) {
        throw CustomException("Деление на ноль в Z2", denominator, 2);
    }
    return 1 / denominator;
}

int main() {
    setlocale(0, "RU");
    double b;
    cout << "Введите значение для b: ";
    cin >> b;

    try {
        double Z1 = calculatez1(b);
        double Z2 = calculatez2(b);

        cout << "Z1 = " << Z1 << endl;
        cout << "Z2 = " << Z2 << endl;
        if (fabs(Z1 - Z2) < 1e-6) {
            cout << "Z1 и Z2 приблизительно равны." << endl;
        }
        else {
            cout << "Z1 и Z2 не равны." << endl;
        }
    }
    catch (const CustomException& e) {
        cout << "Поймано исключение: " << e.what() << endl;
        cout << "Значение ошибки: " << e.getValue() << endl;
        cout << "Код ошибки: " << e.getErrorCode() << endl;
    }
    catch (const exception& e) {
        cout << "Стандартное исключение: " << e.what() << endl;
    }

    return 0;
}
