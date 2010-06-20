#ifndef MPLLIBS_TEST_TEST_RESULT_H
#define MPLLIBS_TEST_TEST_RESULT_H

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <iostream>

namespace mpllibs
{
  namespace test
  {
    class TestResult
    {
    public:
      TestResult(
        const std::string& name_,
        const std::string& filename_,
        int lineNumber_,
        bool success_
      ) :
        _name(name_),
        _filename(filename_),
        _lineNumber(lineNumber_),
        _success(success_)
      {}
      
      const std::string& name() const
      {
        return _name;
      }
      
      const std::string& filename() const
      {
        return _filename;
      }
      
      int lineNumber() const
      {
        return _lineNumber;
      }
      
      bool success() const
      {
        return _success;
      }
    private:
      std::string _name;
      std::string _filename;
      int _lineNumber;
      bool _success;
    };
    
    inline std::ostream& operator<<(std::ostream& out_, const TestResult& r_)
    {
      out_ << r_.name() << ": ";
      if (r_.success())
      {
        out_ << "OK";
      }
      else
      {
        out_ << "FAIL (" << r_.filename() << ":" << r_.lineNumber() << ")";
      }
      return out_ << std::endl;
    }
  }
}

#endif

