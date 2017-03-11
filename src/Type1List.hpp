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

#ifndef TYPE1LIST_HPP
#define TYPE1LIST_HPP

// standard library includes
#include <vector>
#include <string>

class Type1List{
private:
    std::vector< std::string > _list;
    unsigned int _curpos;

public:
    Type1List();

    bool has_next_field();
    std::string get_next_field();

    void print_contents();
};

#endif // TYPE1LIST_HPP
