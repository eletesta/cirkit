/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
 * Copyright (C) 2015-2017  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "xmgmajdecomp.hpp"

#include <core/utils/program_options.hpp>
#include <cli/stores.hpp>
#include <classical/xmg/xmg.hpp>
#include <classical/xmg/xmg_exact_decomp.hpp>

namespace cirkit
{

xmg_majdecomp_command::xmg_majdecomp_command( const environment::ptr& env )
  : cirkit_command( env, "Decomposition into 2 functions for maj-n decomposition and exact expression" )
{
  add_positional_option( "filename" );
  opts.add_options() 
	( "filename",  value_with_default( &filename ),           "filename for output dimacs" )
    ( "inputs", value_with_default( &inputs ),   "number of inputs" )
    ( "gates", value_with_default( &gates ),     "number of gates" )
    ;
  add_new_option();
}

bool xmg_majdecomp_command::execute()
{
	
	boost::optional<xmg_graph> g; 
	if (inputs == 4)
	{
		g = xmg_exact_decomposition<4, 3>(filename);
	}
	
	if (inputs == 6)
	{
	    g = xmg_exact_decomposition<6, 6>(filename);
	}
	
	if (inputs == 8)
	{
		if (gates == 10)
		g = xmg_exact_decomposition<8, 10>(filename);
		if (gates == 9)
		g = xmg_exact_decomposition<8, 9>(filename);
		if (gates == 11)
		g = xmg_exact_decomposition<8, 11>(filename);
	}

    if ( g != boost::none )
    {
      auto& xmgs = env->store<xmg_graph>();
      xmgs.extend();
      xmgs.current() = *g;
    }

  return true;
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
