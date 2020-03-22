#ifndef hashTable__H_
#define hashTable__H_
    #ifndef maxSize
        #define maxSize 0xfff
    #endif
    // How to use the list: 
    // 1. declare it. it can be on the stack or heap, but the data is always on the heap
    // 2. use update to add to the dictionary
    // 3. when you want to delete an entry, use the remove keyword
    // 4. to get the data from any entry, use the get keyword.
    #include "hashTable.cpp"
    #include "SHA.h"
#endif 