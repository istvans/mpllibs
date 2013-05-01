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
#include <mpllibs/metaparse/one_of.hpp>
#include <mpllibs/metaparse/sequence.hpp>
#include <mpllibs/metaparse/transform.hpp>
#include <mpllibs/metaparse/return.hpp>
#include <mpllibs/metaparse/any1.hpp>
#include <mpllibs/metaparse/any_one_of.hpp>
#include <mpllibs/metaparse/any_one_of1.hpp>
#include <mpllibs/metaparse/any.hpp>
#include <mpllibs/metaparse/digit_val.hpp>
#include <mpllibs/metaparse/int.hpp>
#include <mpllibs/metaparse/letter.hpp>
#include <mpllibs/metaparse/space.hpp>
#include <mpllibs/metaparse/middle_of.hpp>
#include <mpllibs/metaparse/one_char.hpp>
#include <mpllibs/metaparse/first_of.hpp>
#include <mpllibs/metaparse/last_of.hpp>
#include <mpllibs/metaparse/foldl.hpp>
#include <mpllibs/metaparse/foldlp.hpp>

#include <mpllibs/metaparse/util/int_to_digit.hpp>

#include <boost/xpressive/regex_primitives.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/char.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>

namespace mpllibs
{
  namespace xlxpressive
  {
    struct build_bos
    {
      typedef build_bos type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::bos;
      }
    };
    typedef metaparse::always< metaparse::lit_c<'^'>, xlxpressive::build_bos > bos;

    //=========================================================================

