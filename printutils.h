#ifndef PRINTUTILS_H
#define PRINTUTILS_H

#include <iostream>
#include <vector>

// Utility functions

template <typename T> void print2Dmatrix(std::vector<std::vector<T>> matrix);
template <typename T> void print2Dmatrix(std::vector<std::vector<T>> matrix) {
    if (matrix.empty()) {
        std::cout << "Matrix Empty!" << std::endl;
        return;
    }

    for (std::vector<T> row : matrix) {
        if (row.empty()) {
            std::cout << "Empty!" << std::endl;
            continue;
        }

        for (auto val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
};

template <typename T> void printArray(std::vector<T> arr);
template <typename T> void printArray(std::vector<T> arr) {
    if (arr.empty()) {
        std::cout << "Empty!" << std::endl;
        return;
    }

    for (auto i : arr)
        std::cout << i << " ";
    std::cout << std::endl << std::endl;
};

template <typename T> void printPairArray(std::vector<std::pair<T, T>> arr);
template <typename T> void printPairArray(std::vector<std::pair<T, T>> arr) {
    if (arr.empty()) {
        std::cout << "Empty!" << std::endl;
        return;
    }

    for (auto i : arr)
        std::cout << i.first << "," << i.second << " ";
    std::cout << std::endl << std::endl;
};

#endif /* PRINTUTILS_H */
