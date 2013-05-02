// Copyright Istvan Siroki (stevesiroki@gmail.com) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "../../../mpllibs/xlxpressive/regexp_grammar.hpp"
//#include <mpllibs/xlxpressive/regexp_grammar.hpp>

#include <boost/mpl/string.hpp>

#include <string>

//#include <boost/proto/core.hpp>
//#include <boost/proto/transform/arg.hpp>
//#include <boost/proto/transform/when.hpp>

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
  //const sregex re = ~boost::xpressive::_n >> ~boost::xpressive::_n;
  //const sregex re = (boost::xpressive::s1= boost::xpressive::as_xpr('f') >> boost::xpressive::as_xpr('o') >> boost::xpressive::as_xpr('o'));
  //sregex re = boost::xpressive::after(boost::xpressive::as_xpr('f') >> boost::xpressive::as_xpr('o') >> boost::xpressive::as_xpr('o')) >> boost::xpressive::as_xpr('b') >> boost::xpressive::as_xpr('a') >> boost::xpressive::as_xpr('r');

//  using boost::xpressive::set;
//  using boost::xpressive::range;
//  using boost::xpressive::as_xpr;
//  auto set_expr = range( 'a', 'z' );
//  auto tmp1 = set_expr | range( '0', '9' );
//  set_expr = tmp1;
//  auto tmp2 = set_expr | as_xpr('F');
//  set_expr = tmp2;
//  auto tmp3 = set_expr | as_xpr('O');
//  set_expr = tmp3;
//  auto tmp4 = set_expr | as_xpr('O');
//  set_expr = tmp4;
//  auto tmp5 = set_expr | as_xpr('#');
//  set_expr = tmp5;
//  auto tmp6 = set_expr | as_xpr('_');
//  set_expr = tmp6;
//  sregex re = set[ set_expr ];

//  sregex tmp2 = tmp | as_xpr('F');
//    |  as_xpr('F') | as_xpr('O') | as_xpr('O') | as_xpr('#') | as_xpr('_') ];
//  sregex re = boost::xpressive::set[ boost::xpressive::_w ];
  sregex re = apply_wrap1<regexp_parser, Regexp>::type::run();
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
  std::cout<<"=========================================="<<std::endl;
  return (success && size_check && sub_match);
}

int main()
{
  std::vector<std::string> matched;

  matched.push_back("#2abcabc");
  typedef boost::mpl::string< '[#\\d','abc',']+|','foo' > Regexp1;
  search< Regexp1 >("#2abcabc", matched);
  matched.clear();

//  matched.push_back("a");
//  typedef boost::mpl::string< '[\\w',']' > Regexp2;
//  search< Regexp2 >("a", matched);
//  matched.clear();

}

