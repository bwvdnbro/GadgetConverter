#ifndef NAMEMAP_HPP
#define NAMEMAP_HPP

// standard library includes
#include <map>
#include <string>

class NameMap{
private:
    std::map< std::string, std::string > _dict;

public:
    NameMap();

    std::string get_name(std::string key);

    void print_contents();
};

#endif // NAMEMAP_HPP
