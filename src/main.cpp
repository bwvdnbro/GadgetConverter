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

#include "Block.hpp"
#include "CommandLineArguments.hpp"
#include "Header.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv){
    CommandLineArguments args(argc, argv);

    Reader reader(args.get_input_name());
    
    Header header = reader.get_header();
    vector< Block* > blocks = reader.get_blocks();
    
    Writer writer(args.get_output_name());
    writer.write_header(header);
    for(unsigned int i = 0; i < blocks.size(); i++){
        writer.write_block(*blocks[i]);
    }
    
    return 0;
}
