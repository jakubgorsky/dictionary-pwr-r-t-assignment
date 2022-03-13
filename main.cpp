#include <iostream>
#include "dictionary.h"

// Helper function to populate the dictionary
std::string gen_random_string(const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

int main() {
    Dictionary dict;
    // Populating the dictionary with random entries
    for (int i{}; i < 100; i++){
        dict.append(gen_random_string(5),(rand()%9999));
    }
    dict.append("Key1", 1);
    std::cout << dict << "\n";
    std::cout << dict.list_all();
    std::cout << dict.values(4);
    std::cout << dict.list(4);
    dict.remove("Key1");
    std::cout << dict;
    dict.clear(5);
    std::cout << dict.length(1) << "\n";
    std::cout << dict;
}