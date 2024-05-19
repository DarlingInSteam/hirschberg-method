#pragma once


class Map {
public:
    Map();

    void insert(char c, int value);
    int get(char c);
    void display();

private:
    int getIndex(char c);
    int* values;
};