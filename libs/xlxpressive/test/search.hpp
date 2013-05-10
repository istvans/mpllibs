// Copyright Istvan Siroki (stevesiroki@gmail.com) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/xlxpressive/regexp_grammar.hpp>

#include <boost/test/unit_test.hpp>

#include <boost/mpl/string.hpp>

#include <string>

struct nested_result_analyzer
{
  const std::vector<std::string>* _m;
  bool* _sub_match;
  int _k;

  nested_result_analyzer(const std::vector<std::string>& m, bool& sub_match) :
    _m(&m), _sub_match(&sub_match), _k(-1) {}

  template <class T>
  void operator()(T w)
  {
    for (int i = 0; i < w.size(); ++i) {
      std::cout << "Got: " << w[i].str() << std::endl;
      if (w[i].str() == "") // throw away empty_seq
        continue;

      ++_k;
      if (_k >= _m->size()) {
        *_sub_match = false;
        continue;
      }
      else if ( w[i].str() != (*_m)[_k]) {
        *_sub_match = false;
      }
      std::cout << w[i].str() << "'" << " VS " << "'" << (*_m)[_k] << "'" << std::endl;
    }
  }

  int size() const
  {
    return (_k + 1);
  }
};


template <class Regexp>
bool search(const std::string& s, const std::vector<std::string>& m)
{
  using boost::xpressive::sregex;
  using boost::xpressive::smatch;
  using boost::xpressive::regex_search;

  using boost::mpl::apply_wrap1;

  using mpllibs::xlxpressive::regexp_parser;

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
  for (int i = 0; i < m.size(); ++i) {
    if (i >= w.size()) {
      sub_match = false;
      continue;
    }
    else if(w[i].str() != m[i]) {
      sub_match = false;
    }
    std::cout << "'" << w[i].str() << "'" << " VS " << "'" << m[i] << "'" << std::endl;
  }
  std::cout << "sub_match: " << sub_match << std::endl;

  // If sub_match and size_check failed, try to match with nested results
  if (!sub_match && !size_check) {
    if ( w.nested_results().size() > 0) {
      std::cout << "Trying to check with nested results..." << std::endl;

      sub_match = true;
      nested_result_analyzer nra(m, sub_match);
      nra = std::for_each(
        w.nested_results().begin(),
        w.nested_results().end(),
        nra);
      
      size_check = nra.size() == m.size();
      std::cout << "size_check: " << size_check << " | " << nra.size() << " ~ " << m.size() << std::endl;
      std::cout << "sub_match: " << sub_match << std::endl;
    }
  }

  std::cout << "RESULT: " << (success && size_check && sub_match) << std::endl;
  std::cout << "====================================================" << std::endl;
  return (success && size_check && sub_match);
}

