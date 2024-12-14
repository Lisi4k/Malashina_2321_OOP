#include <iostream>
#include <string>
#include <regex>
#include <fstream>
using namespace std;

class Bitmap {
public:
    Bitmap(const string& filename) : filename(filename) {}

    pair<int, int> getSizeFromFile() { 
        
        ifstream file(filename, ios::binary);
        if (!file) {
            throw runtime_error("Не удалось открыть файл: " + filename);
        }

        file.seekg(18); //байты. по 4 на каждый
        int width = 0, height = 0;
        file.read(reinterpret_cast<char*>(&width), sizeof(width));
        file.read(reinterpret_cast<char*>(&height), sizeof(height));
        return make_pair(width, height);
    }

private:
    string filename;
};


class ImageProxy {
public:
    ImageProxy(const string& filename) : filename(filename) {}

    pair<int, int> getSize() {
        regex pattern("_(\\d+)x(\\d+)\\.bmp$"); //из JS регвыр
        smatch match;

        if (regex_search(filename, match, pattern)) {
            int width = stoi(match[1]);
            int height = stoi(match[2]);//строка в число
            return make_pair(width, height);
        }
        else {
            
            Bitmap bmp(filename);
            return bmp.getSizeFromFile();
        }
    }

private:
    string filename;
};

int main() {
    setlocale(0, "Ru");
    try {
        
        ImageProxy img1("lolkek_1920x1080.bmp");
        pair<int, int> size1 = img1.getSize();
        cout << "Размер lolkek_1920x1080.bmp: " << size1.first << "x" << size1.second << endl;

        ImageProxy img2("rabstol_735x360.bmp");
        pair<int, int> size2 = img2.getSize();
        cout << "Размер rabstol_735x360.bmp: " << size2.first << "x" << size2.second << endl;

        ImageProxy img3("strannik_4444.bmp");
        pair<int, int> size3 = img3.getSize();
        cout << "Размер strannik_1920x1080.bmp: " << size3.first << "x" << size3.second << endl;

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
