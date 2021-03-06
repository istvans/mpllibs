// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metaparse/digit_val.hpp>
#include <mpllibs/metaparse/is_error.hpp>
#include <mpllibs/metaparse/source_position.hpp>
#include <mpllibs/metaparse/get_result.hpp>

#include "common.hpp"

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_digit_val)
{
  using mpllibs::metaparse::is_error;
  using mpllibs::metaparse::digit_val;
  using mpllibs::metaparse::start;
  using mpllibs::metaparse::get_result;
  
  using boost::mpl::apply_wrap2;
  using boost::mpl::equal_to;

  // test_with_text
  BOOST_MPL_ASSERT((is_error<apply_wrap2<digit_val, str_hello, start> >));

  // test_with_number
  BOOST_MPL_ASSERT((
    equal_to<get_result<apply_wrap2<digit_val, str_1983, start> >::type, int1>
  ));

  // test_with_empty_string
  BOOST_MPL_ASSERT((is_error<apply_wrap2<digit_val, str_, start> >));
}

