#include <map>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    string line;
    ifstream input("../2022/inputs/input03.txt");
    if (input.is_open()) {
        while (getline(input, line)) {
        }
        input.close();
    } else cout << "Unable to open file";
}