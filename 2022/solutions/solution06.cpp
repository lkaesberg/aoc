#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int main() {
    string line;
    ifstream input("../2022/inputs_uni/input06.txt");
    int numberOfDistinctCharacters = 4;
    if (input.is_open()) {
        while (getline(input, line)) {
            for (int i = numberOfDistinctCharacters - 1; i < line.length(); ++i) {
                set<char> temp;
                for (int j = 0; j < numberOfDistinctCharacters; ++j) {
                    temp.insert(line[i - j]);
                }
                if (temp.size() == numberOfDistinctCharacters) {
                    cout << i + 1;
                    break;
                }
            }
        }
        input.close();
    } else cout << "Unable to open file";
}