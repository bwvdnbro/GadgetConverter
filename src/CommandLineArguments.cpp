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

#include "CommandLineArguments.hpp"
#include "Error.hpp"

#include <iostream>

#include <getopt.h>

using namespace std;

enum CommandLineArgumentNames{
    ARGUMENT_INPUT_NAME,
    ARGUMENT_OUTPUT_NAME,
    ARGUMENT_HELP
};


void CommandLineArguments::print_usage(){
    cout << "USAGE: GadgetConverter --input_name NAME --output_name NAME"
         << endl;
}

CommandLineArguments::CommandLineArguments(int argc, char **argv){
    // read the command line arguments using getopt
    static struct option long_options[] = {
        {"input_name", required_argument, NULL, ARGUMENT_INPUT_NAME},
        {"output_name", required_argument, NULL, ARGUMENT_OUTPUT_NAME},
        {"help", no_argument, NULL, ARGUMENT_HELP},
        {0, 0, 0, 0}
    };

    int c;
    opterr = 0;
    while((c = getopt_long(argc, argv, "i:o:h", long_options, NULL)) != -1){
        switch(c){
        case ARGUMENT_INPUT_NAME:
        {
            _input_name = optarg;
            break;
        }
        case ARGUMENT_OUTPUT_NAME:
        {
            _output_name = optarg;
            break;
        }
        case ARGUMENT_HELP:
        {
            print_usage();
            exit(0);
            break;
        }
        case '?':
        {
            cout << "warning: unknown command line argument \""
                 << argv[optind-1] << "\" is ignored" << endl;
            print_usage();
            break;
        }
        default:
            // NEVER END UP HERE
            break;
        }
    }

    // check if all obligatory arguments have been specified
    if(!_input_name.size()){
        print_usage();
        error("Error: no input file name given!");
    }
    if(!_output_name.size()){
        print_usage();
        error("Error: no output file name given!");
    }

    // make sure the _output_name contains a .hdf5 extension
    if(_output_name.find(".hdf5") != _output_name.size()-5){
        _output_name += string(".hdf5");
    }
}

std::string CommandLineArguments::get_input_name(){
    return _input_name;
}

std::string CommandLineArguments::get_output_name(){
    return _output_name;
}
