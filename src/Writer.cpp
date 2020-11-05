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

#include "Writer.hpp"
#include "Block.hpp"
#include "Error.hpp"
#include "Header.hpp"

#include <iostream>
#include <sstream>
using namespace std;

template <> const hid_t HDF5types<unsigned int>::type = H5T_NATIVE_UINT32;
template <> const hid_t HDF5types<int>::type = H5T_NATIVE_INT32;
template <> const hid_t HDF5types<double>::type = H5T_NATIVE_DOUBLE;
template <> const hid_t HDF5types<bool>::type = H5T_NATIVE_UINT32;
template <> const hid_t HDF5types<float>::type = H5T_NATIVE_FLOAT;

hid_t Writer::get_particle_group(unsigned int parttype) {
  stringstream groupname;
  groupname << "PartType" << parttype;
  htri_t link = H5Lexists(_file, groupname.str().c_str(), H5P_DEFAULT);
  hid_t group;
  if (link > 0) {
    group = H5Gopen(_file, groupname.str().c_str());
  } else {
    group = H5Gcreate(_file, groupname.str().c_str(), -1);
  }
  return group;
}

Writer::Writer(string filename) {
  _file = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
}

Writer::~Writer() { H5Fclose(_file); }

void Writer::write_header(Header &header) {
  Array<bool, 6> flag_entropy_ics;

  hid_t group = H5Gcreate(_file, "Header", -1);
  write(group, "BoxSize", header.get_box());
  write(group, "Flag_Entropy_ICs", flag_entropy_ics);
  write(group, "MassTable", header.get_masses());
  write(group, "NumFilesPerSnapshot", header.get_numfiles());
  write(group, "NumPart_ThisFile", header.get_npart());
  write(group, "NumPart_Total", header.get_npart_total());
  write(group, "NumPart_Total_HighWord", header.get_npart_highword());
  write(group, "Time", header.get_time());
  write(group, "Redshift", header.get_redshift());
  H5Gclose(group);
}

void Writer::write_block(Block &block) {
  for (unsigned int parttype = 0; parttype < 6; parttype++) {
    if (block.has_data(parttype)) {
      hid_t group = get_particle_group(parttype);
      //            vector<float> data = block.get_data<float>(parttype);
      string name = _names.get_name(block.get_name());
      //            cout << "Writing block: " << name << endl;
      if (!block.get_size(parttype)) {
        error("No data for block \"" + name + "\"!");
      }
      if (block.is_vec()) {
        hsize_t dims[2] = {block.get_size(parttype) / 3, 3};

        vector<char> buffer = block.get_buffer(parttype);

        hid_t filespace = H5Screate_simple(2, dims, NULL);
        hid_t dataset = H5Dcreate(group, name.c_str(), block.get_type(),
                                  filespace, H5P_DEFAULT);
        H5Dwrite(dataset, block.get_type(), H5P_DEFAULT, filespace, H5P_DEFAULT,
                 &buffer[0]);
        H5Sclose(filespace);
        H5Dclose(dataset);
      } else {
        hsize_t dims[1] = {block.get_size(parttype)};

        vector<char> buffer = block.get_buffer(parttype);

        hid_t filespace = H5Screate_simple(1, dims, NULL);
        hid_t dataset = H5Dcreate(group, name.c_str(), block.get_type(),
                                  filespace, H5P_DEFAULT);
        H5Dwrite(dataset, block.get_type(), H5P_DEFAULT, filespace, H5P_DEFAULT,
                 &buffer[0]);
        H5Sclose(filespace);
        H5Dclose(dataset);
      }
      H5Gclose(group);
    }
  }
}
