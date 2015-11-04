#include "Block.hpp"
#include "CommandLineArguments.hpp"
#include "Header.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv){
    CommandLineArguments args(argc, argv);

    Reader reader(args.get_input_name());
    
    Header header = reader.get_header();
    vector< Block* > blocks = reader.get_blocks();
    
    Writer writer(args.get_output_name());
    writer.write_header(header);
    for(unsigned int i = 0; i < blocks.size(); i++){
        writer.write_block(*blocks[i]);
    }
    
    return 0;
}
