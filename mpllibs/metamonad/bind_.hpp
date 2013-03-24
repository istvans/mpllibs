#ifndef MPLLIBS_METAMONAD_BIND__HPP
#define MPLLIBS_METAMONAD_BIND__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metamonad/monad.hpp>
#include <mpllibs/metamonad/metafunction.hpp>

#include <boost/mpl/apply_wrap.hpp>

namespace mpllibs
{
  namespace metamonad
  {
    MPLLIBS_METAFUNCTION(bind_, (MonadTag)(A)(B))
    ((boost::mpl::apply_wrap2<typename monad<MonadTag>::bind_, A, B>));
  }
}

#endif

