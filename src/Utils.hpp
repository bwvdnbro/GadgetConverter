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

#ifndef UTILS_HPP
#define UTILS_HPP

// standard library includes (alphabetically)
#include <istream>

namespace Utils{
    inline unsigned int get_blocksize(std::istream& stream){
        unsigned int blocksize;
        stream.read(reinterpret_cast<char*>(&blocksize), sizeof(unsigned int));
        return blocksize;
    }
}

#endif // UTILS_HPP
