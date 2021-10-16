#include <iostream>
#include <sstream>

#include "httplib.h"

#include <hashMap.hpp>
using namespace std;

#ifndef CLIENT
#define CLIENT

enum userCommand {
    EXIT,
    INSERT,
    REMOVE,
    GET,
    NONE,
};

class client
{
    private:

        hashTable userTable;

        userCommand parseCommand(string command) {
            stringstream ss;
            ss << command;
            

            string mainCommand;
            string key;
            string value;

            string token;
            int index=0;

            ss >> mainCommand;

            if(mainCommand == "exit"){
                exit(1);
                return EXIT;
            }
            else if(mainCommand == "insert"){
                while(ss >> token){
                    if(index == 0){
                        key = token;
                    } else if(index == 1){
                        value = token;
                    } else {
                        cout << " -------- " << "insert <key> <value>" << endl;
                        cout << "          " << "ERROR: arguments exceed limit" << endl;
                        return NONE;
                    }
                    index++;
                }

                if(key.length() != 0 && value.length() != 0) {
                    cout << key << " : " << value << endl;
                    userTable.insert(key, value);
                }
                return INSERT;
            }
            else if(mainCommand == "remove"){
                while(ss >> token){
                    if(index == 0){
                        key = token;
                    } else {
                        cout << " -------- " << "remove <key>" << endl;
                        cout << "          " << "ERROR: arguments exceed limit" << endl;
                        return NONE;

                    }
                    index++;
                }
                if(key.length() != 0 ){
                    bool removeResult = userTable.remove(key);
                    if(removeResult == 1) {
                        cout << key << " removed" << endl;
                    } else {
                        cout << key <<" not found" << endl;
                    }

                }
                return REMOVE;
            }
            else if(mainCommand == "get"){
                while(ss >> token){
                    if(index == 0){
                        key = token;
                    } else {
                        cout << " -------- " << "get <key>" << endl;
                        cout << "          " << "ERROR: arguments exceed limit" << endl;
                        return NONE;

                    }
                    index++;
                }
                if(key.length() != 0 ){
                    string searchResult = userTable.search(key);
                    cout << key << " : " << searchResult << endl;

                }
                return GET;
            }
            else {
                cout << mainCommand << " not recognized" << endl;
                return NONE;
            }
        }
    public:

    void clientStart(){
        cout  << "\033[2J"; // clear terminal
        string userCommand;
        while(true){
            cout << "KeyStore> ";
            getline(cin, userCommand); // need to read whole line of arguments 
            parseCommand(userCommand);
            
        }
    }

    void serverStart() {
        httplib::Server svr;
        svr.Get("/get", [&](const httplib::Request &req, httplib::Response &res) {
            printf("request from : %s \n", (char*)req.remote_addr.c_str());
            if(req.has_param("key")){
                string key = req.get_param_value("key");
                string searchStatus = userTable.search(key);
                res.set_content(searchStatus, "text/plain");

            } else {
                res.status = 400;
                res.set_content("no key provided", "text/plain");
            }

        });
        svr.Put("/insert", [&](const httplib::Request &req, httplib::Response &res) {
            printf("request from : %s \n", (char*)req.remote_addr.c_str());
            if(req.has_param("key") && req.has_param("value")){
                string key = req.get_param_value("key");
                string value = req.get_param_value("value");
                bool insertStatus = userTable.insert(key, value);
                if(insertStatus == 1) {
                    res.status = 200;
                    res.set_content("inserted key", "text/plain");
                } else {
                    res.status = 403;
                    res.set_content("couldn't insert key", "text/plain");
                }

            }
        });
        cout << "listening for requests" << endl;

        svr.listen("localhost", 8080);
    }   
};

#endif