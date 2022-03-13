//
// Created by Jakub Górski on 13/3/2022 as a recruitment assignment.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <vector>
#include <utility>
#include <iostream>


typedef std::pair<std::string, int> dPair;
typedef std::vector<std::pair<std::string, int>> dictionary[32];

class Dictionary {
    private:
        dictionary dict;
        static int hashFunction(const std::string& key);
    public:
        Dictionary();

        bool isEmpty() const;

        void append(const dPair &k_v_pair);

        void append(const std::string &, int);

        int getValue(const std::string& key);

        void remove(const std::string& key);

        std::string list(int group_index = -1);

        std::string values(int values = -1);

        std::string list_all();

        void clear(int group_index = -1);

        int length(int group_index = -1);

        /*
         * Overload for subscript operator.
         * Returns a reference to value provided by a key within the brackets.
         * Can also be used to modify a value under a certain key
         * Example usage:
         * int value = dictionary["key1"];
         * dictionary["key3"] = 3;
         */
        auto &operator[] (const std::string &key) {

            // Gets hash value for given key
            int hashVal = hashFunction(key);

            // Gets reference to the vector of that hash value
            auto &cell = dict[hashVal];

            // Gets iterator pointing to the first element in the vector
            auto itr = begin(cell);

            // Iterates through the vector to check if the provided key is a duplicate
            for (; itr != end(cell); itr++) {
                if (itr->first == key) {
                    return itr->second;
                }
            }

            // Throws an error if the provided key is duplicate.
            std::string error = "[ERROR] Specified key: '" + key + "' is not present in given dictionary.\nBe sure to use dictionary.append() before modifying values with shortened syntax.";
            throw std::invalid_argument(error);
        }

        friend std::ostream& operator<<(std::ostream&, Dictionary&);
};

#endif //DICTIONARY_H
