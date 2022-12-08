#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool isVisible(vector<vector<int>> treeGrid, int x, int y, int width, int height) {
    auto value = treeGrid[y][x];
    bool visible = true;
    for (int i = x - 1; i >= 0; --i) {
        if (treeGrid[y][i] >= value) {
            visible = false;
        }
    }
    if (visible) return true;
    visible = true;
    for (int i = x + 1; i < width; ++i) {
        if (treeGrid[y][i] >= value) {
            visible = false;
        }
    }
    if (visible) return true;
    visible = true;
    for (int i = y - 1; i >= 0; --i) {
        if (treeGrid[i][x] >= value) {
            visible = false;
        }
    }
    if (visible) return true;
    visible = true;
    for (int i = y + 1; i < height; ++i) {
        if (treeGrid[i][x] >= value) {
            visible = false;
        }
    }
    if (visible) return true;
    return false;
}

int scenicScore(vector<vector<int>> treeGrid, int x, int y, int width, int height) {
    auto value = treeGrid[y][x];
    int score = 1;
    for (int i = x - 1; i >= 0; --i) {
        if (treeGrid[y][i] >= value || i == 0) {
            score *= x - i;
            break;
        }
    }
    for (int i = x + 1; i < width; ++i) {
        if (treeGrid[y][i] >= value || i == width - 1) {
            score *= i - x;
            break;
        }
    }
    for (int i = y - 1; i >= 0; --i) {
        if (treeGrid[i][x] >= value || i == 0) {
            score *= y - i;
            break;
        }
    }
    for (int i = y + 1; i < height; ++i) {
        if (treeGrid[i][x] >= value || i == height - 1) {
            score *= i - y;
            break;
        }
    }
    return score;
}

int main() {
    string line;
    ifstream input("../2022/inputs/input08.txt");

    vector<vector<int>> treeGrid;

    if (input.is_open()) {
        while (getline(input, line)) {
            vector<int> treeLine;
            for (auto tree: line) {
                treeLine.push_back(stoi(string(1, tree)));
            }
            treeGrid.push_back(treeLine);
        }
        input.close();
    } else cout << "Unable to open file";
    int count = 0;
    int highestScore = 0;
    int width = treeGrid[0].size();
    int height = treeGrid.size();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto score = scenicScore(treeGrid, x, y, width, height);
            cout << score << " ";
            if (score > highestScore) {
                highestScore = score;
            }
            if (isVisible(treeGrid, x, y, width, height)) {
                count++;
            }
        }
        cout << endl;

    }
    cout << count << endl;
    cout << highestScore << endl;
}