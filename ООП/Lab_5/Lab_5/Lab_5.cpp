#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;


class CharProcessor {
public:
    
    explicit CharProcessor(char inputChar) : character(inputChar) {}

    
    void toLowerCase() {
        character = tolower(character);
    }

    
    void printDetails() const {
        cout << "Символ: " << character << ", Шестнадцатеричный: 0x" << hex << uppercase << int(character) << ", Восьмеричный: 0" << oct << int(character) << endl;
    }

private:
    char character; 
};


int main() {
    setlocale(0, "RU");
    string input;
    cout << "Введите строку: ";
    getline(cin, input);

    for (char c : input) {
        CharProcessor processor(c);
        processor.toLowerCase();
        processor.printDetails();
    }

    return 0;
}