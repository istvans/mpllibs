#ifndef MPLLIBS_METAMONAD_MULTI_LET_HPP
#define MPLLIBS_METAMONAD_MULTI_LET_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metamonad/let.hpp>
#include <mpllibs/metamonad/metafunction.hpp>
#include <mpllibs/metamonad/lambda.hpp>
#include <mpllibs/metamonad/name.hpp>
#include <mpllibs/metamonad/lazy.hpp>
#include <mpllibs/metamonad/already_lazy.hpp>

#include <boost/mpl/pair.hpp>
#include <boost/mpl/fold.hpp>

namespace mpllibs
{
  namespace metamonad
  {
    MPLLIBS_METAFUNCTION(multi_let, (M)(E))
    ((
      boost::mpl::fold<
        M,
        E,
        lambda<s, p,
          lazy<
            let<
              boost::mpl::first<already_lazy<p> >,
              boost::mpl::second<already_lazy<p> >,
              already_lazy<s>
            >
          >
        >
      >
    ));
  }
}

#endif

