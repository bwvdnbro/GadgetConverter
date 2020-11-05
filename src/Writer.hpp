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

#ifndef WRITER_HPP
#define WRITER_HPP

// forward declarations (alphabetically)
class Block;
class Header;

// project includes
#include "Array.hpp"
#include "NameMap.hpp"

// standard library includes
#include <fstream>
#include <string>

// external library includes
#include <hdf5.h>

template <typename T> struct HDF5types { static const hid_t type; };

class Writer {
private:
  NameMap _names;
  hid_t _file;

  template <typename T, unsigned int N>
  void write(hid_t link, std::string name, Array<T, N> &d) {
    hsize_t dims[1] = {N};
    hid_t attspace = H5Screate_simple(1, dims, NULL);
    hid_t att = H5Acreate(link, name.c_str(), HDF5types<T>::type, attspace,
                          H5P_DEFAULT);
    H5Awrite(att, HDF5types<T>::type, &d);
  }

  template <typename T> void write(hid_t link, std::string name, T d) {
    hsize_t dims[1] = {1};
    hid_t attspace = H5Screate_simple(1, dims, NULL);
    hid_t att = H5Acreate(link, name.c_str(), HDF5types<T>::type, attspace,
                          H5P_DEFAULT);
    H5Awrite(att, HDF5types<T>::type, &d);
  }

  hid_t get_particle_group(unsigned int parttype);

public:
  Writer(std::string filename);
  ~Writer();

  void write_header(Header &header);
  void write_block(Block &block);
};

#endif // WRITER_HPP
