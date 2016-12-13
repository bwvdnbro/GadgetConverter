/*******************************************************************************
 * This file is part of GadgetConverter
 * Copyright (C) 2016 Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 *
 * GadgetConverter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GadgetConverter is distributed in the hope that it will be useful,
 * but WITOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with GadgetConverter. If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include "TypeMap.hpp"
#include "Paths.hpp"

#include <fstream>
#include <iostream>

using namespace std;

TypeMap::TypeMap(){
    map< string, hid_t > types;
    types["FLOAT"] = H5T_NATIVE_FLOAT;
    types["INT"] = H5T_NATIVE_UINT32;

    ifstream ifile(TYPEMAP_PATH);
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
