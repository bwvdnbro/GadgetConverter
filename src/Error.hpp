#include <cstdlib>
#include <iostream>

#define error(s) { \
    std::cerr << __FILE__ << ":" << __FUNCTION__ << "():" << __LINE__ << ": " \
              << s << std::endl; \
    abort(); \
    }
