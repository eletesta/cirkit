/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file dsop.hpp
 *
 * @brief Computes disjoint SOP
 *
 * @author Mathias Soeken
 * @since  2.3
 */

#ifndef CLI_DSOP_COMMAND_HPP
#define CLI_DSOP_COMMAND_HPP

#include <string>

#include <core/cli/command.hpp>
#include <core/cli/environment.hpp>

namespace cirkit
{

class dsop_command : public command
{
public:
  dsop_command( const environment::ptr& env );

protected:
  rules_t validity_rules() const;
  bool execute();

  std::string filename;
  std::string outname;
  unsigned    optfunc = 1u;
  unsigned    sortfunc = 0u;
};

}

#endif

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
