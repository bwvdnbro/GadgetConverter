/*******************************************************************************
 * This file is part of GadgetConverter
 * Copyright (C) 2017 Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
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

#include "Type1List.hpp"
#include "Paths.hpp"

#include <fstream>
#include <iostream>

using namespace std;

Type1List::Type1List() {
  ifstream ifile(TYPE1LIST_PATH);
  if (ifile.good()) {
    string element;
    while (ifile >> element) {
      _list.push_back(element);
    }
  } else {
    // error!
  }
  _curpos = 0;
}

bool Type1List::has_next_field() { return _curpos < _list.size(); }

string Type1List::get_next_field() {
  unsigned int curpos = _curpos;
  ++_curpos;
  return _list[curpos];
}

void Type1List::print_contents() {
  for (unsigned int i = 0; i < _list.size(); ++i) {
    cout << "List[" << i << "]: '" << _list[i] << "'" << endl;
  }
}
