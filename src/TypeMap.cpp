#include "TypeMap.hpp"

#include <fstream>
#include <iostream>

using namespace std;

TypeMap::TypeMap(){
    map< string, hid_t > types;
    types["FLOAT"] = H5T_NATIVE_FLOAT;
    types["INT"] = H5T_NATIVE_UINT32;

    ifstream ifile("resources/types.txt");
    if(ifile.good()){
        string key;
        string type;
        while(ifile.good()){
            ifile >> key >> type;
            _dict[key] = types[type];
        }
    } else {
        // error!
    }
}

hid_t TypeMap::get_type(string key){
    return _dict[key];
}

void TypeMap::print_contents(){
    typedef map< string, hid_t >::iterator iterator;
    for(iterator it = _dict.begin(); it != _dict.end(); ++it){
        cout << it->first << ": " << it->second << endl;
    }
}
