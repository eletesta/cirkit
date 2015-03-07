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
 * @file truth_table_utils.hpp
 *
 * @brief Truth table utilities
 *
 * @author Mathias Soeken
 * @since  2.0
 */

#ifndef TRUTH_TABLE_UTILS_HPP
#define TRUTH_TABLE_UTILS_HPP

#include <boost/dynamic_bitset.hpp>

namespace cirkit
{

/**
 * @brief Truth table type
 *
 * Most of the functions implemented in this file are inspired by
 *   https://bitbucket.org/alanmi/abc/src/768916cc932a3608c7bc8b27d3d4cb0e15727d63/src/misc/util/utilTruth.h?at=default
 *   and
 *   https://bitbucket.org/sterin/pyaig/src/fd77fb0298da597e8b80c85cc7b5391d7ba7d1e4/src/pyaig/truthtables.py?at=default
 *
 * We assume a truth table argues on variables x_0, ..., x_{n-1}
 */
using tt = boost::dynamic_bitset<>;

class tt_store
{
public:
  tt_store( tt_store const& ) = delete;
  void operator=( tt_store const& ) = delete;

  static tt_store& i();
  const unsigned width = 6u;

  inline const tt& operator()( unsigned i ) const
  {
    return tts.at( i );
  }

private:
  tt_store();

  const std::vector<tt> tts  = { tt( 64u, 0xaaaaaaaaaaaaaaaa ),
                                 tt( 64u, 0xcccccccccccccccc ),
                                 tt( 64u, 0xf0f0f0f0f0f0f0f0 ),
                                 tt( 64u, 0xff00ff00ff00ff00 ),
                                 tt( 64u, 0xffff0000ffff0000 ),
                                 tt( 64u, 0xffffffff00000000 ) };
};

/**
 * @brief Constant 0 truth table
 *
 * Has size 2^0
 */
tt tt_const0();

/**
 * @brief Constant 1 truth table
 *
 * Has size 2^0
 */
tt tt_const1();

/*
 * @brief Truth table for function x_i
 *
 * Has size 2^{i+1}
 */
tt tt_nth_var( unsigned i );

/**
 * @brief Returns number of variables in truth table
 *
 * This is not the support size but only n (see above)
 */
unsigned tt_num_vars( const tt& t );

/**
 * @brief Extends a truth table to fit n variables
 */
void tt_extend( tt& t, unsigned to );

/**
 * @brief Aligns two truth tables two same size
 */
void tt_align( tt& t1, tt& t2 );

/**
 * @brief Checks whether x_i is in the support set of t
 */
bool tt_has_var( const tt& t, unsigned i );

/**
 * @brief Returns a bitset which encodes the supporting set
 *
 * The bitset is enabled at position i if x_i is in the
 * support of t.  The bitset is of size n, where n is the
 * size of t.
 */
boost::dynamic_bitset<> tt_support( const tt& t );

/**
 * @brief Returns the number of variables in the support of t
 */
unsigned tt_support_size( const tt& t );

/**
 * @brief Computes the 0 cofactor
 */
tt tt_cof0( const tt& t, unsigned i );

/**
 * @brief Computes the 1 cofactor
 */
tt tt_cof1( const tt& t, unsigned i );

bool tt_cof0_is_const0( const tt& t, unsigned i );
bool tt_cof0_is_const1( const tt& t, unsigned i );
bool tt_cof1_is_const0( const tt& t, unsigned i );
bool tt_cof1_is_const1( const tt& t, unsigned i );
bool tt_cofs_opposite( const tt& t, unsigned i );

/**
 * @brief Existential quantification
 */
tt tt_exists( const tt& t, unsigned i );

/**
 * @brief Universal quantification
 */
tt tt_forall( const tt& t, unsigned i );

/**
 * @brief Permutes variables i and j
 */
tt tt_permute( const tt& t, unsigned i, unsigned j );

/**
 * @brief Removes variable i
 */
tt tt_remove_var( const tt& t, unsigned i );

/**
 * @brief Flips variable i
 */
tt tt_flip( const tt& t, unsigned i );

/**
 * @brief Compact truth table to minbase
 *
 * If `psupport' variable is given, then the support is stored
 * there which anyway needs to be computed.
 */
void tt_to_minbase( tt& t, boost::dynamic_bitset<>* psupport = nullptr );

/**
 * @brief Compact truth table to minbase and discard some variables
 *
 * If `psupport' variable is given, then the support is stored
 * there which anyway needs to be computed.
 */
void tt_to_minbase_and_discard( tt& t, unsigned max_size = 6u, boost::dynamic_bitset<>* psupport = nullptr );

/**
 * @brief Uncompact truth table
 */
void tt_from_minbase( tt& t, const boost::dynamic_bitset<> pattern );

std::string tt_to_hex( const tt& t );

}

#endif

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
