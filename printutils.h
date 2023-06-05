#ifndef PRINTUTILS_H
#define PRINTUTILS_H

#include <iostream>
#include <vector>

template <typename T> void print2Dmatrix(std::vector<std::vector<T>> res);
template <typename T> void print2Dmatrix(std::vector<std::vector<T>> res) {
    if (res.empty()) {
        std::cout << "Empty!" << std::endl;
        return;
    }

    int r = res.size();
    int c = res[0].size();

    for (auto row : res) {
        for (auto val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T> void printArray(std::vector<T> arr);
template <typename T> void printArray(std::vector<T> arr) {
    for (auto i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
};

#endif /* PRINTUTILS_H */