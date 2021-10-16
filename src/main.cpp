#include "hashMap.hpp"
#include "prime.hpp"
#include "client.hpp"
// #include "httplib.h"
#include <stdio.h>
#include <sstream>
#include <iostream>

#include <cstdlib>

#include <chrono>

using namespace std;


int main(int argc, char *argv[]){

    hashTable hash;

    // string key;
    // string value;
    // string randomStrings[10] = {"key", "pee", "wee", "fee", "store", "flee", "wee", "fee", "store", "flee"};
    // for(int i = 0; i < 2000; i++){
        
    //     key = randomStrings[rand() % 10] + to_string(i) + randomStrings[rand() % 10];
    //     value = "value" + to_string(i);
    //     // printf("keys: %s\n", keys);
    //     hash.insert(key, value);
    // }
    // for(int i = 0; i < 1000; i++){
    //     key = "key" + to_string(i);
    //     value = "value" + to_string(i);
    //     hash.search(key);
    //     hash.remove(key);
    // }
    // hash.remove("key20");
    // cout << "\n" << hash.filled << " : " << hash.size<< "\n";
    // cout << "\n" << "max depth of hashtable" << " : " << hash.returnDepth()<< "\n";
    
    client* userClient = new client;

    for(int i = 0; i < argc; i++){
        string arg = argv[i];
        if(arg == "-h") {
            if(argv[i+1] != NULL) {
                printf("hosts: %s \n", argv[i+1]);
            } else {
                cout << "hosts not specified after " << argv[i] << endl;
            }
        }
    }
    // userClient ->clientStart();
    userClient -> serverStart();

    cout << "weiner" << endl;



    return 0;
}