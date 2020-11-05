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

#include "NameMap.hpp"
#include "Paths.hpp"

#include <fstream>
#include <iostream>
using namespace std;

NameMap::NameMap() {
  ifstream ifile(NAMEMAP_PATH);
  if (ifile.good()) {
    std::string key;
    std::string name;
    while (ifile.good()) {
      ifile >> key >> name;
      _dict[key] = name;
    }
  } else {
    // Error!
  }
}

string NameMap::get_name(string key) { return _dict[key]; }

void NameMap::print_contents() {
  typedef map<string, string>::iterator iterator;
  for (iterator it = _dict.begin(); it != _dict.end(); ++it) {
    cout << it->first << ": " << it->second << endl;
  }
}
