//
// Created by Jakub Górski on 13/3/2022 as a recruitment assignment.
//

#include "dictionary.h"

/*
 * Clears the dictionary upon initialization.
 */
Dictionary::Dictionary() {
    for (auto &i : dict){
        i.clear();
    }
}

/*
 * Returns a hash value for a given string key.
 */
int Dictionary::hashFunction(const std::string& key) {
    int hash{};

    // Iterates through every character of the key, gets its ASCII value and adds it to the sum.

    for(const auto &item : key){
        hash += (int) item;
    }

    // Returns remainder of dividing the ASCII sum by 32 (no. Hash Groups)
    return hash % 32;
}

/*
 * Checks if the dictionary is empty.
 */
bool Dictionary::isEmpty() const {
    bool empty = true;
    for (const auto& i : dict){
        if (!i.empty()) empty = false;
    }
    return empty;
}

/*
 * Appends a dPair object to the dictionary.
 * dPair = std::pair<std::string, int>
 */
void Dictionary::append(const dPair& k_v_pair){

    // Gets hash value for given key
    int hashVal = hashFunction(k_v_pair.first);

    // Gets reference to the vector of that hash value
    auto& cell = dict[hashVal];

    // Gets iterator pointing to the first element in the vector
    auto itr = begin(cell);

    // Iterates through the vector to check if the provided key is a duplicate
    for(; itr != end(cell); itr++){
        if (itr->first == k_v_pair.first){
            // Can implement logging to file
            // Throws an error if the provided key is duplicate.
            std::string error = "[ERROR] Specified key: '" + k_v_pair.first + "' is already present in given dictionary and has a value of: " + std::to_string(getValue(k_v_pair.first)) + ".\nPlease use shortened syntax to change the value corresponding to that key.";
            throw std::invalid_argument(error);
        }
    }

    // If duplicate key was not found, pushes back the pair to the dictionary.
    cell.push_back(k_v_pair);
}

/*
 * Appends a key-value pair to the dictionary.
 * key is of type std::string
 * value is of type int
 */
void Dictionary::append(const std::string& key, int value){

    // Gets hash value for given key
    int hashVal = hashFunction(key);

    // Gets reference to the vector of that hash value
    auto& cell = dict[hashVal];

    // Gets iterator pointing to the first element in the vector
    auto itr = begin(cell);

    // Iterates through the vector to check if the provided key is a duplicate
    for(; itr != end(cell); itr++){
        if (itr->first == key){
            // Can implement logging to file
            // Throws an error if the provided key is duplicate.
            std::string error = "[ERROR] Specified key: '" + key + "' is already present in given dictionary and has a value of: " + std::to_string(getValue(key)) + ".\nPlease use shortened syntax to change the value corresponding to that key.";
            throw std::invalid_argument(error);
        }
    }

    // If duplicate key was not found, pushes back the pair to the dictionary. emplace_back() is used here instead of push_back(std::make_pair(key, value) for performance reasons
    cell.emplace_back(key, value);
}

/*
 * Removes a key-value pair from the dictionary.
 * key is of type std::string
 */
void Dictionary::remove(const std::string& key) {

    // Gets hash value for given key
    int hashVal = hashFunction(key);

    // Gets reference to the vector of that hash value
    auto& cell = dict[hashVal];

    // Gets iterator pointing to the first element in the vector
    auto itr = begin(cell);

    // Iterates through the vector to check if the provided key is a duplicate
    for(; itr != end(cell); itr++){
        if (itr->first == key){
            // Can implement: logging to file
            // Removes the pair and then assigns the returned iterator to the one we used. If it didn't, we could face fragmentation issues.
            itr = cell.erase(itr);
            return;
        }
    }

    // Throws an error if the provided key was not found in the dictionary.
    std::string error = "[ERROR] Specified key: '" + key + "' is not present in given dictionary.\nBe sure to use dictionary.append() before trying to get a value.";
    throw std::invalid_argument(error);
}

/*
 * Gets value from the key-value pair.
 * key is of type std::string
 * returns an int
 */
int Dictionary::getValue(const std::string& key){

    // Gets hash value for given key
    int hashVal = hashFunction(key);

    // Gets reference to the vector of that hash value
    auto& cell = dict[hashVal];

    // Gets iterator pointing to the first element in the vector
    auto itr = begin(cell);

    // Iterates through the vector to check if the provided key is a duplicate
    for(; itr != end(cell); itr++){
        if (itr->first == key){
            // Can implement: logging to file
            // Returns the value pointed by the key
            return itr->second;
        }
    }

    // Throws an error if the provided key was not found in the dictionary.
    std::string error = "[ERROR] Specified key: '" + key + "' is not present in given dictionary.\nBe sure to use dictionary.append() before trying to get a value.";
    throw std::invalid_argument(error);
}

