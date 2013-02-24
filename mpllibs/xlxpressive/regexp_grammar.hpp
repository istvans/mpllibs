#ifndef MPLLIBS_XLXPRESSIVE_REGEXP_GRAMMAR_HPP
#define MPLLIBS_XLXPRESSIVE_REGEXP_GRAMMAR_HPP

// Copyright Istvan Siroki (stevesiroki@gmail.com)  2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/lit_c.hpp>
#include <mpllibs/metaparse/build_parser.hpp>
#include <mpllibs/metaparse/entire_input.hpp>
#include <mpllibs/metaparse/always.hpp>

#include <boost/xpressive/regex_primitives.hpp>
#include <boost/xpressive/xpressive.hpp>

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
    
    struct build_eos
    {
      typedef build_eos type;
      static boost::xpressive::sregex run() {
        return boost::xpressive::eos;
      }
    };
    typedef metaparse::always< metaparse::lit_c<'$'>, build_eos > eos; 
    

//    typedef metaparse::build_parser<metaparse::entire_input<eos> > regexp_parser;
    typedef metaparse::build_parser<metaparse::entire_input<bos> > regexp_parser;
  }
}

#endif

