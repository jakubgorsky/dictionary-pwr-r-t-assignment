# C++ Dictionary
Simple C++ implementation of Python's dictionary based on separate chaining hash table.

### CREATED AS A RECRUITMENT ASSIGNMENT FROM PWR RACING TEAM

Included main.cpp is for demonstration purposes only, you do not have to download it in order to use this class.

# Prequisites
I don't think there are any, but I am using a C++14 compiler, so be sure to use at least that.

# Usage

## There are two things you need to know before using this object.

1. This dictionary uses its own alias for `std::pair<std::string, int>`, namely `dPair`. You can use it to append to the dictionary, as so:
```Cpp
dictionary.append(dPair("key", 1);
```
2. Hash group indexing starts from 1 and ends at 32. In total, there are 32 groups you can freely analyze using methods described below. This object automatically converts user input indecies into array indecies (namely subtracts 1 from them). 

To use the dictionary simply include the header file in your desired .cpp file.

First, you need to initialize the dicionary:
```Cpp
#include "dictionary.h"

Dictionary dictionary;
```
Then, you have a variety of methods at your disposal to manipulate the data contained within:
```Cpp
void append(const dPair& k_v_pair);
void append(const std::string& key, int value);
void remove(const std::string& key);
int getValue(const std::string& key);
std::string list(int group_index);
std::string values(int group_index);
std::string list_all();
void clear(int group_index = -1);
int length(int group_index = -1);
```

### Appending to the dictionary
```Cpp 
append(const dPair& k_v_pair);
```
Takes in `dPair` as an argument (`typedef std::pair<std::string, int> dPair;`) and appends passed key-value pair to the dictionary.
```Cpp 
append(const std::string& key, int value);
```
Does the same thing, but with separate `std::string` and `int` variables.

Both methods throw `std::invalid_argument` exception if the provided key is duplicate.

#### Examples:
```Cpp 
std::pair<std::string, int> kv_pair = std::make_pair("key", 1);
dictionary.append(kv_pair);
...
dictionary.append("key2", 2);
```

### Removing from the dictionary
```Cpp
remove(const std::string& key);
```

Takes in an `std::string` key as an argument and removes key-value pair pointed by the key. Throws `std::invalid_argument` exception if key was not found in the dictionary.

#### Example:
```Cpp
dictionary.remove("key2");
```

### Reading from the dictionary

Althought there is a short-hand syntax for reading and modifying key-value pairs (further described under [short-hand syntax](#short-hand-syntax)), you can get a value of a corresponding key by invoking `getValue(const std::string& key)` method. It takes in a key of type `std::string` and returns value of type `int`.

If the key-value pair was not found it throws an `std::invalid_argument` exception.

#### Example:
```Cpp
dictionary.append("key3", 3);
std::cout << dictionary.getValue("key3");
```
Output:
```
3
```

### Listing the dictionary

By default argument equals to `-1` and lists the whole dictionary (keys only). The same applies for `.values(int group_index)`. All listing methods return a string.
Throws an `std::out_of_range` exception if `group_index` is not within `0 < group_index <= 32`.

Althought there is an operator overload for `std::ostream` (further described under [short-hand syntax](#short-hand-syntax)) you can list a particular chain (or group) under specified hash value (1-32).

There are three methods for listing the data stored in the dictionary. One for keys, one for values, one for both.

#### Example:
```Cpp
std::cout << dictionary.list(4);
std::cout << dictionary.values(4);
```
Output:
```
['key1', 'key2', 'key15', ] // lists chain four of 32
[1, 2, 15, ] // lists chain four of 32
// list_all() produces a very long output, similar to doing std::cout << dictionary (but with values too)
```
**Important:** *Provided output does not reflect any real-life scenario because of how the hashing function works. It is only meant for showing what it looks like.*

### Clearing the dictionary

```Cpp
void clear(int group_index = -1);
```
If argument is not provided, clears the whole dictionary. If it is provided, clears only the specified hash group.

#### Example:
```Cpp
dictionary.clear(4); // clears fourth hash group
dictionary.clear(); // clears whole dictionary
```

### Getting the length (number of elements) of the dictionary

To get the number of elements in the dictionary, simply print or assign the return value of the `length()` method (returns an `int`). If you want to go deeper, you can specify an index of a hash group and get its number of elements.

#### Example:
```Cpp
std::pair<std::string, int> kv_pair = std::make_pair("key", 1);
dictionary.append(kv_pair);
...
dictionary.append("key2", 2);
std::cout << dictionary.length();
...
// assume there are 3 key-value pairs with hashed value of 7
std::cout << dictionary.length(7);
```
Output:
```
2
3
```

## Short-hand syntax

To make life easier I have implemented two overloads for operators.
Overloaded operators are the subscript `[]` and stream insertion operator `<<`.

### Subscript `[]` overload:

The overloaded operator returns a reference to a value specified by the `std::string` key within the brackets. You can then print it out, assign to a variable or modify the value under that key.

#### Exapmles:

```Cpp
dictionary.append("key1", 1);
std::cout << dictionary["key1"] << "\n";
dictionary["key1"] = 4;
std::cout << dictionary["key1";
```

Output:

```
1
4
```

It throws an `std::invalid_argument` exception if a specified key is not found in the dictionary.

### Stream insertion operator `<<` overload

The overload lists the whole dictionary (all the hash groups).

#### Example:

```Cpp
dictionary.append("key1", 1);
std::cout << dictionary;
```

Output:

```Cpp
[
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        []
        ['key1', ]
        []
        []
        []
        []
        []
]
```

## Complexity

Theoretically, dictionaries should have Big-O notation complexity of O(1) (instant lookup). Sadly, given the time for the assignemnt and complicated nature of achieving such a fast lookup, I had to settle on best case scenario complexity of O(1) and worst case scenario complexity of O(n). There is a way to achieve O(logn) complexity, though. It involves BBSTs (Balanced Binary Search Trees) such as AVL or Red-Black Tree (both best case O(1), average O(logn), worst case O(logn)), but again, given the time for the assignment it was way too complex to implement in such short period of time. However, I am fairly sure if I were given a week rather than 3 days I could achieve it without any problems.
Either way, the way this dictionary works makes it a complexity of O(n) (linear).

# How does it work?

In essence, for each key-value pair provided the hashing function calculates the hash value of given key, then looks if the key is already present in the dictionary. If the key is present it aborts the insertion and throws an `std::invalid_argument` exception. If the key is not present, it appends the key-value pair to the end of a vector (separate chaining).

#### Hashing formula:

Takes each character from the key, gets its ASCII value and sums it up. Then returns the remainder of dividing it by number of hash groups (32 in this case).

### Collision handling:

There are 32 hash buckets to store infinitely-expandable (theoretically) vectors of K-V pairs. If there are two pairs producing the same hash value, for example:
```
"abc": 1;
"cba": 2;
```
they will both get appended to a vector in bucket number 6 `(97 + 98 + 99) % 32 = 6`. This approach is better than open addressing because it eliminates the need for a growable, yet fixed size array-type data structure, saves a lot of hustle with probing algorithms and is of the same complexity as open addressing. That way, we get sort of a tree that looks similar to this one:

![Example of separate chaining](https://study.com/cimages/multimages/16/sep_chain2.png)
###### *Study.com: Separate Chaining: Concept, Advantages & Disadvantages*
