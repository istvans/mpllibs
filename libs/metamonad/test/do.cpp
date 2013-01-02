// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_DYN_LINK

#include <mpllibs/metamonad/do.hpp>
#include <mpllibs/metamonad/tmp_tag.hpp>
#include <mpllibs/metamonad/tmp_value.hpp>
#include <mpllibs/metamonad/returns.hpp>
#include <mpllibs/metamonad/lazy_metafunction.hpp>
#include <mpllibs/metamonad/metafunction.hpp>
#include <mpllibs/metamonad/eval_let.hpp>
#include <mpllibs/metamonad/let.hpp>

#include <mpllibs/metatest/boost_test.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/type_traits.hpp>

#include "common.hpp"

using boost::mpl::apply;
using boost::mpl::equal_to;
using boost::mpl::minus;

using mpllibs::metamonad::do_;
using mpllibs::metamonad::set;
using mpllibs::metamonad::do_return;
using mpllibs::metamonad::tmp_tag;
using mpllibs::metamonad::tmp_value;
using mpllibs::metamonad::returns;
using mpllibs::metamonad::lazy;

/*
 * WrapperMonad
 */
namespace
{
  struct wrapper_tag : tmp_tag<wrapper_tag> {};

  typedef wrapper_tag wrapper_monad;

  MPLLIBS_METAFUNCTION(wrapped, (T)) ((tmp_value<wrapped<T>, wrapper_tag>));

  template <class T>
  struct unwrap;

  template <class T>
  struct unwrap<wrapped<T> > : returns<T> {};
}

MPLLIBS_DEFINE_TO_STREAM_FOR_TEMPLATE(1, wrapped, "wrapped")

namespace mpllibs
{
  namespace metamonad
  {
    template <>
    struct monad<wrapper_tag>
    {
      MPLLIBS_METAFUNCTION_CLASS(return_, (T)) ((wrapped<T>));
      MPLLIBS_METAFUNCTION_CLASS(bind, (A)(F)) ((boost::mpl::apply<F, A>));
    };
  }
}

namespace boost
{
  namespace mpl
  {
    template <>
    struct equal_to_impl<wrapper_tag, wrapper_tag>
    {
      MPLLIBS_LAZY_METAFUNCTION(apply, (A)(B))
      ((lazy<equal_to<unwrap<A>, unwrap<B> > >));
    };
  }
}

namespace
{
  MPLLIBS_LAZY_METAFUNCTION(minus_2, (A)) ((lazy<right<minus<A, int2> > >));
  
  MPLLIBS_LAZY_METAFUNCTION(eval_to_right, (T)) ((right<T>));
}

BOOST_AUTO_TEST_CASE(test_do)
{
  using mpllibs::metatest::meta_require;

  using mpllibs::metamonad::lazy;
  using mpllibs::metamonad::let;
  using mpllibs::metamonad::eval_let;

  using boost::is_same;

  meta_require<
    equal_to<
      right<int11>,
      do_<either,
        set<x, do_return<int13> >,
        minus_2<x>
      >::type
    >
  >(MPLLIBS_HERE, "test_do");

  meta_require<
    equal_to<
      right<int9>,
      do_<either,
        set<x, do_return<int13> >,
        set<y, minus_2<x> >,
        minus_2<y>
      >::type
    >
  >(MPLLIBS_HERE, "test_do_three_steps");

  meta_require<
    equal_to<
      right<int9>,
      do_<either,
        set<x, do_return<int13> >,
        set<y, minus_2<x> >,
        minus_2<x>,
        minus_2<y>
      >::type
    >
  >(MPLLIBS_HERE, "test_do_two_calls");

  meta_require<
    equal_to<
      right<int13>,
      do_<either,
        do_return<int11>,
        do_return<int13>
      >::type
    >
  >(MPLLIBS_HERE, "test_do_two_returns");

  meta_require<
    equal_to<
      right<right<int13> >,
      do_<either,
        do_return<
          do_<either,
            do_return<int13>
          >
        >
      >::type
    >
  >(MPLLIBS_HERE, "test_nested_do_with_return");

  meta_require<
    equal_to<
      right<right<int13> >,
      do_<either,
        do_return<do_return<int13> >
      >::type
    >
  >(MPLLIBS_HERE, "test_contents_of_return_is_substituted");

  meta_require<
    equal_to<
      right<int13>,
      lazy<
        do_<either,
          set<x, do_return<int13> >,
          do_return<x>
        >
      >::type
    >
  >(MPLLIBS_HERE, "test_do_in_lazy");

  meta_require<
    equal_to<
      right<wrapped<int13> >,
      do_<either,
        eval_to_right<
          do_<wrapper_monad,
            do_return<int13>
          >
        >
      >::type
    >
  >(MPLLIBS_HERE, "test_nested_do_with_different_monads");

  meta_require<
    equal_to<
      right<int13>,
      eval_let<
        x, int11,
        do_<either,
          set<x, do_return<int13> >,
          do_return<x>
        >
      >::type
    >
  >(MPLLIBS_HERE, "test_set_in_let");

  meta_require<
    equal_to<
      right<int11>,
      eval_let<
        x, int11,
        do_<either,
          set<x, do_return<int13> >,
          do_return<int11>
        >
      >::type
    >
  >(MPLLIBS_HERE, "test_argument_of_set_and_do_in_let");

  meta_require<
    equal_to<
      right<int11>,
      eval_let<
        x, int11,
        do_<either,
          set<y, do_return<x> >,
          set<x, do_return<int13> >,
          do_return<y>
        >
      >::type
    >
  >(MPLLIBS_HERE, "test_let_before_override");

  meta_require<
    is_same<
      do_<either, do_return<int11> >,
      let<x, int11, do_<either, do_return<int11> > >::type
    >
  >(MPLLIBS_HERE, "test_na_arguments_of_do");
}

MPLLIBS_DEFINE_TO_STREAM_FOR_TEMPLATE(1, minus_2, "minus_2")
MPLLIBS_DEFINE_TO_STREAM_FOR_TEMPLATE(1, eval_to_right, "eval_to_right")



