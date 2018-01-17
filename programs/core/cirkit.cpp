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

/**
 * @author Mathias Soeken
 * @author Heinz Riener
 */

#include <memory>

#include <alice/alice.hpp>

#include <cli/stores.hpp>
#include <cli/commands/abc.hpp>
#include <cli/commands/bdd.hpp>
#include <cli/commands/blif_to_bench.hpp>
#include <cli/commands/bool_complex.hpp>
#include <cli/commands/comb_approx.hpp>
#include <cli/commands/compress.hpp>
#include <cli/commands/cone.hpp>
#include <cli/commands/contrinv.hpp>
#include <cli/commands/cuts.hpp>
#include <cli/commands/dectest.hpp>
#include <cli/commands/demo.hpp>
#include <cli/commands/depth.hpp>
#include <cli/commands/dsop.hpp>
#include <cli/commands/esop.hpp>
#include <cli/commands/exorcism.hpp>
#include <cli/commands/expr.hpp>
#include <cli/commands/feather.hpp>
#include <cli/commands/gen_npn_circuit.hpp>
#include <cli/commands/gen_trans_arith.hpp>
#include <cli/commands/isop.hpp>
#include <cli/commands/memristor.hpp>
#include <cli/commands/mig_rewrite.hpp>
#include <cli/commands/migfh.hpp>
#include <cli/commands/npn.hpp>
#include <cli/commands/output_noise.hpp>
#include <cli/commands/permmask.hpp>
#include <cli/commands/plim.hpp>
#include <cli/commands/print_io.hpp>
#include <cli/commands/propagate.hpp>
#include <cli/commands/read_sym.hpp>
#include <cli/commands/rename.hpp>
#include <cli/commands/satnpn.hpp>
#include <cli/commands/shuffle.hpp>
#include <cli/commands/simgraph.hpp>
#include <cli/commands/simulate.hpp>
#include <cli/commands/spectral.hpp>
#include <cli/commands/strash.hpp>
#include <cli/commands/support.hpp>
#include <cli/commands/testbdd.hpp>
#include <cli/commands/tt.hpp>
#include <cli/commands/unate.hpp>
#include <cli/commands/worstcase.hpp>
#include <cli/commands/xmgmajdecomp.hpp>
#include <cli/commands/xmgmerge.hpp>

#include <core/utils/bdd_utils.hpp>

#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>

using namespace cirkit;

using cirkit_store_types = boost::mpl::vector<aig_graph, mig_graph, xmg_graph, simple_fanout_graph_t, tt, bdd_function_t, expression_t::ptr, counterexample_t>;

#define STORE_TYPES cirkit_store_types

#include <addon_commands.hpp> // auto-generated file from CMake

template<typename CLI, typename T> struct extend_cli_main;
template<typename T, typename... Ts>
struct extend_cli_main<cli_main<Ts...>, T>
{
  using type = cli_main<Ts..., T>;
};
using cli_t = boost::mpl::fold<STORE_TYPES, cli_main<>, extend_cli_main<boost::mpl::_1, boost::mpl::_2>>::type;


ALICE_BEGIN(cirkit)

  cli_t cli( "cirkit" );

  cli.set_category( "I/O" );

  ADD_READ_COMMAND( aiger, "Aiger" );
  ADD_READ_COMMAND( bench, "Bench" );
  ADD_READ_COMMAND( pla, "PLA" );
  ADD_READ_COMMAND( verilog, "Verilog" );
  ADD_READ_COMMAND( yig, "YIG" );
  ADD_WRITE_COMMAND( aiger, "Aiger" );
  ADD_WRITE_COMMAND( edgelist, "Edge list" );
  ADD_WRITE_COMMAND( pla, "PLA" );
  ADD_WRITE_COMMAND( smt, "SMT-LIB2" );
  ADD_WRITE_COMMAND( verilog, "Verilog" );
  ADD_COMMAND( read_sym );
  ADD_COMMAND( blif_to_bench );

  cli.set_category( "Approximation" );
  ADD_COMMAND( comb_approx );
  ADD_COMMAND( worstcase );

  cli.set_category( "Experimental" );
  ADD_COMMAND( testbdd );

  cli.set_category( "Rewriting" );
  ADD_COMMAND( cone );
  ADD_COMMAND( feather );
  ADD_COMMAND( mig_rewrite );
  ADD_COMMAND( migfh );
  ADD_COMMAND( propagate );
  ADD_COMMAND( rename );
  ADD_COMMAND( shuffle );
  ADD_COMMAND( strash );
  ADD_COMMAND( xmgmerge );

  cli.set_category( "Verification" );
  ADD_COMMAND( simulate );
  ADD_COMMAND( support );
  ADD_COMMAND( unate );

  cli.set_category( "Truth table" );
  ADD_COMMAND( bool_complex );
  ADD_COMMAND( dectest );
  ADD_COMMAND( npn );
  ADD_COMMAND( permmask );
  ADD_COMMAND( spectral );
  ADD_COMMAND( tt );

  cli.set_category( "Synthesis" );
  ADD_COMMAND( isop );

  cli.set_category( "Optimization" );
  ADD_COMMAND( esop );
  ADD_COMMAND( exorcism );

  cli.set_category( "Reverse engineering" );
  ADD_COMMAND( contrinv );
  ADD_COMMAND( cuts );
  ADD_COMMAND( satnpn );
  ADD_COMMAND( simgraph );

  cli.set_category( "RRAM" );
  ADD_COMMAND( memristor );
  ADD_COMMAND( plim );

  cli.set_category( "Generator" );
  ADD_COMMAND( gen_npn_circuit );
  ADD_COMMAND( gen_trans_arith );

  cli.set_category( "Various" );
  ADD_COMMAND( abc );
  ADD_COMMAND( bdd );
  ADD_COMMAND( compress );
  ADD_COMMAND( demo );
  ADD_COMMAND( depth );
  ADD_COMMAND( dsop );
  ADD_COMMAND( expr );
  ADD_COMMAND( output_noise );
  ADD_COMMAND( print_io );
  ADD_COMMAND( xmg_majdecomp );

#include <addon_defines.hpp>

ALICE_END

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
