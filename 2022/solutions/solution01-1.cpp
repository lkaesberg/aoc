//
// Created by Larsk on 01.12.2022.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> inventoryOfElves;
    string line;
    ifstream input("../2022/inputs/input01-1.txt");
    int currentElv = 0;

    inventoryOfElves.push_back(0);
    if (input.is_open()) {
        while (getline(input, line)) {
            if (line == "") {
                currentElv++;
                inventoryOfElves.push_back(0);
                continue;
            }
            inventoryOfElves[currentElv] += stoi(line);
        }
        input.close();
    } else cout << "Unable to open file";
    int maxCalories = 0;
    sort(inventoryOfElves.begin(), inventoryOfElves.end(), greater<>());
    cout << "Problem1: " << inventoryOfElves[0] << "\n";
    cout << "Problem2: " << inventoryOfElves[0] + inventoryOfElves[1] + inventoryOfElves[2] << "\n";

}