# Copyright Istvan Siroki (stevesiroki@gmail.com)  2012.-2013.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

aux_source_directory(. SOURCES)
add_executable(xlxpressive_test ${SOURCES})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(xlxpressive_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
else()
  target_link_libraries(xlxpressive_test boost_unit_test_framework)
endif()

add_test(xlxpressive_unit_tests xlxpressive_test)

