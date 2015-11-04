#ifndef COMMANDLINEARGUMENTS_HPP
#define COMMANDLINEARGUMENTS_HPP

#include <string>

class CommandLineArguments{
private:
    /*! \brief Name of the old snapshot to convert */
    std::string _input_name;
    
    /*! \brief Name of the newly created converted snapshot */
    std::string _output_name;

public:
    CommandLineArguments(int argc, char **argv);
    
    std::string get_input_name();
    std::string get_output_name();
};

#endif // COMMANDLINEARGUMENTS_HPP
