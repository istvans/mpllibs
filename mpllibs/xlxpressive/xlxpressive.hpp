#ifndef MPLLIBS_XLXPRESSIVE_XLXPRESSIVE_H
#define MPLLIBS_XLXPRESSIVE_XLXPRESSIVE_H

// Copyright Istvan Siroki (stevesiroki@gmail.com) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/xlxpressive/regexp_grammar.hpp>
#include <mpllibs/metaparse/string.hpp>

#define MPLLIBS_REGEX(s) (boost::mpl::apply_wrap1<mpllibs::xlxpressive::regexp_parser, MPLLIBS_STRING(s)>::type::run())

#endif // MPLLIBS_XLXPRESSIVE_XLXPRESSIVE_H

