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

// project includes (alphabetically)
#include "Header.hpp"
#include "Error.hpp"
#include "Utils.hpp"

// standard library includes (alphabetically)
#include <iostream>

// namespaces
using namespace std;
using namespace Utils;

//# public methods

Header::Header() : _time(0.), _redshift(0.) {}

Header::Header(istream &stream, bool type_1) {
  unsigned int blocksize;
  if (!type_1) {
    blocksize = get_blocksize(stream);
    char name[4];
    stream.read(name, 4);
    get_blocksize(stream);
    blocksize -= get_blocksize(stream);
    if (blocksize) {
      error("Wrong blocksize!");
    }
  }
  blocksize = get_blocksize(stream);
  read(stream, _npart);
  read(stream, _masses);
  read(stream, _time);
  read(stream, _redshift);
  read(stream, _flag_sfr);
  read(stream, _flag_feedback);
  read(stream, _npart_total);
  read(stream, _flag_cooling);
  read(stream, _num_files);
  read(stream, _box[0]);
  // the box is always a cube
  _box[1] = _box[0];
  _box[2] = _box[0];
  read(stream, _omega0);
  read(stream, _omega_lambda);
  read(stream, _hubble_param);
  read(stream, _hubble_a);
  read(stream, _flag_stellar_age);
  read(stream, _flag_metals);
  read(stream, _npart_total_highword);
  read(stream, _flag_entropy_instead_u);

  char rest[52];
  stream.read(rest, 52);
  blocksize -= get_blocksize(stream);
  if (blocksize) {
    error("Wrong blocksize!");
  }
}

Array<unsigned int, 6> &Header::get_npart() { return _npart; }

Array<double, 6> &Header::get_masses() { return _masses; }

double Header::get_time() { return _time; }

Array<double, 3> &Header::get_box() { return _box; }

int Header::get_numfiles() { return _num_files; }

Array<unsigned int, 6> &Header::get_npart_total() { return _npart_total; }

Array<unsigned int, 6> &Header::get_npart_highword() {
  return _npart_total_highword;
}

double Header::get_redshift() { return _redshift; }

void Header::print_contents() {
  cout << "Header:" << endl;
  cout << "npart: " << _npart[0] << ", " << _npart[1] << ", " << _npart[2]
       << ", " << _npart[3] << ", " << _npart[4] << ", " << _npart[5] << endl;
  cout << "masses: " << _masses[0] << ", " << _masses[1] << ", " << _masses[2]
       << ", " << _masses[3] << ", " << _masses[4] << ", " << _masses[5]
       << endl;
  cout << "time: " << _time << endl;
  cout << "redshift: " << _redshift << endl;
}
