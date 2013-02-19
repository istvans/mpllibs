#ifndef MPLLIBS_METAMONAD_MULTI_LET_C_HPP
#define MPLLIBS_METAMONAD_MULTI_LET_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metamonad/multi_let.hpp>
#include <mpllibs/metamonad/metafunction.hpp>

namespace mpllibs
{
  namespace metamonad
  {
    MPLLIBS_METAFUNCTION(multi_let_c, (M)(E)) ((multi_let<M, syntax<E> >));
  }
}

#endif

