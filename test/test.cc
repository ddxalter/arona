#include"test/test.h"

#include<iostream>
#include<cstddef>

static std::size_t count_success = 0;
static std::size_t count_fail = 0;
static std::size_t count_total = 0;

static const std::string set_color_red = "\033[31m";
static const std::string set_color_green = "\033[32m";
static const std::string unset_color = "\033[m";

static const std::string msg_success = set_color_green + "SUCCESS" + unset_color;
static const std::string msg_fail = set_color_red + "FAIL   " + unset_color;

static const std::string msg_yes = set_color_green + "YES" + unset_color;
static const std::string msg_no = set_color_red + "NO" + unset_color;

void test_initialize()
{
  // currently there is nothing to do
}

void test_finalize()
{
  std::cerr << "Done " << count_total << " test cases." << std::endl
            << "Success : " << count_success << "/" << count_total << std::endl
            << "Fail    : " << count_fail << "/"<< count_total << std::endl;

  std::cerr << "[All Passed] ? " << (count_fail == 0 ? msg_yes : msg_no) << std::endl;
}

bool test_case(const std::string& case_name, bool case_result)
{
  std::cerr << "[test] " << (case_result ? msg_success : msg_fail) << " @ " << case_name << std::endl;

  count_total = count_total + 1;
  count_success = count_success + (case_result ? 1 : 0);
  count_fail = count_fail + (case_result ? 0 : 1);
  return case_result;
}