    struct build_eos
    {
      typedef build_eos type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::eos;
      }
    };
    typedef metaparse::always< metaparse::lit_c<'$'>, xlxpressive::build_eos > eos;
    
    //=========================================================================
    
    struct build_any
    {
      typedef build_any type;
      static boost::xpressive::sregex run()
      {
        return ~boost::xpressive::_n;
      }
    };
    typedef metaparse::always< metaparse::lit_c<'.'>, xlxpressive::build_any > any;
    
    //=========================================================================

    struct build_number
    {
      template <class N>
      struct apply
      {
        typedef apply type;

        static boost::xpressive::sregex run()
        {
          return boost::xpressive::as_xpr( metaparse::util::int_to_digit<N>::type::value );
        }

        static int int_value()
        {
          return metaparse::util::int_to_digit<N>::type::value;
        }

        static char char_value()
        {
          int n = int_value();
          switch (n) {
            case 0: return '0';
            case 1: return '1';
            case 2: return '2';
            case 3: return '3';
            case 4: return '4';
            case 5: return '5';
            case 6: return '6';
            case 7: return '7';
            case 8: return '8';
            case 9: return '9';
          }
        }

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout<< "  build_number-run(after)" << std::endl;
          return after;
        }
        
        template <class Before>
        struct add_set_item {
          typedef add_set_item type;

          template <class T>
          static boost::xpressive::sregex run(T after)
          {
            std::cout << "  build_number-add_set_item" << std::endl;
            return Before::type::run( char_value() | after );
          }
        };
      };
    };
    typedef metaparse::transform< metaparse::digit_val, xlxpressive::build_number > number;

    //=========================================================================

    struct build_letter
    {
      template <class ch>
      struct apply
      {
        typedef apply type;

        static boost::xpressive::sregex run()
        {
          std::cout<< "  build_letter-run: " << ch::value << std::endl;
          return boost::xpressive::as_xpr( ch::value );
        }

        static char char_value()
        {
          std::cout<< "  build_letter-char_value: " << ch::value << std::endl;
          return ch::value;
        }

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout<< "  build_letter-run(after)" << std::endl;
          return after;
        }
        
        template <class Before>
        struct add_set_item {
          typedef add_set_item type;

          template <class T>
          static boost::xpressive::sregex run(T after)
          {
            std::cout << "  build_letter-add_set_item: " << ch::value << std::endl;
            return Before::type::run( char_value() | after );
          }
        };
      };
    };
    typedef metaparse::transform< metaparse::letter, xlxpressive::build_letter > letter;

    //=========================================================================
    
    //\0 -> s0
    struct back_reference0
    {
      typedef back_reference0 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s0;
      }
    };
    //\1 -> s1
    struct back_reference1
    {
      typedef back_reference1 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s1;
      }
    };
    //\2 -> s2
    struct back_reference2
    {
      typedef back_reference2 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s2;
      }
    };
    //\3 -> s3
    struct back_reference3
    {
      typedef back_reference3 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s3;
      }
    };
    //\4 -> s4
    struct back_reference4
    {
      typedef back_reference4 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s4;
      }
    };
    //\5 -> s5
    struct back_reference5
    {
      typedef back_reference5 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s5;
      }
    };
    //\6 -> s6
    struct back_reference6
    {
      typedef back_reference6 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s6;
      }
    };
    //\7 -> s7
    struct back_reference7
    {
      typedef back_reference7 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s7;
      }
    };
    //\8 -> s8
    struct back_reference8
    {
      typedef back_reference8 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s8;
      }
    };
    //\9 -> s9
    struct back_reference9
    {
      typedef back_reference9 type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::s9;
      }
    };
    
    template <int N>
    struct eval_back_reference_impl;
    
    template <> struct eval_back_reference_impl<0> : back_reference0 {};
    template <> struct eval_back_reference_impl<1> : back_reference1 {};
    template <> struct eval_back_reference_impl<2> : back_reference2 {};
    template <> struct eval_back_reference_impl<3> : back_reference3 {};
    template <> struct eval_back_reference_impl<4> : back_reference4 {};
    template <> struct eval_back_reference_impl<5> : back_reference5 {};
    template <> struct eval_back_reference_impl<6> : back_reference6 {};
    template <> struct eval_back_reference_impl<7> : back_reference7 {};
    template <> struct eval_back_reference_impl<8> : back_reference8 {};
    template <> struct eval_back_reference_impl<9> : back_reference9 {};
 
    struct eval_back_reference
    {
      template <class N>
      struct apply :
        eval_back_reference_impl<
          N::type::value
        >
      {};
    };
    
    //\b  -> _b
    struct word_boundary
    {
      typedef word_boundary type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::_b;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  word_boundary-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  word_boundary-add_set_item" << std::endl;
          return Before::type::run( boost::xpressive::_b | after );
        }
      };
    };
    //\B  -> ~_b
    struct not_word_boundary
    {
      typedef not_word_boundary type;
      static boost::xpressive::sregex run()
      {
        return ~boost::xpressive::_b;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  not_word_boundary-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  not_word_boundary-add_set_item" << std::endl;
          return Before::type::run( ~boost::xpressive::_b | after );
        }
      };
    };
    //\d  -> _d
    struct digit_character
    {
      typedef digit_character type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::_d;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  digit_character-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  digit_character-add_set_item" << std::endl;
          return Before::type::run( boost::xpressive::_d | after );
        }
      };
    };
    //\D  -> ~_d
    struct not_digit_character
    {
      typedef not_digit_character type;
      static boost::xpressive::sregex run()
      {
        return ~boost::xpressive::_d;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  not_digit_character-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  not_digit_character-add_set_item" << std::endl;
          return Before::type::run( ~boost::xpressive::_d | after );
        }
      };
    };
    //\w  -> _w
    struct word_character
    {
      typedef word_character type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::_w;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  build_letter-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  word_character-add_set_item" << std::endl;
          return Before::type::run( boost::xpressive::_w | after );
        }
      };
    };
    //\W  -> ~_w
    struct not_word_character
    {
      typedef not_word_character type;
      static boost::xpressive::sregex run()
      {
        return ~boost::xpressive::_w;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  not_word_character-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  not_word_character-add_set_item" << std::endl;
          return Before::type::run( ~boost::xpressive::_w | after );
        }
      };
    };
    //\s  -> _s
    struct space_character
    {
      typedef space_character type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::_s;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  space_character-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  space_character-add_set_item" << std::endl;
          return Before::type::run( boost::xpressive::_s | after );
        }
      };
    };
    //\S  -> ~_s
    struct not_space_character
    {
      typedef not_space_character type;
      static boost::xpressive::sregex run()
      {
        return ~boost::xpressive::_s;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  not_space_character-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  not_space_character-add_set_item" << std::endl;
          return Before::type::run( ~boost::xpressive::_s | after );
        }
      };
    };
    //\r|\r\n -> _ln
    struct logical_newline
    {
      typedef logical_newline type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::_ln;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  logical_newline-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  logical_newline-add_set_item" << std::endl;
          return Before::type::run( boost::xpressive::_ln | after );
        }
      };
    };
    //\n -> _n
    struct literal_newline
    {
      typedef literal_newline type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::_n;
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  literal_newline-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  literal_newline-add_set_item" << std::endl;
          return Before::type::run( boost::xpressive::_n | after );
        }
      };
    };
    //\\ -> as_xpr('\\')
    struct backslash
    {
      typedef backslash type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::as_xpr('\\');
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  backslash-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  backslash-add_set_item" << std::endl;
          return Before::type::run( '\\' | after );
        }
      };
    };
    //\^ -> as_xpr('^')
    struct caret
    {
      typedef caret type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::as_xpr('^');
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  caret-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  caret-add_set_item" << std::endl;
          return Before::type::run( '^' | after );
        }
      };
    };
    //\$ -> as_xpr('$')
    struct dollar
    {
      typedef dollar type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::as_xpr('$');
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  dollar-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  dollar-add_set_item" << std::endl;
          return Before::type::run( '$' | after );
        }
      };
    };
    //\. -> as_xpr('.')
    struct full_stop
    {
      typedef full_stop type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::as_xpr('.');
      }

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout<< "  full_stop-run(after)" << std::endl;
        return after;
      }
        
      template <class Before>
      struct add_set_item {
        typedef add_set_item type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "  full_stop-add_set_item" << std::endl;
          return Before::type::run( '.' | after );
        }
      };
    };

    struct build_bschar
    {
      template <class Bschar>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run()
        {
          return Bschar::type::run();
        }

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout<< "  build_bschar-run(after)" << std::endl;
          return after;
        }
        
        template <class Before>
        struct add_set_item {
          typedef add_set_item type;
  
          template <class T>
          static boost::xpressive::sregex run(T after)
          {
            std::cout << "  build_bschar-add_set_item" << std::endl;
            return Bschar::template add_set_item<Before>::type::run(after);
          }
        };
      };
    };
    
    typedef metaparse::transform <
      metaparse::last_of<
        metaparse::lit_c<'\\'>,
        metaparse::one_of<
          metaparse::transform<
            metaparse::digit_val,
            xlxpressive::eval_back_reference
          >,
          metaparse::one_of<
            metaparse::always< metaparse::lit_c<'b'>, xlxpressive::word_boundary >,
            metaparse::always< metaparse::lit_c<'B'>, xlxpressive::not_word_boundary >
          >,
          metaparse::one_of<
            metaparse::always< metaparse::lit_c<'d'>, xlxpressive::digit_character >,
            metaparse::always< metaparse::lit_c<'D'>, xlxpressive::not_digit_character >
          >,
          metaparse::one_of<
            metaparse::always< metaparse::lit_c<'w'>, xlxpressive::word_character >,
            metaparse::always< metaparse::lit_c<'W'>, xlxpressive::not_word_character >
          >,
          metaparse::one_of<
            metaparse::always< metaparse::lit_c<'s'>, xlxpressive::space_character >,
            metaparse::always< metaparse::lit_c<'S'>, xlxpressive::not_space_character >
          >,
          metaparse::one_of<
            metaparse::always< metaparse::lit_c<'^'>, xlxpressive::caret >,
            metaparse::always< metaparse::lit_c<'$'>, xlxpressive::dollar >,
            metaparse::always< metaparse::lit_c<'.'>, xlxpressive::full_stop >
          >,
          metaparse::one_of<
            metaparse::always<
              metaparse::one_of<
                metaparse::lit_c<'r'>,
                metaparse::sequence<
                  metaparse::lit_c<'r'>,
                  metaparse::lit_c<'\\'>,
                  metaparse::lit_c<'n'>
                >
              >,
              xlxpressive::logical_newline
            >,
            metaparse::always< metaparse::lit_c<'n'>, xlxpressive::literal_newline >
          >,
          metaparse::return_< xlxpressive::backslash >
        >
      >,
      xlxpressive::build_bschar
    >
    bschar;
    
    //=========================================================================

    struct build_non_alphabet
    {
      template <class ch>
      struct apply
      {
        typedef apply type;

        static boost::xpressive::sregex run()
        {
          return boost::xpressive::as_xpr( ch::value );
        }
  
        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout<< "  build_non_alphabet-run(after)" << std::endl;
          return after;
        }
        
        template <class Before>
        struct add_set_item {
          typedef add_set_item type;
          
          template <class T>
          static boost::xpressive::sregex run(T after)
          {
            std::cout << "  build_non_alphabet-add_set_item: " << ch::value << std::endl;
            return Before::type::run( ch::value | after );
          }
        };
      };
    };

    typedef metaparse::transform<
      metaparse::one_of<
        metaparse::lit_c<' '>,
        metaparse::lit_c<','>,
        metaparse::lit_c<';'>,
        metaparse::lit_c<':'>,
        metaparse::lit_c<'='>,
        metaparse::lit_c<'~'>,
        metaparse::lit_c<'<'>,
        metaparse::lit_c<'>'>,
        metaparse::lit_c<'-'>,
        metaparse::lit_c<'_'>,
        metaparse::lit_c<'!'>,
        metaparse::lit_c<'@'>,
        metaparse::lit_c<'#'>,
        metaparse::lit_c<'%'>,
        metaparse::lit_c<'&'>
      >,
      xlxpressive::build_non_alphabet
    >
    non_alphabet;

    //=========================================================================

    typedef metaparse::one_of<
      xlxpressive::bschar,
      xlxpressive::number,
      xlxpressive::letter,
      xlxpressive::non_alphabet
    >
    set_item;
    
    //=========================================================================
    // Forward declaration of reg_exp
    struct reg_exp;
    //=========================================================================

    typedef metaparse::any1<
      metaparse::one_char
    >
    name;
    
    //(?:s) -> (s)
    struct no_back_ref
    {
      typedef no_back_ref type;
      static boost::xpressive::sregex run(boost::xpressive::sregex s)
      {
        std::cout << "  no_back_ref" << std::endl;
        return (s);
      }
    };
    //(?i:s) -> icase(s)
    struct icase
    {
      typedef icase type;
      static boost::xpressive::sregex run(boost::xpressive::sregex s)
      {
        std::cout << "  icase" << std::endl;
        return boost::xpressive::icase(s);
      }
    };
    //(?>s) -> keep(s)
    struct keep
    {
      typedef keep type;
      static boost::xpressive::sregex run(boost::xpressive::sregex s)
      {
        std::cout << "  keep" << std::endl;
        return boost::xpressive::keep(s);
      }
    };
    //(?=s) -> before(s)
    struct before
    {
      typedef before type;
      static boost::xpressive::sregex run(boost::xpressive::sregex s)
      {
        std::cout << "  before" << std::endl;
        return boost::xpressive::before(s);
      }
    };
    //(?!s) -> ~before(s)
    struct not_before
    {
      typedef not_before type;
      static boost::xpressive::sregex run(boost::xpressive::sregex s)
      {
        std::cout << "  not_before" << std::endl;
        return ~boost::xpressive::before(s);
      }
    };
    //(?<=s) -> after(s)
    struct after
    {
      typedef after type;
      static boost::xpressive::sregex run(const boost::xpressive::sregex s)
      {
        std::cout << "  after" << std::endl;
        return boost::xpressive::after(s);
      }
    };
    //(?<!s) -> ~after(s)
    struct not_after
    {
      typedef not_after type;
      static boost::xpressive::sregex run(boost::xpressive::sregex s)
      {
        std::cout << "  not_after" << std::endl;
        return ~boost::xpressive::after(s);
      }
    };
    
    struct build_qexp
    {
      template <class Seq>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run() {
          std::cout << "build_qexp - getting tmp" << std::endl;
          const boost::xpressive::sregex tmp = boost::mpl::at< Seq, boost::mpl::int_<2> >::type::run();
          std::cout << "build_qexp - got tmp" << std::endl;
          return boost::mpl::at< Seq, boost::mpl::int_<1> >::type::run( tmp );
        }
      };
    };
    
    typedef metaparse::transform<
      metaparse::sequence<
        metaparse::lit_c<'?'>,
        metaparse::one_of<
          metaparse::always< metaparse::lit_c<':'>, xlxpressive::no_back_ref >,
          metaparse::always<
            metaparse::sequence< metaparse::lit_c<'i'>, metaparse::lit_c<':'> >,
            xlxpressive::icase
          >,
          metaparse::always< metaparse::lit_c<'>'>, xlxpressive::keep >,
          metaparse::always< metaparse::lit_c<'='>, xlxpressive::before >,
          metaparse::always< metaparse::lit_c<'!'>, xlxpressive::not_before >,
          metaparse::always<
            metaparse::sequence< metaparse::lit_c<'<'>, metaparse::lit_c<'='> >,
            xlxpressive::after
          >,
          metaparse::always<
            metaparse::sequence< metaparse::lit_c<'<'>, metaparse::lit_c<'!'> >,
            xlxpressive::not_after
          >
          // TODO Add named capture support
        >,
        xlxpressive::reg_exp
      >,
      build_qexp
    >
    qexp;

    //------------------

    struct build_qexp_based_bracket_exp
    {
      template <class E>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run()
        {
          std::cout << "build_qexp_based_bracket_exp" << std::endl;
          return E::type::run();
        }
      };
    };

    int bracket_counter = 0;
    struct build_reg_exp_based_bracket_exp
    {
      template <class E>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run()
        {
          ++bracket_counter;
          std::cout<< "build_reg_exp_based_bracket_exp - capturing: " << bracket_counter <<std::endl;
          boost::xpressive::sregex a = E::type::run();
          boost::xpressive::sregex ret;
          std::cout<< "build_reg_exp_based_bracket_exp - before creation of " << bracket_counter <<std::endl;
          switch(bracket_counter) {
            case 1: ret = (boost::xpressive::s1= a); break;
            case 2: ret = (boost::xpressive::s2= a); break;
            case 3: ret = (boost::xpressive::s3= a); break;
            case 4: ret = (boost::xpressive::s4= a); break;
            case 5: ret = (boost::xpressive::s5= a); break;
            case 6: ret = (boost::xpressive::s6= a); break;
            case 7: ret = (boost::xpressive::s7= a); break;
            case 8: ret = (boost::xpressive::s8= a); break;
            case 9: ret = (boost::xpressive::s9= a); break;
          }
          std::cout<< "build_reg_exp_based_bracket_exp - returning " << bracket_counter << std::endl;
          return ret;
        }
      };
    };

    struct eval_bracket_exp
    {
      template <class E>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run()
        {
          std::cout<< "eval_bracket_exp" << std::endl;
          return E::type::run();
        }
      };
    };

    typedef metaparse::transform<
      metaparse::middle_of<
        metaparse::lit_c<'('>,
        metaparse::one_of<
          metaparse::transform< xlxpressive::qexp,    xlxpressive::build_qexp_based_bracket_exp >,
          metaparse::transform< xlxpressive::reg_exp, xlxpressive::build_reg_exp_based_bracket_exp >
        >,
        metaparse::lit_c<')'>
      >,
      xlxpressive::eval_bracket_exp
    >
    bracket_exp;

    //=========================================================================

    //[[:alnum:]] -> alnum
    struct alnum
    {
      typedef alnum type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::alnum;
      }
    };
    //[[:alpha:]] -> alpha
    struct alpha
    {
      typedef alpha type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::alpha;
      }
    };
    //[[:blank:]] -> blank
    struct blank
    {
      typedef blank type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::blank;
      }
    };
    //[[:cntrl:]] -> cntrl
    struct cntrl
    {
      typedef cntrl type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::cntrl;
      }
    };
    //[[:digit:]] -> digit
    struct digit
    {
      typedef digit type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::digit;
      }
    };
    //[[:graph:]] -> graph
    struct graph
    {
      typedef graph type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::graph;
      }
    };
    //[[:lower:]] -> lower
    struct lower
    {
      typedef lower type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::lower;
      }
    };
    //[[:print:]] -> print
    struct print
    {
      typedef print type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::print;
      }
    };
    //[[:punct:]] -> punct
    struct punct
    {
      typedef punct type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::punct;
      }
    };
    //[[:space:]] -> space
    struct space
    {
      typedef space type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::space;
      }
    };
    //[[:upper:]] -> upper
    struct upper
    {
      typedef upper type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::upper;
      }
    };
    //[[:xdigit:]] -> xdigit
    struct xdigit
    {
      typedef xdigit type;
      static boost::xpressive::sregex run()
      {
        return boost::xpressive::xdigit;
      }
    };

    struct eval_char_group
    {
      template <class Seq>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run()
        {
          return boost::mpl::at< Seq, boost::mpl::int_<2> >::type::run();
        }
      };
    };

    typedef metaparse::transform<
      metaparse::sequence<
        metaparse::lit_c<'['>,
        metaparse::lit_c<':'>,
        metaparse::one_of<
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'a'>,
              metaparse::lit_c<'l'>,
              metaparse::lit_c<'n'>,
              metaparse::lit_c<'u'>,
              metaparse::lit_c<'m'>
            >,
            xlxpressive::alnum
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'a'>,
              metaparse::lit_c<'l'>,
              metaparse::lit_c<'p'>,
              metaparse::lit_c<'h'>,
              metaparse::lit_c<'a'>
            >,
            xlxpressive::alpha
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'b'>,
              metaparse::lit_c<'l'>,
              metaparse::lit_c<'a'>,
              metaparse::lit_c<'n'>,
              metaparse::lit_c<'k'>
            >,
            xlxpressive::blank
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'c'>,
              metaparse::lit_c<'n'>,
              metaparse::lit_c<'t'>,
              metaparse::lit_c<'r'>,
              metaparse::lit_c<'l'>
            >,
            xlxpressive::cntrl
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'d'>,
              metaparse::lit_c<'i'>,
              metaparse::lit_c<'g'>,
              metaparse::lit_c<'i'>,
              metaparse::lit_c<'t'>
            >,
            xlxpressive::digit
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'g'>,
              metaparse::lit_c<'r'>,
              metaparse::lit_c<'a'>,
              metaparse::lit_c<'p'>,
              metaparse::lit_c<'h'>
            >,
            xlxpressive::graph
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'l'>,
              metaparse::lit_c<'o'>,
              metaparse::lit_c<'w'>,
              metaparse::lit_c<'e'>,
              metaparse::lit_c<'r'>
            >,
            xlxpressive::lower
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'p'>,
              metaparse::lit_c<'r'>,
              metaparse::lit_c<'i'>,
              metaparse::lit_c<'n'>,
              metaparse::lit_c<'t'>
            >,
            xlxpressive::print
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'p'>,
              metaparse::lit_c<'u'>,
              metaparse::lit_c<'n'>,
              metaparse::lit_c<'c'>,
              metaparse::lit_c<'t'>
            >,
            xlxpressive::punct
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'s'>,
              metaparse::lit_c<'p'>,
              metaparse::lit_c<'a'>,
              metaparse::lit_c<'c'>,
              metaparse::lit_c<'e'>
            >,
            xlxpressive::space
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'u'>,
              metaparse::lit_c<'p'>,
              metaparse::lit_c<'p'>,
              metaparse::lit_c<'e'>,
              metaparse::lit_c<'r'>
            >,
            xlxpressive::upper
          >,
          metaparse::always<
            metaparse::sequence<
              metaparse::lit_c<'x'>,
              metaparse::lit_c<'d'>,
              metaparse::lit_c<'i'>,
              metaparse::lit_c<'g'>,
              metaparse::lit_c<'i'>,
              metaparse::lit_c<'t'>
            >,
            xlxpressive::xdigit
          >
        >,
        metaparse::lit_c<':'>,
        metaparse::lit_c<']'>,
        metaparse::lit_c<']'>
      >,
      xlxpressive::eval_char_group
    >
    char_group;

    //------------------

    struct build_range
    {
      template <class Seq>
      struct apply
      {
        typedef apply type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout<< "  build_range-run(after)" << std::endl;
          return after;
        }
        
        template <class Before>
        struct add_set_item {
          typedef add_set_item type;

          template <class T>
          static boost::xpressive::sregex run(T after)
          {
            using boost::xpressive::range;
            using boost::mpl::at;
            using boost::mpl::int_;

            std::cout << "  build_range-add_set_item" << std::endl;
            return Before::type::run( range( at< Seq, int_<0> >::type::char_value(), at< Seq, int_<2> >::type::char_value() ) | after );
          }
        };
      };
    };

    typedef metaparse::transform<
      metaparse::one_of<
        metaparse::sequence< xlxpressive::number, metaparse::lit_c<'-'>, xlxpressive::number>,
        metaparse::sequence< xlxpressive::letter, metaparse::lit_c<'-'>, xlxpressive::letter>
      >,
      xlxpressive::build_range
    >
    range_exp;
    
    //------------------

    struct empty_set
    {
      typedef empty_set type;

      template <class T>
      static boost::xpressive::sregex run(T after)
      {
        std::cout << "empty_set run" << std::endl;
        return boost::xpressive::set[ after ];
      }
    };

    struct set_builder
    {
      template <class Next, class State>
      struct apply
      {
        typedef apply type;

        template <class T>
        static boost::xpressive::sregex run(T after)
        {
          std::cout << "set_builder run" << std::endl;
          return Next::template add_set_item< State >::type::run(after);
        }
      };
    };

    struct start_building_set
    {
      template <class RealSetBuilder>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run()
        {
          std::cout << "start_building_set run" << std::endl;
          return RealSetBuilder::type::run(boost::xpressive::range('4', '2'));
        }
      };
    };

    struct build_set
    {
      template <class Set>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run()
        {
          return Set::type::run();
        }
      };
    };

    typedef metaparse::transform<
      metaparse::first_of<
        metaparse::transform<
          metaparse::foldl1<
            metaparse::one_of< xlxpressive::range_exp, xlxpressive::set_item >,
            xlxpressive::empty_set,
            xlxpressive::set_builder
          >,
          xlxpressive::start_building_set
        >,
        metaparse::lit_c<']'>
      >,
      xlxpressive::build_set
    >
    set;
    
    //[...] -> set[...]
    template <class S>
    struct positive_set
    {
      typedef positive_set type;
      static boost::xpressive::sregex run()
      {
        return S::type::run();
      }
    };
    //[^...] -> ~set[...]
    template <class S>
    struct negative_set
    {
      typedef negative_set type;
      static boost::xpressive::sregex run()
      {
        return ~S::type::run();
      }
    };

    template <char A, class Set>
    struct eval_set_impl;
    
    template <class Set> struct eval_set_impl<'x', Set> : positive_set<Set> {};
    template <class Set> struct eval_set_impl<'^', Set> : negative_set<Set> {};
 
    struct eval_set
    {
      template <class Seq>
      struct apply :
        eval_set_impl<
          boost::mpl::front<Seq>::type::value,
          boost::mpl::back<Seq>
        >
      {};
    };
    
    //------------------
    
    struct build_group
    {
      template <class G>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run()
        {
          return G::type::run();
        }
      };
    };

    typedef metaparse::transform<
      metaparse::last_of<
        metaparse::lit_c<'['>,
        metaparse::one_of<
          xlxpressive::char_group,
          metaparse::transform<
            metaparse::sequence<
              metaparse::one_of<
                metaparse::lit_c<'^'>,
                metaparse::return_< boost::mpl::char_<'x'> >
              >,
              xlxpressive::set
            >,
            xlxpressive::eval_set
          >
        >
      >,
      xlxpressive::build_group
    >
    group;
    
    //=========================================================================

    typedef metaparse::one_of<
      xlxpressive::set_item,
      xlxpressive::bos,
      xlxpressive::eos,
      xlxpressive::any,
      xlxpressive::bracket_exp,
      xlxpressive::group
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
          boost::mpl::at< Seq, boost::mpl::int_<0> >::type::value,
          boost::mpl::at< Seq, boost::mpl::int_<1> >::type::value,
          boost::mpl::at< Seq, boost::mpl::int_<2> >::type::value,
          boost::mpl::at< Seq, boost::mpl::int_<3> >::type::value,
          boost::mpl::at< Seq, boost::mpl::int_<4> >::type::value,
          boost::mpl::at< Seq, boost::mpl::int_<5> >::type::value
        >
      {};
    };
    
    typedef metaparse::transform <
      metaparse::one_of<
        metaparse::sequence<
          metaparse::one_of<
            metaparse::lit_c<'*'>,
            metaparse::lit_c<'+'>,
            metaparse::lit_c<'?'>,
            metaparse::lit_c<'{'>
          >,
          metaparse::one_of<
            metaparse::digit_val,
            metaparse::return_< boost::mpl::int_<-1> >
          >,
          metaparse::one_of<
            metaparse::lit_c<','>,
            metaparse::return_< boost::mpl::char_<'x'> >
          >,
          metaparse::one_of<
            metaparse::digit_val,
            metaparse::return_< boost::mpl::int_<-1> >
          >,
          metaparse::one_of<
            metaparse::lit_c<'}'>,
            metaparse::return_< boost::mpl::char_<'x'> >
          >,
          metaparse::one_of<
            metaparse::lit_c<'?'>,
            metaparse::return_< boost::mpl::char_<'x'> >
          >
        >,
        metaparse::return_<
          boost::mpl::vector<
            boost::mpl::char_<'x'>,
            boost::mpl::int_<-1>,
            boost::mpl::char_<'x'>,
            boost::mpl::int_<-1>,
            boost::mpl::char_<'x'>,
            boost::mpl::char_<'x'>
          >
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
          std::cout << "build_unary_item" << std::endl;
          return boost::mpl::back<Seq>::type::run(boost::mpl::front<Seq>::type::run());
        }
      };
    };

    typedef metaparse::transform<
      metaparse::sequence<xlxpressive::item::type, xlxpressive::repetition>,
      xlxpressive::build_unary_item
    >
    unary_item;

    //=========================================================================

    boost::shared_ptr<boost::xpressive::sregex> seq_expr_ptr;

    struct seq_builder
    {
      template<class E> void operator()(E)
      {
        BOOST_ASSERT(seq_expr_ptr != 0);
        std::cout << "seq_builder - regex_id: " << seq_expr_ptr->regex_id()<< " use_count: " << seq_expr_ptr.use_count() << std::endl;
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
          std::cout << "build_sequence - before new" << std::endl;
          seq_expr_ptr.reset(new boost::xpressive::sregex);
          std::cout << "build_sequence - after new" << std::endl;

          boost::mpl::for_each<Seq>(seq_builder());
          std::cout << "build_sequence - after seq_builder" << std::endl;
          return *seq_expr_ptr; 
        }
      };
    };

    typedef metaparse::transform<
      metaparse::any< xlxpressive::unary_item >,
      xlxpressive::build_sequence
    >
    seq;
    
    //=========================================================================

    boost::xpressive::sregex alternation;

    struct reg_exp_builder
    {
      template<class Seq> void operator()(Seq)
      {
        boost::xpressive::sregex tmp = alternation | Seq::type::run();
        alternation = tmp;
      }
    };

    struct build_regular_expression
    {
      template <class Seq>
      struct apply
      {
        typedef apply type;
        static boost::xpressive::sregex run() {
          std::cout << "build_regular_expression - init alternation" << std::endl;
          alternation = boost::mpl::front<Seq>::type::run();
          std::cout << "build_regular_expression - for_each reg_exp_builder" << std::endl;
          boost::mpl::for_each< typename boost::mpl::back<Seq>::type >(reg_exp_builder());
          std::cout << "build_regular_expression - returning alternation" << std::endl;

          return alternation;
        }
      };
    };

    struct reg_exp : metaparse::transform<
      metaparse::sequence<
        xlxpressive::seq,
        metaparse::any_one_of<
          metaparse::last_of<
            metaparse::lit_c<'|'>,
            xlxpressive::seq
          >
        >
      >,
      xlxpressive::build_regular_expression
    >
    {};
    
    //=========================================================================

    typedef metaparse::build_parser< metaparse::entire_input<reg_exp> > regexp_parser;
  }
}

#endif

