#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include "SHA.h"
#include <sstream>
#define maxSize 0xfff
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
      // we will store the dictionary values as key-value pairs. 
      // if there are collisions we will store them laterally accross the variable to decrease search time for the item
      // Hashtable:
      // -> hashnode ("Cat", "Data") -> hashnode ("Tac", "data")
      // -> hashnode ("Dog", "Data")
      // -> ... (to max size)
      // -> hashnode ("Zebra", "Data")
      // The hash function we will use is SHA 256, given by the website http://www.zedwood.com/article/cpp-sha256-function

      class hashNode{
         public:
            hashNode(string index, T stuff): text{index}, data{stuff}, next{nullptr} {};
            string text;
            T data;
            hashNode *next;
      };
      hashNode *hashTable[maxSize] ;
      T defaultValue;

   public:
      dict(T defaultV):defaultValue{defaultV}{
         for (int i = 0; i < maxSize; ++i){
            hashTable[i] = nullptr;
         }
      }
      ~dict(){
         //go through each item in the list and delete them from the heap.
         for (hashNode *item : hashTable){
            hashNode *prev, *curr;
            curr = item;
            while(curr != nullptr){
               prev = curr;
               curr = curr->next;
               prev->next = nullptr;
               //remove the item from the list and continue
               delete prev;
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
      void updateLaterally(string text, T data, hashNode *curr){
      // if the item is found, set it and delete the target
        if(curr->text == text){
           curr->data = data;
           return ;
        }
        //if not, then search
        if(curr->next != nullptr){
           //look for the target or look for the end node
           return updateLaterally(text, data, curr->next);
        } else {
           hashNode *target = new hashNode(text, data);
           curr->next = target;
           return;
        }

      }
      void update(string key, T data){
         //get the hash representation of the key
         
         int location = hashFunc(key);
         //check to see if it exists, if it doesnt make this key|data pair the new head
         if (hashTable[location] == nullptr){
            hashNode *node = new hashNode(key, data);
            hashTable[location] = node;
            return;
         } else if (hashTable[location]->text == key){
            //if the current is the right one, update it.
            hashTable[location]->data = data;
            return;
         } else {
            
            updateLaterally(key, data, hashTable[location]);
            return;
         }
      }
      T get(string key){
         //get the hash representation of the key
         int location = hashFunc(key);
         //check to see if it exists, if it doesnt make this key|data pair the new head
         if (hashTable[location] == nullptr){
            return defaultValue;
         } 
         hashNode * curr = hashTable[location];
         while(curr != nullptr){
            //if the text is found, return the data.
            if(curr->text == key){
               return &(curr->data);
            }
            // go to next item laterally.
            curr = curr->next;
         }
         return defaultValue;
      }



      bool remove(string key){
         //get the hash representation of the key
         int location = hashFunc(key);
         //check to see if it exists, if it doesnt make this key|data pair the new head
         if (hashTable[location] == nullptr){
            return false;
         } else if (hashTable[location]->text == key){
            hashNode *prev = hashTable[location]; 
            hashNode *curr  = hashTable[location]->next;
            prev->next = nullptr;
            delete prev;
            hashTable[location] = curr;
            return true;
         }
         return deleteLaterally(key, hashTable[location], hashTable[location]->next);
         
         
      }
      bool deleteLaterally(string key, hashNode *prev, hashNode *curr){
         //if the current has the correct index text, delete it!
         if (curr->text == key){
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
int main() {
   dict<bool> visitedList = dict<bool>(false) ;
   visitedList.update("batch", true);
   visitedList.update("btach", true);
   visitedList.update("cbath", true);
   visitedList.update("hctab", true);
   visitedList.update("bathc", true);

   if(visitedList.get("batch")==1){
      cout<<"batch entered correctly";
   } else {
      cout << "Incorrect data";
   }
   cout<<"\n";
   if(visitedList.get("cat")==1){
      cout<<"cat entered correctly";
   } else {
      cout << "cat entered incorrectly";
   }

}
