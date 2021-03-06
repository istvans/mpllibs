// Copyright Abel Sinkovics (abel@sinkovics.hu) 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metamonad/match.hpp>
#include <mpllibs/metamonad/metafunction.hpp>
#include <mpllibs/metamonad/exception.hpp>
#include <mpllibs/metamonad/syntax.hpp>
#include <mpllibs/metamonad/box.hpp>
#include <mpllibs/metamonad/tmp_value.hpp>
#include <mpllibs/metamonad/eval_guard.hpp>
#include <mpllibs/metamonad/pair.hpp>

#include <boost/test/unit_test.hpp>

#include <boost/type_traits.hpp>

#include <boost/mpl/map.hpp>
#include <boost/mpl/assert.hpp>

#include "common.hpp"
#include "same_map.hpp"
#include "is_empty.hpp"

using mpllibs::metamonad::tmp_value;

namespace
{
  template <class A, class B, class C>
  struct some_template : tmp_value<some_template<A, B, C> > {};
}

BOOST_AUTO_TEST_CASE(test_match)
{
  using mpllibs::metamonad::match;
  using mpllibs::metamonad::_;
  using mpllibs::metamonad::var;
  using mpllibs::metamonad::exception;
  using mpllibs::metamonad::bad_match;
  using mpllibs::metamonad::syntax;
  using mpllibs::metamonad::box;
  using mpllibs::metamonad::eval_guard;
  using mpllibs::metamonad::pair;

  using boost::mpl::na;
  using boost::mpl::map;

  using boost::is_same;

  // test_match_any
  BOOST_MPL_ASSERT((is_empty<match<syntax<_>, int13> >));

  // test_no_match
  BOOST_MPL_ASSERT((
    is_same<
      exception<bad_match<box<double>, box<int> > >,
      match<syntax<box<double> >, box<int> >::type
    >
  ));

  // test_match_same_type
  BOOST_MPL_ASSERT((is_empty<match<syntax<box<int> >, box<int> > >));

  // test_match_var
  BOOST_MPL_ASSERT((
    same_map<map<pair<x, syntax<int13> > >, match<syntax<x>, int13>::type>
  ));

  // test_nested_match_any
  BOOST_MPL_ASSERT((
    is_empty<
      match<
        syntax<some_template<_, box<int>, box<double> > >,
        some_template<box<char>, box<int>, box<double> >
      >
    >
  ));

  // test_bad_nested_match
  BOOST_MPL_ASSERT((
    is_same<
      exception<bad_match<box<int>, box<char> > >,
      match<
        syntax<some_template<box<int>, box<int>, box<double> > >,
        some_template<box<char>, box<int>, box<double> >
      >::type
    >
  ));

  // test_match_nested_var
  BOOST_MPL_ASSERT((
    same_map<
      map<pair<x, syntax<int13> > >,
      match<
        syntax<some_template<box<int>, box<double>, x> >,
        some_template<box<int>, box<double>, int13>
      >::type
    >
  ));

  // test_match_nested_var_twice
  BOOST_MPL_ASSERT((
    same_map<
      map<pair<x, syntax<int13> > >,
      match<
        syntax<some_template<x, box<double>, x> >,
        some_template<int13, box<double>, int13>
      >::type
    >
  ));

  // test_nested_var_twice_doesnt_match
  BOOST_MPL_ASSERT((
    is_same<
      exception<bad_match<x, syntax<box<double> > > >,
      match<
        syntax<some_template<x, box<int>, x> >,
        some_template<box<char>, box<int>, box<double> >
      >::type
    >
  ));

  // test_two_vars
  BOOST_MPL_ASSERT((
    same_map<
      map<pair<x, syntax<int13> >, pair<y, syntax<int11> > >,
      match<
        syntax<some_template<y, box<double>, x> >,
        some_template<int11, box<double>, int13>
      >::type
    >
  ));

  // test_match_with_na_template_argument
  BOOST_MPL_ASSERT((
    same_map<
      map<pair<x, syntax<na> > >,
      match<syntax<some_template<x, _, _> >, some_template<na, na, na> >::type
    >
  ));

  // test_match_with_eval_guard
  BOOST_MPL_ASSERT((
    same_map<
      map<pair<x, syntax<int13> > >,
      match<syntax<eval_guard<x> >, eval_guard<int13> >::type
    >
  ));
}


