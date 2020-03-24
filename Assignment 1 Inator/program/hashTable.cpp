#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <sstream>
#include <random>
#include <ctime>
#ifndef maxSize
   #define maxSize 0xfff
#endif
// This is a dictionary class created by mathew lawrence 
// This dictionary is stored as pointers on the heap and is designed to get big.
// This class has three functions:
// ->update(string key, T value)
//    ->Finds the SHA key and places it in the array (based on the max size of the array)
//    -> if there is a collision, places it in a linked list next to it 
// ->delete (string key)
//    ->Finds SHA key and maps it to the array 
//    ->Returns true if the key exists and is deleted, false otherwise
// ->get(string key)
//    ->Finds the SHA Key and maps it to the array 
//    ->if it cannot find the array, it returns the default value set by the constructor
//    ->Returns the data in said key.
// ->constructor(T Default value)
//    ->initializes the data to a series of null pointers 
//    -> sets the default value to what you choose


using namespace std;

template <typename T>
class dict {
   private:
      struct node {
         string key;
         T data;
      };

      // we will store the dictionary values as key-value pairs. 
      // if there are collisions we will store them laterally accross the variable to decrease search time for the item
      // Hashtable:
      // -> hashnode ("Cat", "Data") -> hashnode ("Tac", "data")
      // -> hashnode ("Dog", "Data")
      // -> ... (to max size)
      // -> hashnode ("Zebra", "Data")
      // The hash function we will use is SHA 256, given by the website http://www.zedwood.com/article/cpp-sha256-function

      //an array of vectors (hashtable big)
      int size;
      vector<node> hashTable[maxSize] ;
      T defaultValue;
      string lastKey;

   public:
      dict(T defaultV):defaultValue{defaultV}{
         size = 0;
         lastKey = "";
         for (int i = 0; i < maxSize; ++i){
            hashTable[i] = vector<node>();
         }
         
      }
      ~dict(){
         
         
      }

      int hashFunc (string input){
         //function which takes the input hash and returns a table index
         int hash = 0;
         for (int i = 0; i < input.length(); ++i){
            //hash is the char's location + the actual char
            hash+= input[i]+i;
         }
         return hash % maxSize;
      }
      
      int getSize(){
         return size;
      }
      T* update(string key, T data){
         int index = hashFunc(key);
         T* oldData = get(key);
         if(oldData == nullptr){
            node newNode = node();
            newNode.key = key;
            newNode.data = data;
            hashTable[index].push_back(newNode);
            oldData = & (hashTable[index][hashTable[index].size()-1].data);
         } else {
            *oldData = data;
         }
         return oldData;
      }
      
      T* get(string key){
         int index = hashFunc(key);
         if(hashTable[index].empty()){
            return nullptr;
         }
         for(int i = 0; i < hashTable[index].size(); ++i){
            if (hashTable[index][i].key == key) {
               return &(hashTable[index][i].data);
            }
         }
         return nullptr;
      }
      //override the List["key"] operator
      T&  operator[](string key){
         T* tempN = get(key);
         if(tempN == nullptr){
            tempN = update(key, defaultValue);
         }
         return *tempN;
      }

};

// How to use the list: 
// 1. declare it. it can be on the stack or heap, but the data is always on the heap
// 2. use update to add to the dictionary
// 3. when you want to delete an entry, use the remove keyword
// 4. to get the data from any entry, use the get keyword.
