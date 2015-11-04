#include "CommandLineArguments.hpp"
#include "Error.hpp"

#include <iostream>

#include <getopt.h>

using namespace std;

enum CommandLineArgumentNames{
    ARGUMENT_INPUT_NAME,
    ARGUMENT_OUTPUT_NAME
};

CommandLineArguments::CommandLineArguments(int argc, char **argv){
    // read the command line arguments using getopt
    static struct option long_options[] = {
        {"input_name", required_argument, NULL, ARGUMENT_INPUT_NAME},
        {"output_name", required_argument, NULL, ARGUMENT_OUTPUT_NAME},
        {0, 0, 0, 0}
    };
    
    int c;
    opterr = 0;
    while((c = getopt_long(argc, argv, "i:o:", long_options, NULL)) != -1){
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
        case '?':
        {
            cout << "warning: unknown command line argument \""
                 << argv[optind-1] << "\" is ignored" << endl;
            break;
        }
        default:
            // NEVER END UP HERE
            break;
        }
    }
    
    // check if all obligatory arguments have been specified
    if(!_input_name.size()){
        error("Error: no input file name given!");
    }
    if(!_output_name.size()){
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
