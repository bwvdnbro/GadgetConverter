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

#ifndef READER_HPP
#define READER_HPP

// forward declarations (alphabetically)
class Block;

// local includes
#include "Header.hpp"

// standard library includes (alphabetically)
#include <fstream>
#include <string>
#include <vector>

class Reader {
private:
  std::ifstream _file;
  Header _header;
  std::vector<Block *> _blocks;

public:
  Reader(std::string filename, bool type_1);
  ~Reader();

  Header &get_header();
  std::vector<Block *> &get_blocks();
};

#endif // READER_HPP
