#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>

using namespace std;

void printStack(stack<char> s) {
    // If stack is empty then return
    if (s.empty())
        return;


    char x = s.top();

    // Pop the top element of the stack
    s.pop();

    // Recursively call the function printStack
    printStack(s);

    // Print the stack element starting
    // from the bottom
    cout << x << " ";

    // Push the same element onto the stack
    // to preserve the order
    s.push(x);
}

stack<char> reverseStack(stack<char> normalStack) {
    stack<char> tmpStack;
    while (!normalStack.empty()) {
        tmpStack.push(normalStack.top());
        normalStack.pop();
    }
    return tmpStack;
}

vector<int> getNumberFromString(string s) {
    stringstream str_strm;
    str_strm << s; //convert the string s into stringstream
    string temp_str;
    int temp_int;
    vector<int> numbers;
    while (!str_strm.eof()) {
        str_strm >> temp_str; //take words into temp_str one by one
        if (stringstream(temp_str) >> temp_int) { //try to convert string to int
            numbers.push_back(temp_int);
        }
        temp_str = ""; //clear temp string
    }
    return numbers;
}

int main() {
    string line;
    ifstream input("../2022/inputs/input05.txt");

    vector<stack<char>> crateTower;

    bool loadingCreates = true;

    if (input.is_open()) {
        while (getline(input, line)) {
            if (line.length() == 0) {
                loadingCreates = false;

                for (auto &tower: crateTower) {
                    tower.pop();
                    tower = reverseStack(tower);
                    printStack(tower);
                    cout << endl;
                }

                continue;
            }
            if (loadingCreates) {
                for (int i = crateTower.size(); i < (line.length() - 3) / 4 + 1; ++i) {
                    crateTower.push_back(*new stack<char>());
                }
                for (int i = 1; i < line.length(); i += 4) {
                    if (line[i] == ' ') continue;
                    crateTower[(i - 1) / 4].push(line[i]);
                }

            } else {
                auto instructions = getNumberFromString(line);
                stack<char> crane;
                for (int i = 0; i < instructions[0]; ++i) {
                    crane.push(crateTower[instructions[1] - 1].top());
                    crateTower[instructions[1] - 1].pop();
                }
                while (!crane.empty()) {
                    crateTower[instructions[2] - 1].push(crane.top());
                    crane.pop();
                }
                cout << "-------------------" << endl;
                for (const auto &tower: crateTower) {
                    printStack(tower);
                    cout << endl;
                }
            }
        }
        input.close();
    } else cout << "Unable to open file";
    cout << "-------------------" << endl;

    for (auto tower: crateTower) {
        if (!tower.empty()) cout << tower.top();
    }
}