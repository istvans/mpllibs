#!/usr/bin/perl
# Copyright Istvan Siroki (stevesiroki@gmail.com) 2013.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
use strict;
use warnings;

use JSON;
use Data::Dumper;

my $filename = "test.json";
open (my $TEST_FILE, "<$filename") or die "Cannot open $filename ($!)";
local $/;
my $raw_test_cases = <$TEST_FILE>;
close ($TEST_FILE);

my $test_cases = from_json($raw_test_cases);
#print Dumper($test_cases);

print "// Copyright Istvan Siroki (stevesiroki\@gmail.com) 2013.\n";
print "// Distributed under the Boost Software License, Version 1.0.\n";
print "//    (See accompanying file LICENSE_1_0.txt or copy at\n";
print "//          http://www.boost.org/LICENSE_1_0.txt)\n";
print "\n";
print "#define BOOST_TEST_DYN_LINK\n";
print "\n";
print "#include <mpllibs/xlxpressive/regexp_grammar.hpp>\n";
print "\n";
print "#include <mpllibs/metatest/boost_test.hpp>\n";
print "#include <boost/test/unit_test.hpp>\n";
print "\n";
print "#include <boost/mpl/string.hpp>\n";
print "\n";
print "#include <string>\n";
print "\n";
print "#include \"search.hpp\"\n";
print "\n";
print "BOOST_AUTO_TEST_CASE(test_grammar)\n";
print "{\n";
print "  using boost::mpl::string;\n";
print "\n";

my $CHAR_LIMIT = 4;
for (my $k = 0; $k < scalar(@$test_cases); ++$k) {
  my ($regexp, $test_str, $expect) = @{$test_cases->[$k]};
  my $not = "";

  my $perl_match = 0;
  if (!$expect) {
    $not = "!";
    $perl_match = 1 if ("$test_str" !~ /$regexp/);
  }
  else {
    $perl_match = 1 if ("$test_str" =~ /$regexp/);
  }
  print  "  BOOST_REQUIRE(" . (($perl_match) ? "true" : "false") . "); //perl test\n";

  my @re_chars = split(//, $regexp);
  $regexp = "'";
  for (my $k = 0; $k < scalar(@re_chars); ++$k) {
    $regexp .= $re_chars[$k];
    if (($k+1) % $CHAR_LIMIT == 0) {
      if ($k == (scalar(@re_chars)-1)) {
        $regexp .= "'";
      }
      else {
        $regexp .= "','";
      }
    }
  }
  $regexp .= "'" if (substr($regexp, length($regexp)-1, 1) ne "'");

  printf "  typedef string< %s > pattern%i;\n", $regexp, $k;
  printf "  BOOST_REQUIRE(%s search< pattern%i >(\"%s\") );\n", $not, $k, $test_str;
  print "\n";
}

print "}\n";
print "// Generated on " . localtime() . " (CET)\n";

