// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metaparse/util/curry.hpp>

#include "common.hpp"

#include <mpllibs/metatest/test.hpp>
#include <mpllibs/metatest/has_type.hpp>
#include <mpllibs/metatest/to_stream_fwd.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/identity.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

namespace
{
  using std::ostream;
  using boost::mpl::identity;

  template <class A, class B>
  struct get_first : identity<A> {};
  
  template <class A, class B>
  struct get_second : identity<B> {};
  
  typedef identity<int13> nullary_metafunction;
}

MPLLIBS_DEFINE_TO_STREAM_FOR_TEMPLATE(2, get_first, "get_first")
MPLLIBS_DEFINE_TO_STREAM_FOR_TEMPLATE(2, get_second, "get_second")

BOOST_AUTO_TEST_CASE(test_curry)
{
  using mpllibs::metatest::has_type;
  using mpllibs::metatest::meta_require;
  
  using mpllibs::metaparse::util::curry0;
  using mpllibs::metaparse::util::curry2;
  
  using boost::mpl::equal_to;
  using boost::mpl::apply_wrap1;

  meta_require<has_type<curry2<get_second> > >(MPLLIBS_HERE, "test_has_type");

  meta_require<
    equal_to<
      apply_wrap1<apply_wrap1<curry2<get_first>, int11>::type, int13>::type,
      int11
    >
  >(MPLLIBS_HERE, "test_currying_first_argument");

  meta_require<
    equal_to<
      apply_wrap1<apply_wrap1<curry2<get_second>, int11>::type, int13>::type,
      int13
    >
  >(MPLLIBS_HERE, "test_currying_second_argument");

  meta_require<
    equal_to<curry0<nullary_metafunction>::type, int13>
  >(MPLLIBS_HERE, "test_nullary");
}


