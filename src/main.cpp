#include "Block.hpp"
#include "Header.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv){
    Reader reader("snapshot_0000");
    
    Header header = reader.get_header();
    vector< Block* > blocks = reader.get_blocks();
    
    Writer writer("snapshot_0000.hdf5");
    writer.write_header(header);
    for(unsigned int i = 0; i < blocks.size(); i++){
        writer.write_block(*blocks[i]);
    }
    
    return 0;
}
