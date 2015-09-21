#ifndef TYPEMAP_HPP
#define TYPEMAP_HPP

// standard library includes
#include <map>
#include <string>

// external library includes
#include <hdf5.h>

class TypeMap{
private:
    std::map< std::string, hid_t > _dict;

public:
    TypeMap();

    hid_t get_type(std::string key);

    void print_contents();
};

#endif // TYPEMAP_HPP
