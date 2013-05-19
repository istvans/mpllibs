// Copyright István Siroki (stevesiroki@gmail.com)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/xlxpressive/xlxpressive.hpp>

using namespace boost::xpressive;
using namespace std;

struct test_case
{
  test_case(const string _text, const sregex _xpressive_pattern, const sregex _xlxpressive_pattern) : text(_text), xpressive_pattern(_xpressive_pattern), xlxpressive_pattern(_xlxpressive_pattern) {}

  string text;
  sregex xpressive_pattern;
  sregex xlxpressive_pattern;

  smatch wx, wxl;

  bool test()
  {
    return regex_search(text, wx, xpressive_pattern) && regex_search(text, wxl, xlxpressive_pattern);
  }
};

int main()
{
  vector<test_case> test_cases;
  using boost::xpressive::set;

  test_cases.push_back(test_case("hello world!",
      ((s1= +_w) >> ' ' >> (s2= +_w) >> '!'),
      MPLLIBS_REGEX("(\\w+) (\\w+)!")));
  
  test_cases.push_back(test_case("$12.34",
        ('$' >> +_d >> '.' >> _d >> _d),
        MPLLIBS_REGEX("\\$\\d+\\.\\d\\d")));

  test_cases.push_back(test_case("c5.foo",
        (bos >> set[as_xpr('a')|'b'|'c'|'d'] >> range('3','8') >> '.' >> 'f' >> 'o' >> 'o'  >> eos),
        MPLLIBS_REGEX("^[abcd][3-8]\\.foo$")));

  test_cases.push_back(test_case("1234.56789F",
        (bos>>(s1=+range('0','9')>>!(s2='.'>>*range('0','9')))>>(s3=set[as_xpr('C')|'F'])>>eos),
        MPLLIBS_REGEX("^([0-9]+(\\.[0-9]*)?)([CF])$")));

  int matched = 0;
  int i = 1;
  for(std::vector<test_case>::iterator it = test_cases.begin(); it != test_cases.end(); ++it, ++i) {
    cout << i << ". ";
    if (it->test()) {
      cout << "MATCH" << endl;
      ++matched;
    }
    else
      cout << "NOT MATCH" << endl;
  }  

  cout << "Matched: " << matched << '/' << test_cases.size() << endl;

  return 0;
}

