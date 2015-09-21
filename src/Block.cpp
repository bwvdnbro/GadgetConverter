/**
 * @file Block.cpp
 *
 * @brief Data block: imlementation
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@ugent.be)
 */

// project includes
#include "Block.hpp"
#include "TypeMap.hpp"
#include "Utils.hpp"

// standard library includes
#include <iostream>
#include <sstream>

// namespaces
using namespace std;
using namespace Utils;

/**
 * @brief Constructor
 *
 * This routine reads the header of the block in the Gadget snapshot and uses it
 * to initialize internal variables. It does NOT read actual data from the file,
 * but stores the offset of the data in the file so that it can easily be
 * retrieved when the data is requested.
 *
 * @param stream File to read from
 * @param npart Number of particles of each type
 * @param tm TypeMap used to link block names to internal data types
 */
Block::Block(std::istream& stream, Array<unsigned int, 6> npart, TypeMap &tm)
    : _stream(stream) {
    unsigned int blocksize = get_blocksize(stream);
    char name[5];
    stream.read(name, 4);
    name[4] = '\0';
    for(unsigned int i = 0; i < 4; i++){
        if(name[i] == ' '){
            name[i] = '\0';
        }
    }
    _name = std::string(name);
    _type = tm.get_type(_name);
    if(_name == "HEAD"){
        _vec = false;
        get_blocksize(stream);
        blocksize -= get_blocksize(stream);
        if(blocksize){
            error("Wrong blocksize!");
        }
        blocksize = get_blocksize(stream);
        stream.seekg(blocksize, stream.cur);
        blocksize -= get_blocksize(stream);
        if(blocksize){
            error("Wrong blocksize!");
        }
    } else {
        unsigned int datasize = get_blocksize(stream);
        blocksize -= get_blocksize(stream);
        if(blocksize){
            error("Wrong blocksize!");
        }
        // subtract size of block info at start and ending of datablock
        datasize -= 8;
        unsigned int totnpart = 0;
        for(unsigned int i = 0; i < 6; i++){
            totnpart += npart[i];
        }
        // some magic to find out which particle types are present
        // might be wrong for some snapshots...
        _vec = (datasize/(totnpart*sizeof(float)) == 3);
        if(npart[0]*sizeof(float) == datasize){
            _mesh[0] = true;
            _mesh[1] = false;
            _mesh[2] = false;
            _mesh[3] = false;
            _mesh[4] = false;
            _mesh[5] = false;
        } else {
            _mesh[0] = true;
            _mesh[1] = npart[1] > 0;
            _mesh[2] = npart[2] > 0;
            _mesh[3] = npart[3] > 0;
            _mesh[4] = npart[4] > 0;
            _mesh[5] = npart[5] > 0;
        }
        blocksize = get_blocksize(stream);
        for(unsigned int i = 0; i < 6; i++){
            _streampos[i] = stream.tellg();
            if(_mesh[i]){
                _streamsize[i] = npart[i]*sizeof(float);
                if(_vec){
                    _streamsize[i] *= 3;
                }
                stream.seekg(_streamsize[i], stream.cur);
            }
        }
        blocksize -= get_blocksize(stream);
        if(blocksize){
            error("Wrong blocksize!");
        }
    }
}

/**
 * @brief Test if the Block contains a scalar or vector variable
 *
 * @return True if the Block contains vector data, false if it contains scalar
 * data
 */
bool Block::is_vec(){
    return _vec;
}

/**
 * @brief Get the number of data cells in the Block for the given particle type
 *
 * @param parttype Type of the particles for which we want the data size
 * @return Number of data cells for the given particle type
 */
unsigned int Block::get_size(unsigned int parttype){
    if(_type == H5T_NATIVE_FLOAT){
        return _streamsize[parttype]/sizeof(float);
    }
    if(_type == H5T_NATIVE_UINT32){
        return _streamsize[parttype]/sizeof(unsigned int);
    }
    return 0;
}

/**
 * @brief Get the binary buffer containing the raw data for the given particle
 * type
 *
 * @param parttype Type of the particles for which we want the raw data
 * @return Binary buffer containing the raw data for the given particle type
 */
vector<char> Block::get_buffer(unsigned int parttype){
    vector<char> buffer(_streamsize[parttype]);
    _stream.seekg(_streampos[parttype]);
    _stream.read(&buffer[0], _streamsize[parttype]);
    return buffer;
}

/**
 * @brief Get the type of the data in the Block
 *
 * @return HDF5-type of the data in the Block
 */
hid_t Block::get_type(){
    return _type;
}

/**
 * @brief Get the Gadget snapshot name of the Block
 *
 * @return The Gadget snapshot name of the Block (old name)
 */
std::string Block::get_name(){
    return _name;
}

/**
 * @brief Check whether the Block contains data for the given particle type
 *
 * @param index Type of particles for which we want to check if there is data
 * @return True if there is data for the given particle type
 */
bool Block::has_data(unsigned int index){
    return _mesh[index];
}
