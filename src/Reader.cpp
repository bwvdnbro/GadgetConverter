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
