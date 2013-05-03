// Copyright Istvan Siroki (stevesiroki@gmail.com) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  THIS FILE IS GENERATED BY ./gen_test.pl 
//  USED TEST CASE FILE: regress.txt
//  DO NOT EDIT MANUALLY!!!

#define BOOST_TEST_DYN_LINK

#include <mpllibs/xlxpressive/regexp_grammar.hpp>

#include <boost/test/unit_test.hpp>

#include <boost/mpl/string.hpp>

#include <string>

#include "search.hpp"

BOOST_AUTO_TEST_CASE(test_grammar)
{
  std::vector<std::string> matched;
  //Number of test cases: 41

  //[test1]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("");
  typedef boost::mpl::string< '^' > Regexp0;
  BOOST_REQUIRE( search< Regexp0 >("", matched) );
  matched.clear();

  //[test2]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("");
  typedef boost::mpl::string< '$' > Regexp1;
  BOOST_REQUIRE( search< Regexp1 >("", matched) );
  matched.clear();

  //[test3]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("A");
  typedef boost::mpl::string< '.' > Regexp2;
  BOOST_REQUIRE( search< Regexp2 >("A", matched) );
  matched.clear();

  //[test4]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("iiiiiii");
  typedef boost::mpl::string< '.*' > Regexp3;
  BOOST_REQUIRE( search< Regexp3 >("iiiiiii", matched) );
  matched.clear();

  //[test5]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("");
  typedef boost::mpl::string< '.*?' > Regexp4;
  BOOST_REQUIRE( search< Regexp4 >("kkkkk", matched) );
  matched.clear();

  //[test6]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("iii");
  typedef boost::mpl::string< '.{2,','4}' > Regexp5;
  BOOST_REQUIRE( search< Regexp5 >("iii", matched) );
  matched.clear();

  //[test7]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("ff");
  typedef boost::mpl::string< '.{2,','4}?' > Regexp6;
  BOOST_REQUIRE( search< Regexp6 >("ffff", matched) );
  matched.clear();

  //[test8_fail]
  BOOST_REQUIRE(true); //perl test
  typedef boost::mpl::string< '.{2,','4}' > Regexp7;
  BOOST_REQUIRE( search< Regexp7 >("i", matched) );
  matched.clear();

  //[test9]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("abcd");
  typedef boost::mpl::string< '^.*$' > Regexp8;
  BOOST_REQUIRE( search< Regexp8 >("abcd", matched) );
  matched.clear();

  //[test10]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("abc");
  typedef boost::mpl::string< '...' > Regexp9;
  BOOST_REQUIRE( search< Regexp9 >("abcde", matched) );
  matched.clear();

  //[test11]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("abcdefghij");
  typedef boost::mpl::string< '^...','....','...$' > Regexp10;
  BOOST_REQUIRE( search< Regexp10 >("abcdefghij", matched) );
  matched.clear();

  //[test12_fail]
  BOOST_REQUIRE(true); //perl test
  typedef boost::mpl::string< '^...','....','...$' > Regexp11;
  BOOST_REQUIRE( search< Regexp11 >("abcdefghijk", matched) );
  matched.clear();

  //[test13]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("abc");
  typedef boost::mpl::string< '^...','$|^.','...$' > Regexp12;
  BOOST_REQUIRE( search< Regexp12 >("abc", matched) );
  matched.clear();

  //[test14]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("abcd");
  typedef boost::mpl::string< '^...','$|^.','...$' > Regexp13;
  BOOST_REQUIRE( search< Regexp13 >("abcd", matched) );
  matched.clear();

  //[test15]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("cd");
  typedef boost::mpl::string< '^.$|','^..$','|^..','.$' > Regexp14;
  BOOST_REQUIRE( search< Regexp14 >("cd", matched) );
  matched.clear();

  //[test16]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("42176");
  typedef boost::mpl::string< '^42.','*$' > Regexp15;
  BOOST_REQUIRE( search< Regexp15 >("42176", matched) );
  matched.clear();

  //[test17]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("pfoobar");
  typedef boost::mpl::string< '^.fo','o.*$' > Regexp16;
  BOOST_REQUIRE( search< Regexp16 >("pfoobar", matched) );
  matched.clear();

  //[test18]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("a");
  typedef boost::mpl::string< '\\w' > Regexp17;
  BOOST_REQUIRE( search< Regexp17 >("a", matched) );
  matched.clear();

  //[test19_fail]
  BOOST_REQUIRE(true); //perl test
  typedef boost::mpl::string< '\\W' > Regexp18;
  BOOST_REQUIRE( search< Regexp18 >("a", matched) );
  matched.clear();

  //[test20]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("1");
  typedef boost::mpl::string< '\\d' > Regexp19;
  BOOST_REQUIRE( search< Regexp19 >("1", matched) );
  matched.clear();

  //[test21_fail]
  BOOST_REQUIRE(true); //perl test
  typedef boost::mpl::string< '\\D' > Regexp20;
  BOOST_REQUIRE( search< Regexp20 >("1", matched) );
  matched.clear();

  //[test22]
  BOOST_REQUIRE(true); //perl test
  matched.push_back(" ");
  typedef boost::mpl::string< '\\s' > Regexp21;
  BOOST_REQUIRE( search< Regexp21 >(" ", matched) );
  matched.clear();

  //[test23_fail]
  BOOST_REQUIRE(true); //perl test
  typedef boost::mpl::string< '\\S' > Regexp22;
  BOOST_REQUIRE( search< Regexp22 >(" ", matched) );
  matched.clear();

  //[test24]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("    ");
  typedef boost::mpl::string< '\\s+' > Regexp23;
  BOOST_REQUIRE( search< Regexp23 >("foo    bar", matched) );
  matched.clear();

  //[test25]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("korte");
  typedef boost::mpl::string< '\\bk','orte','\\b' > Regexp24;
  BOOST_REQUIRE( search< Regexp24 >("almakorte korte diokorte", matched) );
  matched.clear();

  //[test26]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("foo\\\\t");
  typedef boost::mpl::string< 'foo','\\\\','t' > Regexp25;
  BOOST_REQUIRE( search< Regexp25 >("foo\\\\test", matched) );
  matched.clear();

  //[test27]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("\\");
  typedef boost::mpl::string< '\\' > Regexp26;
  BOOST_REQUIRE( search< Regexp26 >("foo\\bar", matched) );
  matched.clear();

  //[test28]
  BOOST_REQUIRE(true); //perl test
  matched.push_back(" ,;:=~<>-_!@#%&");
  typedef boost::mpl::string< ' ,;:','=~<>','-_!@','#%&' > Regexp27;
  BOOST_REQUIRE( search< Regexp27 >(" ,;:=~<>-_!@#%&", matched) );
  matched.clear();

  //[test29]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("$");
  typedef boost::mpl::string< '\\$' > Regexp28;
  BOOST_REQUIRE( search< Regexp28 >("$", matched) );
  matched.clear();

  //[test30]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("^");
  typedef boost::mpl::string< '\\^' > Regexp29;
  BOOST_REQUIRE( search< Regexp29 >("^", matched) );
  matched.clear();

  //[test31]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("$20.0");
  typedef boost::mpl::string< '\\$','\\d+','\\.','\\','d+' > Regexp30;
  BOOST_REQUIRE( search< Regexp30 >("$20.0", matched) );
  matched.clear();

  //[test32]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("42");
  typedef boost::mpl::string< '[','\\d',']+' > Regexp31;
  BOOST_REQUIRE( search< Regexp31 >("42", matched) );
  matched.clear();

  //[test33]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("76768");
  typedef boost::mpl::string< '[678',']+' > Regexp32;
  BOOST_REQUIRE( search< Regexp32 >("76768", matched) );
  matched.clear();

  //[test34]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("23589");
  typedef boost::mpl::string< '^[1-','9][0','-9]+' > Regexp33;
  BOOST_REQUIRE( search< Regexp33 >("23589", matched) );
  matched.clear();

  //[test35_fail]
  BOOST_REQUIRE(true); //perl test
  typedef boost::mpl::string< '^[1-','9][0','-9]+' > Regexp34;
  BOOST_REQUIRE( search< Regexp34 >("02358", matched) );
  matched.clear();

  //[test36]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("foobarfoo");
  typedef boost::mpl::string< '^[ab','for]','+$' > Regexp35;
  BOOST_REQUIRE( search< Regexp35 >("foobarfoo", matched) );
  matched.clear();

  //[test37]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("2001  foobar");
  typedef boost::mpl::string< '[1-9','][0-','9]+','\\s*','[','abfo','r]+$' > Regexp36;
  BOOST_REQUIRE( search< Regexp36 >("2001  foobar", matched) );
  matched.clear();

  //[test38]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("<html>");
  typedef boost::mpl::string< '[<h-','t>]+' > Regexp37;
  BOOST_REQUIRE( search< Regexp37 >("<html>", matched) );
  matched.clear();

  //[test39]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("foobar");
  typedef boost::mpl::string< '^[[:','alph','a:]]','+$' > Regexp38;
  BOOST_REQUIRE( search< Regexp38 >("foobar", matched) );
  matched.clear();

  //[test40]
  BOOST_REQUIRE(true); //perl test
  matched.push_back("5foobar");
  typedef boost::mpl::string< '^[[:','digi','t:]]','[[:a','lpha',':]]+','$' > Regexp39;
  BOOST_REQUIRE( search< Regexp39 >("5foobar", matched) );
  matched.clear();

  //[test41_fail]
  BOOST_REQUIRE(true); //perl test
  typedef boost::mpl::string< '^[[:','lowe','r:]]','+$' > Regexp40;
  BOOST_REQUIRE( search< Regexp40 >("fOo", matched) );
  matched.clear();
}

