#include "NameMap.hpp"

#include <fstream>
#include <iostream>
using namespace std;

NameMap::NameMap(){
    ifstream ifile("resources/names.txt");
    if(ifile.good()){
        std::string key;
        std::string name;
        while(ifile.good()){
            ifile >> key >> name;
            _dict[key] = name;
        }
    } else {
        // Error!
    }
}

string NameMap::get_name(string key){
    return _dict[key];
}

void NameMap::print_contents(){
    typedef map< string, string >::iterator iterator;
    for(iterator it = _dict.begin(); it != _dict.end(); ++it){
        cout << it->first << ": " << it->second << endl;
    }
}
