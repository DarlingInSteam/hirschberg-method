#include <iostream>
#include <stdexcept>

class Map {
public:
    Map() {
        this->values = new int[26];
    }

    void insert(char c, int value) {
        int index = getIndex(c);
        this->values[index] = value;
    }

    int get(char c) {
        int index = getIndex(c);
        return this->values[index];
    }

    void display() {
        for (int i = 0; i < 26; i++) {
            std::cout << ((char)(i + 97)) << ": " << values[i] << std::endl;
        }
    }

private:
    int getIndex(char c) {
        if (c < 'a' || c > 'z')
            throw std::invalid_argument("Invalid char");
        return c - 97;
    }

    int* values;
};