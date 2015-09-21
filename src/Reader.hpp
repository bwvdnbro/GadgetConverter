#ifndef READER_HPP
#define READER_HPP

// forward declarations (alphabetically)
class Block;
class Header;

// standard library includes (alphabetically)
#include <fstream>
#include <string>
#include <vector>

class Reader{
private:
    std::ifstream _file;
    Header _header;
    std::vector< Block* > _blocks;

public:
    Reader(std::string filename);
    ~Reader();
    
    Header &get_header();
    std::vector< Block* > &get_blocks();
};

#endif // READER_HPP
