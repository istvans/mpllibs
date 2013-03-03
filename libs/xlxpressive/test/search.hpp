// Copyright Istvan Siroki (stevesiroki@gmail.com) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/xlxpressive/regexp_grammar.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/mpl/string.hpp>

#include <string>

template <class Regexp>
bool search(const std::string& s)
{
  using boost::xpressive::sregex;
  using boost::xpressive::smatch;
  using boost::mpl::apply_wrap1;
  using boost::xpressive::regex_search;

  using mpllibs::xlxpressive::regexp_parser;

  const sregex re = apply_wrap1<regexp_parser, Regexp>::type::run();
  smatch w;
  return regex_search(s, w, re);
}

