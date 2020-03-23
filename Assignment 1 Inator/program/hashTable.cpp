#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include "SHA.h"
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
class hashNode{
         public:
            hashNode(string index, T stuff): text{index}, data{stuff}, next{nullptr} {};
            ~hashNode(){
               if(next != nullptr){
                  delete next;
               }
            }
            string text;
            T data;
            hashNode *next;
            hashNode& operator=(T stuff) 
            {
               data = stuff;
               
               

               return *this;  // Return a reference to myself.
            }
      };
template <typename T>
class dict {
   private:
      // we will store the dictionary values as key-value pairs. 
      // if there are collisions we will store them laterally accross the variable to decrease search time for the item
      // Hashtable:
      // -> hashnode ("Cat", "Data") -> hashnode ("Tac", "data")
      // -> hashnode ("Dog", "Data")
      // -> ... (to max size)
      // -> hashnode ("Zebra", "Data")
      // The hash function we will use is SHA 256, given by the website http://www.zedwood.com/article/cpp-sha256-function

      
      hashNode<T> *hashTable[maxSize] ;
      T defaultValue;
      string lastKey;
      int currSize;

   public:
      dict(T defaultV):defaultValue{defaultV}{
         for (int i = 0; i < maxSize; ++i){
            hashTable[i] = nullptr;
         }
         lastKey = "";
         currSize = 0;
      }
      ~dict(){
         //go through each item in the list and delete them from the heap.
         for (hashNode<T> *item : hashTable){
            if(item!=nullptr) {
               delete item;
            }

         }
         
      }

      int hashFunc (string input){
         //function which takes the input hash and returns a table index
         std::stringstream ss;
         unsigned int output;
         //convert the string to a hash input
         ss << hex << sha256(input);
         ss >> output;
         //format it so that it is the right size
         return output % maxSize;
      }
      hashNode<T>* updateLaterally(string text, T data, hashNode<T> *curr){
      // if the item is found, set it and delete the target
        if(curr->text == text){
           curr->data = data;
           return curr;
        }
        //if not, then search
        if(curr->next != nullptr){
           //look for the target or look for the end node
           return updateLaterally(text, data, curr->next);
        } else {
            ++currSize;
           hashNode<T> *target = new hashNode<T>(text, data);
           curr->next = target;
           return target;
        }

      }
      int size(){
         return currSize;
      }
      hashNode<T>* update(string key, T data){
         //get the hash representation of the key
         int location = hashFunc(key);
         //check to see if it exists, if it doesnt make this key|data pair the new head
         if (hashTable[location] == nullptr){
            hashNode<T> *node = new hashNode<T>(key, data);
            hashTable[location] = node;
            ++currSize;
            return node;
         } else if (hashTable[location]->text == key){
            //if the current is the right one, update it.
            hashTable[location]->data = data;
            return  hashTable[location];
         } else {
            
            return updateLaterally(key, data, hashTable[location]);
            
         }
      }
      hashNode<T>* get(string key){
         lastKey = key;
         //get the hash representation of the key
         int location = hashFunc(key);
         T returnable = defaultValue;
         //check to see if it exists, if it doesnt make this key|data pair the new head
         if (hashTable[location] == nullptr){
            //if there is no value to change, then the returned node is still null!
            return nullptr;
            
         } 
         hashNode<T> * curr = hashTable[location];
         while(curr != nullptr){
            //if the text is found, return the data.
            if(curr->text == key){
               
               return curr;
            }
            // go to next item laterally.
            curr = curr->next;
         }
         return nullptr;
      }
      //override the List["key"] operator
      hashNode<T>&  operator[](string key){
         hashNode<T>* node = get(key);
         if(node == nullptr) {
            node = update(key, defaultValue);
         }

        return *node;
         
      }
      



      bool remove(string key){
         //get the hash representation of the key
         int location = hashFunc(key);
         //check to see if it exists, if it doesnt make this key|data pair the new head
         if (hashTable[location] == nullptr){
            return false;
         } else if (hashTable[location].text == key){
            --currSize;
            hashNode<T> *prev = hashTable[location]; 
            hashNode<T> *curr  = hashTable[location].next;
            prev.next = nullptr;
            delete prev;
            hashTable[location] = curr;
            return true;
         }
         return deleteLaterally(key, hashTable[location], hashTable[location]->next);
         
         
      }
      bool deleteLaterally(string key, hashNode<T> *prev, hashNode<T> *curr){
         //if the current has the correct index text, delete it!
         if (curr->text == key){
            --currSize;
            prev->next = curr->next;
            curr->next = nullptr;
            delete curr;
            return true;
         }
         //else parse the list until it finds the correct item or hits the end
         if(curr != nullptr){
            return deleteLaterally(key, prev->next, curr->next);
         }
         return false;
      }

};

// How to use the list: 
// 1. declare it. it can be on the stack or heap, but the data is always on the heap
// 2. use update to add to the dictionary
// 3. when you want to delete an entry, use the remove keyword
// 4. to get the data from any entry, use the get keyword.
