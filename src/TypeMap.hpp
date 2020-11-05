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

#ifndef TYPEMAP_HPP
#define TYPEMAP_HPP

// standard library includes
#include <map>
#include <string>

// external library includes
#include <hdf5.h>

class TypeMap {
private:
  std::map<std::string, hid_t> _dict;

public:
  TypeMap();

  hid_t get_type(std::string key);

  void print_contents();
};

#endif // TYPEMAP_HPP
