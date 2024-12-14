// lab_5 z2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void processFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }

    vector<int> numbers;
    int number;

    // Считываем 
    while (inputFile >> number) {
        numbers.push_back(number);
    }
    inputFile.close();

    
    if (numbers.empty()) {
        cerr << "Error: File is empty or contains invalid data." << endl;
        return;
    }

   
    int lastNumber = numbers.back();

    
    for (int& num : numbers) {
        num += lastNumber;
    }

    // Записываем 
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    for (const int& num : numbers) {
        outputFile << num << "\n";
    }
    outputFile.close();

    cout << "File has been updated successfully." << endl;
}

int main() {
    const string filename = "C:\\Users\\daram\\OneDrive\\Рабочий стол\\ООП\\lab_5 z2\\dada.txt"; 

    processFile(filename);

    return 0;
}