/*
 * Lists keys in the dictionary. If argument is provided, lists only the hash bucket referred to by the index
 * group_index is of type int
 * returns an std::string
 */
std::string Dictionary::list(int group_index){

    std::string os;

    // If the dictionary is empty, returns a message.
    if(isEmpty()) {
        os += "Empty";
        return os;
    }

    // If argument is not provided, it lists the whole dictionary.
    if (group_index == -1){
        os += "[\n";
        for (const auto &i : dict){
            os += "\t[";
            for (const auto &j : i){
                os += "'" + j.first + "', ";
            }
            os += "]\n";
        }
        os += "]\n";
        return os;
    }

    // If argument is provided, it lists only the hash bucket referred to by the argument
    else if (group_index > 0 && group_index <= 32){
        os += "[";
        for (const auto &j : dict[group_index-1]){
            os += "'" + j.first + "', ";
        }
        os += "]\n";
        return os;
    }

    // In any other case throws out_of_range exception.
    else {
        throw std::out_of_range("[ERROR] Given group index is out of hash table's range. Please, use an index between 1-32.");
    }
}

/*
 * Lists values in the dictionary. If argument is provided, lists only the hash bucket referred to by the index
 * group_index is of type int
 * returns an std::string
 */
std::string Dictionary::values(int group_index){

    std::string os;

    // If the dictionary is empty, returns a message.
    if(isEmpty()) {
        os += "Empty";
        return os;
    }

    // If argument is not provided, it lists the whole dictionary.
    if (group_index == -1){
        os += "[\n";
        for (const auto &i : dict){
            os += "\t[";
            for (const auto &j : i){
                os += "" + std::to_string(j.second) + ", ";
            }
            os += "]\n";
        }
        os += "]\n";
        return os;
    }

    // If argument is provided, it lists only the hash bucket referred to by the argument
    else if (group_index > 0 && group_index <= 32){
        os += "[";
        for (const auto &j : dict[group_index-1]){
            os += "" + std::to_string(j.second) + ", ";
        }
        os += "]\n";
        return os;
    }

    // In any other case throws out_of_range exception.
    else {
        throw std::out_of_range("[ERROR] Given group index is out of hash table's range. Please, use an index between 1-32.");
    }
}

/*
 * Lists keys and corresponding values in the dictionary.
 * returns an std::string
 */
std::string Dictionary::list_all(){

    std::string os;

    // If the dictionary is empty, returns a message.
    if(isEmpty()){
        os += "Empty";
        return os;
    }

    // Else, lists the whole dictionary
    else{
        os += "[\n";
        for (const auto &i : dict){
            os += "\t[";
            for (const auto &j : i){
                os += "'" + j.first + "': " + std::to_string(j.second) + ", ";
            }
            os += "]\n";
        }
        os += "]\n";
        return os;
    }
}

/*
 * Returns number of elements in the dictionary.
 * If argument is provided, returns number of elements in the hash group referred to by the index.
 * Returns an int
 */
int Dictionary::length(int group_index) {
    int length{};

    // If argument isn't specified, returns number of elements in the whole dictionary
    if (group_index == -1){
        for (auto &i: dict) {
            length += i.size();
        }
        return length;
    }

    // If specified argument is within bounds, returns the length of the hash bucket referred to by the index
    else if (group_index > 0 && group_index <= 32) {
        length = dict[group_index-1].size();
        return length;
    }

    // In any other case throws out_of_range exception.
    else {
        throw std::out_of_range("[ERROR] Given group index is out of hash table's range. Please, use an index between 1-32.");
    }
}

/*
 * Clears the dictionary
 * If argument isn't specified, clears the whole dictionary.
 * If argument is specified, clears the hash bucket referred to by the index.
 */
void Dictionary::clear(int group_index) {

    // If argument isn't specified, clears the whole dictionary
    if (group_index == -1){
        for (auto &i : dict){
            i.clear();
        }
    }
    // If specified argument is within bounds, clears the hash bucket referred to by the index
    else if (group_index > 0 && group_index <= 32){
        dict[group_index-1].clear();
    }

    // In any other case throws out_of_range exception.
    else {
        throw std::out_of_range("[ERROR] Given group index is out of hash table's range. Please, use an index between 1-32.");
    }
}

/*
 * Overload for stream insertion operator. Lists whole dictionary.
 */
std::ostream &operator<<(std::ostream& os, Dictionary& D) {
    os << "[\n";
    for (const auto &i : D.dict){
        os << "\t[";
        for (const auto &j : i){
            os << "'" << j.first << "', ";
        }
        os << "]\n";
    }
    os << "]\n";
    return os;
}
