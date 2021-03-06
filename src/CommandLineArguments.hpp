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

#ifndef COMMANDLINEARGUMENTS_HPP
#define COMMANDLINEARGUMENTS_HPP

#include <string>

class CommandLineArguments {
private:
  /*! \brief Name of the old snapshot to convert */
  std::string _input_name;

  /*! \brief Name of the newly created converted snapshot */
  std::string _output_name;

  /*! \brief Does the snapshot use Gadget file format type 1? */
  bool _type_1;

  void print_usage();

public:
  CommandLineArguments(int argc, char **argv);

  std::string get_input_name();
  std::string get_output_name();
  bool is_type_1();
};

#endif // COMMANDLINEARGUMENTS_HPP
