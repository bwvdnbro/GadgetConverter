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

// project includes (alphabetically)
#include "Block.hpp"
#include "Error.hpp"
#include "Header.hpp"
#include "Reader.hpp"
#include "TypeMap.hpp"

// standard library includes (alphabetically)
#include <fstream>

// namespaces
using namespace std;

//# public methods

Reader::Reader(string filename){
    TypeMap tm;
    _file.open(filename.c_str());
    if(_file.good()){
        _header = Header(_file);
//        _header.print_contents();

        Array<unsigned int, 6> npart = _header.get_npart();

        // reset the stream
        _file.seekg(0);
        while(_file.peek() != EOF){
            _blocks.push_back(new Block(_file, npart, tm));
        }
        // drop the HEAD block
        delete _blocks[0];
        _blocks.erase(_blocks.begin());
    } else {
        error("File not found: " + filename + "!");
    }
}

Reader::~Reader(){
    for(unsigned int i = 0; i < _blocks.size(); i++){
        delete _blocks[i];
    }
}

Header &Reader::get_header(){
    return _header;
}

vector< Block* > &Reader::get_blocks(){
    return _blocks;
}
