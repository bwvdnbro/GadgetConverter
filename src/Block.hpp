/*******************************************************************************
 * This file is part of GadgetConverter
 * Copyright (C) 2016 Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 *
 * GadgetConverter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GadgetConverter is distributed in the hope that it will be useful,
 * but WITOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with GadgetConverter. If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

/**
 * @file Block.hpp
 *
 * @brief Data block: header
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@ugent.be)
 */
#ifndef BLOCK_HPP
#define BLOCK_HPP

// project includes
#include "Array.hpp"
#include "Error.hpp"

// standard library includes
#include <istream>
#include <sstream>
#include <string>
#include <vector>

// external library includes
#include <hdf5.h>

// forward declarations
class TypeMap;

/**
 * @brief Data block
 *
 * Corresponds to a single block in the Gadget snapshot file, and to all
 * datasets with the same name in the HDF5 snapshot.
 */
class Block{
private:
    /**
     * @brief HDF5-type of the data in the Block
     */
    hid_t _type;
    
    /**
     * @brief Reference to the snapshot file containing the actual data
     */
    std::istream &_stream;
    
    /**
     * @brief (Old) name of the Block
     */
    std::string _name;
    
    /**
     * @brief Array keeping track of which particle types have data for this
     * Block
     */
    Array<bool, 6> _mesh;
    
    /**
     * @brief Offsets of the data for the different particle types in the
     * snapshot file
     */
    Array<int, 6> _streampos;
    
    /**
     * @brief Sizes (in bytes) for the data of the different particle types in
     * the snapshot file
     */
    Array<int, 6> _streamsize;
    
    /**
     * @brief Flag indicating whether the Block contains vector (true) or scalar
     * (false) data
     */
    bool _vec;

public:
    Block(std::istream& stream, Array<unsigned int, 6> npart, TypeMap &tm);
    
    bool is_vec();
    unsigned int get_size(unsigned int parttype);
    std::vector< char > get_buffer(unsigned int parttype);
    hid_t get_type();
    std::string get_name();
    bool has_data(unsigned int type);
};

#endif // BLOCK_HPP
