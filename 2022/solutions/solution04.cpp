#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> split(string text, char split) {
    stringstream textStream(text);
    string part;
    vector<string> parts;
    while (getline(textStream, part, split)) {
        parts.push_back(part);
    }
    return parts;
}

vector<int> splitToInt(string text, char split) {
    stringstream textStream(text);
    string part;
    vector<int> parts;
    while (getline(textStream, part, split)) {
        parts.push_back(stoi(part));
    }
    return parts;
}

int min(int value1, int value2) {
    if (value1 < value2) return value1;
    return value2;
}

int max(int value1, int value2) {
    if (value1 > value2) return value1;
    return value2;
}

int main() {
    string line;
    ifstream input("../2022/inputs/input04.txt");
    int counter = 0;
    int counterPairs = 0;
    if (input.is_open()) {
        while (getline(input, line)) {
            auto elfRanges = split(line, ',');
            auto elf1Range = splitToInt(elfRanges[0], '-');
            auto elf2Range = splitToInt(elfRanges[1], '-');
            auto lowerBound = max(elf1Range[0], elf2Range[0]);
            auto upperBound = min(elf1Range[1], elf2Range[1]);
            if (upperBound >= lowerBound) {
                counterPairs++;
            }
            if (elf1Range[0] >= elf2Range[0] && elf1Range[1] <= elf2Range[1]) {
                counter++;
            } else if (elf2Range[0] >= elf1Range[0] && elf2Range[1] <= elf1Range[1]) {
                counter++;
            }
        }
        input.close();
    } else cout << "Unable to open file";
    cout << counter << " " << counterPairs << endl;
}