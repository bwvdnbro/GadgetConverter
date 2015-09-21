#ifndef UTILS_HPP
#define UTILS_HPP

// standard library includes (alphabetically)
#include <istream>

namespace Utils{
    inline unsigned int get_blocksize(std::istream& stream){
        unsigned int blocksize;
        stream.read(reinterpret_cast<char*>(&blocksize), sizeof(unsigned int));
        return blocksize;
    }
}

#endif // UTILS_HPP
