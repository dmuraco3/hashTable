#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <future>
#include <stdlib.h>
#include <fstream>

#include "prime.hpp"

using namespace std;

#ifndef HASH_MAP
#define HASH_MAP
typedef struct tableEntry
{
    string key;
    string value;
    struct tableEntry *next;


} tableEntry;

class hashTable 
{

public:
    // hashing function for hash table
    bool shouldRehash(int size, int filled){
        if(numEntries <= 25000){
          return 0.7 <= (double)filled/size;
        } else if(numEntries > 25000){
          return 0.6 <= (double)filled/size;
          
        }
    };  

    void resize(){ // wrapper for rehash
        // thread t1(&hashTable::rehash, this, this->entries);
        // t1.detach();

        rehash(entries);

    }

    void rehash(tableEntry param[]){
        int oldSize = size;
        int newSize = next_prime(size);

        depth = 0; // reset depth
        filled = 0; //reset filled

        rehash_idx = 1; // rehashing initialized

        tableEntry *newTable = new tableEntry[newSize];


        if(debug) {
            printf("rehashing from %d to %d\n", oldSize, newSize);
        }
        for(int i = 0; i < oldSize; i++){
            tableEntry *entry = &param[i];
            while(entry -> key.size() != 0){ // confusing while loop maybe cuz breaking out of it from inside when the conditional should just break out of it 
                insert(entry -> key, entry -> value, newTable, newSize);
                if(entry -> next != NULL){
                    entry = entry -> next;
                } else {
                    break;
                }
            }
        }

        delete[] param;
        size = newSize;
        entries = newTable;
        rehash_idx = 0; // rehashing finished

    }

    int hash(string key, int size){
        int hash = 0;
        if(key.length() < 1){
            return 0;
        } else if (key.length() == 1) {

            return (hash + key[0]) % (size);

        } else {
            for(int i = 0; i < key.length(); i++){
                hash = (hash + key[i])  % (size)  ; // introducing size here lessens collisions because of more randomness
            }
            return hash;
        }
    };

    // insert keyed valued into hash table
    //todo: fix collisions using linked list
    void insert(string key, string value, tableEntry *optionEntries = NULL, int sizePassed = 0){
        int localSize = size;
        if(sizePassed != 0 ){
            localSize = sizePassed;
        }
        tableEntry *local = entries;
        if(optionEntries != NULL){
            local = optionEntries;
        }


        int index = hash(key, localSize);
        struct tableEntry* entry = new tableEntry;


        entry->key = key;
        entry->value = value;
        entry->next = NULL;
        int bucketDepth = 0;

        if(local[index].key.size() == 0){
            local[index] = *entry;
            filled++;

            
        } else {
            tableEntry* temp = &local[index];
            bucketDepth+=1;
            while(temp -> next != NULL){
                bucketDepth+=1;
                if(key == temp -> key) {
                    temp -> value = value;
                    break;
                }
                if(temp -> next == NULL){
                    temp -> next = entry;
                    break;
                } 
                if(temp -> next != NULL){
                    temp = temp -> next;
                }


            }
            temp -> next = entry;
            
            if(bucketDepth > depth){
                depth = bucketDepth;
            }
        }
        if(shouldRehash(size, filled) == true && rehash_idx == 0){
            resize();
        }
        numEntries +=1;
    };
    void remove(string key){
        int index = hash(key, size);
        tableEntry *entry = &entries[index];
        tableEntry *prev = entry;


        if(entry -> key == key){
            if(entry -> next == NULL){
                struct tableEntry* newEntry = new tableEntry;
                entries[index] = *newEntry;
                filled--;
            } else {
                entry = entry -> next;
            }
        } else {
            while(entry -> next != NULL){
                if(entry -> next != NULL){
                    prev = entry;
                    entry = entry -> next;
                }
                if(key == entry -> key) {
                    prev -> next = entry -> next;
                    break;
                }

            }
        }
    };
    //find the value associated with key in hashtable
    string search(string key){
        int index = hash(key, size);
        // assert(entries[index]->value != NULL);
        if(entries[index].key == key){
            return entries[index].value;
        } else {
            tableEntry* temp = &entries[index];
            while(temp -> next != NULL){
                if(temp -> next != NULL){
                    temp = temp -> next;
                }
                if(temp -> key == key){
                    return temp -> value;

                } 
            }   
        }
        return "(null)";
    };

    int returnDepth(){
        return depth;
    }

    void serialize(){

        ofstream myFile;
        myFile.open("serialized.txt");
        for(int i = 0; i < size; i++){
            tableEntry* temp = &entries[i];
            if(temp -> key.size() != 0){
                myFile << temp -> key << "." << temp -> value << "\n";
            }
            if(temp -> next != NULL){
                while(temp -> next != NULL){
                    temp = temp -> next;
                    myFile << temp -> key << "." << temp -> value << "\n";
                }
            }
        }
        myFile.close();
    }

    bool debug=true;
    int filled = 0;
    int size = 23; // size = 23 because it is prime number so less collisions

private:
    tableEntry *entries = new tableEntry[23]; // size = 23 because it is prime number so less collisions
    int rehash_idx = 0;
    int depth = 0;
    int numEntries = 0;


};
#endif