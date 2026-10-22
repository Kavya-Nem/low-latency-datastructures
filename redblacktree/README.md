/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA8
* README.md
* Lists the files submitted in assignment along with purpose of each.
***/

## Files

- README.md
  Lists the files submitted in assignment along with purpose of each file.

- Makefile
  Builds all .cpp files and includes a clean target.

- Dictionary.h
  Header file for the Dictionary ADT. Defines the Dictionary type and all its' exported operations.

- Dictionary.cpp
  Implementation of the Dictionary ADT using a red black tree with cursor.

- DictionaryTest.cpp
  Test client used to verify correctness of all the Dictionary ADT operations.

- Words.cpp
  Client program. Reads an input file, extracts unique words, and outputs in alphabetical order using an index Dictionary.

- WordFrequency.cpp
  Client program. Reads an input file, extracts words, and adds them to a dictionary along with frequency, or updates frequency if the word already exists inside of the dictionary. Finally, it prints the string representation of the dictionary to the output in form "key : value" in the keys' insertion order.
