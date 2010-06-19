#ifndef MPLLIBS_PARSER_SEQUENCE_H
#define MPLLIBS_PARSER_SEQUENCE_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/parser/nothing.h>

#include <mpllibs/util/pair.h>
#include <mpllibs/util/make_pair.h>
#include <mpllibs/util/lazy_equal_to.h>
#include <mpllibs/util/compose.h>

#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/quote.hpp>

namespace mpllibs
{
  namespace parser
  {
    template <class p1, class p2>
    struct sequence
    {
      template <class S>
      struct apply :
        boost::mpl::eval_if<
          mpllibs::util::lazy_equal_to<
            boost::mpl::apply<p1, S>,
            mpllibs::parser::nothing
          >,
          mpllibs::parser::nothing,
          boost::mpl::eval_if<
            mpllibs::util::lazy_equal_to<
              boost::mpl::apply<
                mpllibs::util::compose<
                  p2,
                  boost::mpl::quote1<boost::mpl::second>,
                  p1
                >,
                S
              >,
              mpllibs::parser::nothing
            >,
            mpllibs::parser::nothing,
            mpllibs::util::make_pair<
              mpllibs::util::make_pair<
                boost::mpl::apply<
                  mpllibs::util::compose<
                    boost::mpl::quote1<boost::mpl::first>,
                    p1
                  >,
                  S
                >,
                boost::mpl::apply<
                  mpllibs::util::compose<
                    boost::mpl::quote1<boost::mpl::first>,
                    p2,
                    boost::mpl::quote1<boost::mpl::second>,
                    p1
                  >,
                  S
                >
              >,
              boost::mpl::apply<
                mpllibs::util::compose<
                  boost::mpl::quote1<boost::mpl::second>,
                  p2,
                  boost::mpl::quote1<boost::mpl::second>,
                  p1
                >,
                S
              >
            >
          >
        >
      {};
    };
  }
}

#endif

