#ifndef HEADER_HPP
#define HEADER_HPP

// project includes
#include "Array.hpp"

// standard library includes (alphabetically)
#include <istream>

class Header{
private:
    Array<unsigned int, 6> _npart;
    Array<double, 6> _masses;
    double _time;
    double _redshift;
    int _flag_sfr;
    int _flag_feedback;
    Array<unsigned int, 6> _npart_total;
    int _flag_cooling;
    int _num_files;
    Array<double, 3> _box;
    double _omega0;
    double _omega_lambda;
    double _hubble_param;
    double _hubble_a;
    int _flag_stellar_age;
    int _flag_metals;
    Array<unsigned int, 6> _npart_total_highword;
    int _flag_entropy_instead_u;
    
    template<typename T, unsigned int N> void read(std::istream &stream,
                                                   Array<T, N> &a){
        stream.read(a, a.memsize());
    }
    
    template<typename T> void read(std::istream &stream, T &d){
        stream.read(reinterpret_cast<char*>(&d), sizeof(T));
    }

public:
    Header();
    Header(std::istream &stream);
    
    Array<unsigned int, 6> &get_npart();
    Array<double, 6> &get_masses();
    double get_time();
    Array<double, 3> &get_box();
    int get_numfiles();
    Array<unsigned int, 6> &get_npart_total();
    Array<unsigned int, 6> &get_npart_highword();
    double get_redshift();
    
    void print_contents();
};

#endif // HEADER_HPP
