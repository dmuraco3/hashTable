#include "hashMap.hpp"
#include "prime.hpp"
// #include "httplib.h"
#include <stdio.h>
#include <sstream>
#include <iostream>

#include <cstdlib>

#include <chrono>
#include <thread>

using namespace std;


int main(int argc, char *argv[]){

    srand((unsigned)time(0)); 

    hashTable hash;
    
    // httplib::Server svr;

    // svr.Get("/hi", [](const httplib::Request &req, httplib::Response &res) {
    //     printf("\nrequest to hi %s\n", req.remote_addr.c_str());
    //     res.set_content("Hello World!", "text/plain");
    // });

    // svr.listen("0.0.0.0", 8080);

    string key;
    string value;
    string randomStrings[10] = {"key", "pee", "wee", "fee", "store", "flee", "wee", "fee", "store", "flee"};
    for(int i = 0; i < 100000; i++){
        
        key = randomStrings[rand() % 10] + to_string(i) + randomStrings[rand() % 10];
        value = "value" + to_string(i);
        // printf("keys: %s\n", keys);
        hash.insert(key, value);
    }
    for(int i = 0; i < 1000; i++){
        key = "key" + to_string(i);
        value = "value" + to_string(i);
        hash.search(key);
        hash.remove(key);
    }
    hash.remove("key20");
    cout << "\n" << hash.filled << " : " << hash.size<< "\n";
    cout << "\n" << "max depth of hashtable" << " : " << hash.returnDepth()<< "\n";
    string userKey;
    string userValue;

    cout << "key: ";
    cin >> userKey;
    cout << "value: ";
    cin >> userValue;
    cout << endl;

    auto start = std::chrono::high_resolution_clock::now();
    hash.insert(userKey, userValue);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << "time to insert after 100000 entries: " << duration.count() << " microseconds" << endl;



    // hash.serialize();
    return 0;
}