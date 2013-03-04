// Copyright Istvan Siroki (stevesiroki@gmail.com) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  THIS FILE IS GENERATED BY ./gen_test.pl 
//  DO NOT EDIT MANUALLY!!!

#define BOOST_TEST_DYN_LINK

#include <mpllibs/xlxpressive/regexp_grammar.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/mpl/string.hpp>

#include <string>

#include "search.hpp"

BOOST_AUTO_TEST_CASE(test_grammar)
{
  using boost::mpl::string;

  BOOST_REQUIRE(true); //perl test
  typedef string< '^' > pattern0;
  BOOST_REQUIRE( search< pattern0 >("hello") );
}

