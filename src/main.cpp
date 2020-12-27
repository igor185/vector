// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

#include "vector/my_vector.h"

using namespace std::chrono;


template<typename container>
void count(container data_out, const std::string &file_name) {
    std::ifstream data{"../data/data.txt"};

    if (!data) {
        std::cerr << "Cannot open file" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string word;
    std::unordered_map<std::string, size_t> words_count;

    while (data >> word)
        ++words_count[word];

    std::ofstream out{file_name};


    data_out.reserve(words_count.size());

    std::sort(data_out.begin(), data_out.end());

    for (auto &&kw: words_count)
        data_out.emplace_back(std::move(kw));

    for (auto &&elem: data_out)
        out << elem.first << "\t:\t" << elem.second << '\n';
}

constexpr int TESTS_AMOUNT = 50;
int main() {

    my_vector<std::pair<std::string, size_t>> my_vct;
    std::string file1 = "../data/res1.txt";

    std::vector<std::pair<std::string, size_t>> vct;
    std::string file2 = "../data/res2.txt";

    long avg1 = 0, avg2 = 0;


    for(int i = 0; i < TESTS_AMOUNT; i++) {
        auto start = high_resolution_clock::now();
        count(my_vct, file1);
        auto stop = high_resolution_clock::now();
        avg1 += duration_cast<microseconds>(stop - start).count();

        start = high_resolution_clock::now();
        count(vct, file2);
        stop = high_resolution_clock::now();
        avg2 += duration_cast<microseconds>(stop - start).count();
    }

    avg1 /= TESTS_AMOUNT;
    avg2 /= TESTS_AMOUNT;

    std::cout << "My vector: " << avg1 << '\n'
        << "STD vector: " << avg2 << std::endl;

    return EXIT_SUCCESS;
}
