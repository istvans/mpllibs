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
bool search(const std::string& s, const std::vector<std::string>& m)
{
  using boost::xpressive::sregex;
  using boost::xpressive::smatch;
  using boost::xpressive::regex_search;

  using boost::mpl::apply_wrap1;

  using mpllibs::xlxpressive::regexp_parser;

  //const sregex re = boost::xpressive::bos >> *~boost::xpressive::_n >> boost::xpressive::eos;
  //const sregex re = boost::xpressive::bos >> boost::xpressive::eos;
  const sregex re = apply_wrap1<regexp_parser, Regexp>::type::run();
  smatch w;

  bool success = regex_search(s, w, re);
  std::cout << "success: " << success << std::endl;
  if ( !success && m.size() == 0 ) {
    success = true;
  }
  else if ( (success && m.size() == 0) || (!success && m.size() != 0) ) {
    success = false;
  }
  std::cout << "matching expected success: " << success << std::endl;

  bool size_check = w.size() == m.size();
  std::cout << "size_check: " << size_check << " | " << w.size() << " ~ " << m.size() << std::endl;

  bool sub_match = true;
  for (int i = 0; i < w.size(); ++i) {
    std::cout << "'" << w[i].str() << "'" << std::endl;
    if (i >= m.size() || w[i].str() != m[i]) {
      sub_match = false;
      break;
    }
  }
  std::cout << "sub_match: " << sub_match << std::endl;

  std::cout << "RESULT: " << (success && size_check && sub_match) << std::endl;
  std::cout << "====================================================" << std::endl;
  return (success && size_check && sub_match);
}

