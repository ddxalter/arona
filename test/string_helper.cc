#include"test/test.h"

#include"arona/string_helper.h"

bool test_split(std::string input, std::string sep, std::vector<std::string> expected)
{
  auto split_result = arona::split(input, sep);
  if(split_result.size() != expected.size()) return false;
  for(std::size_t i = 0; i < expected.size(); ++i)
  {
    if(split_result[i] != expected[i]) return false;
  }
  return true;
}

bool test_split_skipping(std::string input, std::string sep, std::vector<std::string> expected)
{
  auto split_result = arona::split_skipping(input, sep);
  if(split_result.size() != expected.size()) return false;
  for(std::size_t i = 0; i < expected.size(); ++i)
  {
    if(split_result[i] != expected[i]) return false;
  }
  return true;
}

void test_string_helper()
{
  // tests for single-char separator cases
  test_case("arona::split normal case", test_split("aaa,bbb", ",", {"aaa", "bbb"}));
  test_case("arona::split empty string", test_split("", ",", {""}));
  test_case("arona::split only separator", test_split(",", ",", {"", ""}));
  test_case("arona::split leading separator", test_split(",aaa", ",", {"", "aaa"}));
  test_case("arona::split trailing separator", test_split("aaa,", ",", {"aaa", ""}));
  test_case("arona::split multiple separators", test_split("aaa,,bbb", ",", {"aaa", "", "bbb"}));
  // test for multi-char separator cases
  test_case("arona::split multi-char separator", test_split("aaa--bbb", "--", {"aaa", "bbb"}));
  test_case("arona::split multi-char leading separator", test_split("--aaa", "--", {"", "aaa"}));
  test_case("arona::split multi-char trailing separator", test_split("aaa--", "--", {"aaa", ""}));
  test_case("arona::split multi-char multiple separators", test_split("aaa----bbb", "--", {"aaa", "", "bbb"}));
  // for split_skipping
  test_case("arona::split_skipping normal case", test_split_skipping(" aaa ,  bbb ", " ,", {"aaa", "bbb"}));
  test_case("arona::split_skipping empty string", test_split_skipping("", " ,", {}));
  test_case("arona::split_skipping only separator", test_split_skipping(" , , , ", " ,", {}));
  test_case("arona::split_skipping with empty elements", test_split_skipping(" , aaa , , , bbb , ", " ,", {"aaa", "bbb"}));
  test_case("arona::split_skipping multi separators", test_split_skipping(" aaa ,:;  bbb ,:; ", " ,:;", {"aaa", "bbb"}));
}