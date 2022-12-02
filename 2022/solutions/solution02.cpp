//
// Created by Larsk on 01.12.2022.
//
#include <map>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

map<char, int> choiceToPoints = {
        {'A', 1},
        {'B', 2},
        {'C', 3}
};

map<char, int> outcomeToPoints = {
        {'X', 0},
        {'Y', 3},
        {'Z', 6}
};

map<char, char> decryptChoice = {
        {'X', 'A'},
        {'Y', 'B'},
        {'Z', 'C'}
};
map<char, char> choiceToWin = {
        {'A', 'C'},
        {'B', 'A'},
        {'C', 'B'}
};

map<char, char> choiceToLose = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'A'}
};

int win(char yourChoice, char opponentChoice) {
    if (yourChoice == opponentChoice) return 3;
    if (opponentChoice == choiceToWin[yourChoice]) return 6;
    return 0;
}

int predictChoice(char outcome, char opponentChoice) {
    if (outcome == 'Y') return choiceToPoints[opponentChoice];
    if (outcome == 'X') return choiceToPoints[choiceToWin[opponentChoice]];
    return choiceToPoints[choiceToLose[opponentChoice]];
}

int score1(char yourChoice, char opponentChoice) {
    yourChoice = decryptChoice[yourChoice];
    return choiceToPoints[yourChoice] + win(yourChoice, opponentChoice);
}

int score2(char outcome, char opponentChoice) {
    return predictChoice(outcome, opponentChoice) + outcomeToPoints[outcome];
}


int main() {
    string line;
    ifstream input("../2022/inputs_uni/input02.txt");

    int points1 = 0;
    int points2 = 0;

    if (input.is_open()) {
        while (getline(input, line)) {
            points1 += score1(line[2], line[0]);
            points2 += score2(line[2], line[0]);
        }
        input.close();
    } else cout << "Unable to open file";

    cout << "Total score1: " << points1 << endl;
    cout << "Total score2: " << points2 << endl;

}