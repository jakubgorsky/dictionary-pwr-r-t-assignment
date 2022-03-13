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
    std::cout << "Empty: " << dict.isEmpty() << "\n";
    // Populating the dictionary with random entries
    for (int i{}; i < 30; i++){
        dict.append(gen_random_string(5),(rand()%9999));
    }
    std::cout << "Empty: "<< dict.isEmpty() << "\n";

    dict.append("Key1", 1);
    dict.append(dPair("key2", 2));

    std::cout << "Value of \'key2\': " << dict.getValue("key2") << "\n";

    std::cout << dict.list_all();

    std::cout << "Values in hash bucket 4: " << dict.values(4) << "\n";
    std::cout << "Keys in hash bucket 4: " << dict.list(4) << "\n";

    dict.remove("Key1");
    try{
        std::cout << dict["Key1"] << "\n";
    }
    catch (std::invalid_argument e){
        std::cout << e.what() << "\n";
    }
    dict.clear(5);
    std::cout << "No. elements in hash bucket 1: " << dict.length(1) << "\n";
    std::cout << "No. elements in whole dictionary: " << dict.length() << "\n";
    std::cout << dict;
}