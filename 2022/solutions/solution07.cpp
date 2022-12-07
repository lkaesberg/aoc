#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct file {
    string name;
    file *parent;
    map<string, file *> children;
    bool isDirectory = false;
    int size = 0;
};

vector<string> split(string text, char split) {
    stringstream textStream(text);
    string part;
    vector<string> parts;
    while (getline(textStream, part, split)) {
        parts.push_back(part);
    }
    return parts;
}

void sumSmallDirectories(file *root, int *sum) {
    for (auto [name, file]: root->children) {
        if (file->isDirectory && file->size <= 100000) {
            *sum += file->size;
        }
        sumSmallDirectories(file, sum);
    }
}

void deleteDirectory(file *root, int neededSpace, int *smallest) {
    for (auto [name, file]: root->children) {
        if (file->isDirectory && file->size >= neededSpace && file->size < *smallest) {
            *smallest = file->size;
        }
        deleteDirectory(file, neededSpace, smallest);
    }
}


int main() {
    string line;
    ifstream input("../2022/inputs/input07.txt");
    file root;
    root.isDirectory = true;
    root.name = "/";

    file *currentFile = &root;

    if (input.is_open()) {
        while (getline(input, line)) {
            cout << "Current Folder " << currentFile->name << endl;
            if (line[0] == '$') {
                if (line == "$ cd /") {
                    cout << "Goto root" << endl;
                    currentFile = &root;
                } else if (line == "$ cd ..") {
                    cout << "Goto " << currentFile->parent->name << endl;
                    currentFile = currentFile->parent;
                } else if (line.starts_with("$ cd")) {
                    auto parts = split(line, ' ');
                    cout << "Goto " << parts[2] << endl;
                    currentFile = currentFile->children[parts[2]];
                }
            } else {
                if (line.starts_with("dir")) {
                    auto parts = split(line, ' ');
                    cout << "Add directory " << parts[1] << endl;
                    file *newDirectory = new file;
                    newDirectory->isDirectory = true;
                    newDirectory->name = parts[1];
                    newDirectory->parent = currentFile;
                    currentFile->children[parts[1]] = newDirectory;
                } else {
                    auto parts = split(line, ' ');
                    cout << "Add file " << parts[1] << endl;
                    file *newFile = new file;
                    newFile->name = parts[1];
                    newFile->size = stoi(parts[0]);
                    newFile->parent = currentFile;
                    file *next = newFile;
                    while (next != &root) {
                        next->parent->size += newFile->size;
                        next = next->parent;
                    }
                    currentFile->children[parts[1]] = newFile;
                }
            }
        }
        input.close();
    } else cout << "Unable to open file";
    int sum = 0;
    sumSmallDirectories(&root, &sum);
    cout << sum << endl;
    int smallestDeleteDirectory = INT_MAX;
    cout << root.size << endl;
    cout << 30000000 - (70000000 - root.size) << endl;
    deleteDirectory(&root, 30000000 - (70000000 - root.size), &smallestDeleteDirectory);
    cout << smallestDeleteDirectory << endl;

}