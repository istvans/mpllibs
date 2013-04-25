#ifndef MPLLIBS_XLXPRESSIVE_REGEXP_GRAMMAR_HPP
#define MPLLIBS_XLXPRESSIVE_REGEXP_GRAMMAR_HPP

// Copyright Istvan Siroki (stevesiroki@gmail.com)  2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <assert.h>

#include <mpllibs/metaparse/lit_c.hpp>
#include <mpllibs/metaparse/build_parser.hpp>
#include <mpllibs/metaparse/entire_input.hpp>
#include <mpllibs/metaparse/always.hpp>
#include <mpllibs/metaparse/one_of.hpp>
#include <mpllibs/metaparse/sequence.hpp>
#include <mpllibs/metaparse/transform.hpp>
#include <mpllibs/metaparse/return.hpp>
#include <mpllibs/metaparse/any1.hpp>
#include <mpllibs/metaparse/any.hpp>
#include <mpllibs/metaparse/digit_val.hpp>

#include <boost/xpressive/regex_primitives.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/char.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/for_each.hpp>

using boost::mpl::front;
using boost::mpl::back;
using boost::mpl::at;
using boost::mpl::char_;
using boost::mpl::int_;
using boost::mpl::for_each;

namespace mpllibs
{
  namespace xlxpressive
  {
    struct build_bos
    {
      typedef build_bos type;
      static boost::xpressive::sregex run() {
        return boost::xpressive::bos;
      }
    };
    typedef metaparse::always< metaparse::lit_c<'^'>, build_bos > bos;

    //=========================================================================

    struct build_eos
    {
      typedef build_eos type;
      static boost::xpressive::sregex run() {
        return boost::xpressive::eos;
      }
    };
    typedef metaparse::always< metaparse::lit_c<'$'>, build_eos > eos;
    
    //=========================================================================
    
    struct build_any
    {
      typedef build_any type;
      static boost::xpressive::sregex run() {
        return ~boost::xpressive::_n;
      }
    };
    typedef metaparse::always< metaparse::lit_c<'.'>, build_any > any;
    
    //=========================================================================

    typedef metaparse::one_of<
      xlxpressive::bos,
      xlxpressive::eos,
      xlxpressive::any
    >
    item;
    
    //=========================================================================

    //a  -> a
    struct no_repeat
    {
      typedef no_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return base;
      }
    };
    //a* -> *a
    struct any_repeat
    {
      typedef any_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return *base;
      }
    };
    //a+ -> +a
    struct any1_repeat
    {
      typedef any1_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return +base;
      }
    };
    //a? -> !a
    struct may_repeat
    {
      typedef may_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return !base;
      }
    };
    //a*? -> -*a
    struct any_may_repeat
    {
      typedef any_may_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return -*base;
      }
    };
    //a+? -> -+a
    struct any1_may_repeat
    {
      typedef any1_may_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return -+base;
      }
    };
    //a?? -> -!a
    struct may_might_repeat
    {
      typedef may_might_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return -!base;
      }
    };
    //a{n, m} -> repeat<n, m>(a)
    template <int n, int m>
    struct range_repeat
    {
      typedef range_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return boost::xpressive::repeat<n, m>(base);
      }
    };
    //a{n, m}? -> -repeat<n, m>(a)
    template <int n, int m>
    struct may_range_repeat
    {
      typedef may_range_repeat type;
      static boost::xpressive::sregex run(boost::xpressive::sregex base)
      {
        return -boost::xpressive::repeat<n, m>(base);
      }
    };

    template <char A, int N, char B, int M, char C, char D>
    struct eval_repetition_impl;
    
    template <> struct eval_repetition_impl<'x', -1, 'x', -1, 'x', 'x'> : no_repeat {};
    template <> struct eval_repetition_impl<'*', -1, 'x', -1, 'x', 'x'> : any_repeat {};
    template <> struct eval_repetition_impl<'*', -1, 'x', -1, 'x', '?'> : any_may_repeat {};
    template <> struct eval_repetition_impl<'+', -1, 'x', -1, 'x', 'x'> : any1_repeat {};
    template <> struct eval_repetition_impl<'+', -1, 'x', -1, 'x', '?'> : any1_may_repeat {};
    template <> struct eval_repetition_impl<'?', -1, 'x', -1, 'x', 'x'> : may_repeat {};
    template <> struct eval_repetition_impl<'?', -1, 'x', -1, 'x', '?'> : may_might_repeat {};
    template <int N, int M> struct eval_repetition_impl<'{', N, ',', M, '}', 'x'> : range_repeat<N, M> {};
    template <int N, int M> struct eval_repetition_impl<'{', N, ',', M, '}', '?'> : may_range_repeat<N, M> {};
 
    struct eval_repetition
    {
      template <class Seq>
      struct apply :
        eval_repetition_impl<
          at< Seq, int_<0> >::type::value,
          at< Seq, int_<1> >::type::value,
          at< Seq, int_<2> >::type::value,
          at< Seq, int_<3> >::type::value,
          at< Seq, int_<4> >::type::value,
          at< Seq, int_<5> >::type::value
        >
      {};
    };
    
    typedef metaparse::transform <
      metaparse::sequence<
        metaparse::one_of<
          metaparse::lit_c<'*'>,
          metaparse::lit_c<'+'>,
          metaparse::lit_c<'?'>,
          metaparse::lit_c<'{'>,
          metaparse::return_< char_<'x'> >
        >,
        metaparse::one_of<
          metaparse::digit_val,
          metaparse::return_< int_<-1> >
        >,
        metaparse::one_of<
          metaparse::lit_c<','>,
          metaparse::return_< char_<'x'> >
        >,
        metaparse::one_of<
          metaparse::digit_val,
          metaparse::return_< int_<-1> >
        >,
        metaparse::one_of<
          metaparse::lit_c<'}'>,
          metaparse::return_< char_<'x'> >
        >,
        metaparse::one_of<
          metaparse::lit_c<'?'>,
          metaparse::return_< char_<'x'> >
        >
      >,
      xlxpressive::eval_repetition
    >
    repetition;

    struct build_unary_item
    {
      template <class Seq>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run() {
          return back<Seq>::type::run(front<Seq>::type::run());
        }
      };
    };

    typedef metaparse::transform<
      metaparse::sequence<xlxpressive::item, xlxpressive::repetition>,
      xlxpressive::build_unary_item
    >
    unary_item;

    //=========================================================================

    boost::xpressive::sregex *seq_expr_ptr = 0;

    struct seq_builder
    {
      template<class E> void operator()(E) {
        assert(seq_expr_ptr != 0);
        if (seq_expr_ptr->regex_id() == 0) {
          *seq_expr_ptr = E::type::run();
        }
        else {
          boost::xpressive::sregex tmp = *seq_expr_ptr >> E::type::run();
          *seq_expr_ptr = tmp;
        }
      }
    };

    struct build_sequence
    {
      template <class Seq>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run() {
          seq_expr_ptr = new boost::xpressive::sregex;

          for_each<Seq>(seq_builder());          
          boost::xpressive::sregex seq_expr = *seq_expr_ptr;

          delete seq_expr_ptr;

          return seq_expr; 
        }
      };
    };

    typedef metaparse::transform<
      metaparse::any< xlxpressive::unary_item >,
      xlxpressive::build_sequence
    >
    seq;
    
    //=========================================================================

//    typedef metaparse::build_parser< metaparse::entire_input<reg_exp> > regexp_parser;
    typedef metaparse::build_parser< metaparse::entire_input<seq> > regexp_parser;
  }
}

#endif

