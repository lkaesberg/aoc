#include <map>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int getPriority(char item) {
    int priority = (int) item;
    if (item >= 'a' && item <= 'z') priority -= 96;
    if (item >= 'A' && item <= 'Z') priority -= 38;
    return priority;
}

int main() {
    string line;
    string line1;
    string line2;
    ifstream input("../2022/inputs/input03.txt");
    int sum = 0;
    int sumBadges = 0;
    int index = 0;
    if (input.is_open()) {
        while (getline(input, line)) {
            int compartmentSize = line.length() / 2;
            string compartment1 = line.substr(0, compartmentSize);
            string compartment2 = line.substr(compartmentSize, compartmentSize);
            bool itemFound = false;
            for (auto item1: compartment1) {
                for (auto item2: compartment2) {
                    if (item1 == item2) {
                        sum += getPriority(item1);
                        itemFound = true;
                        break;
                    }
                }
                if (itemFound) break;
            }
            if (index % 3 == 0) {
                line1 = line;
            }
            if ((index - 1) % 3 == 0) {
                line2 = line;
            }
            if ((index - 2) % 3 == 0) {
                itemFound = false;
                for (auto item1: line) {
                    for (auto item2: line1) {
                        for (auto item3: line2) {
                            if (item1 == item2 && item2 == item3) {
                                sumBadges += getPriority(item1);
                                itemFound = true;
                                break;
                            }
                        }
                        if (itemFound) break;
                    }
                    if (itemFound) break;
                }
            }
            index++;
        }
        input.close();
    } else cout << "Unable to open file";

    cout << sum << " " << sumBadges;
}