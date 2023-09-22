#include"test/test.h"

extern void test_factory();
extern void test_timer();
extern void test_random();
extern void test_logger();

extern void test_string_helper();

extern void test_dataframe();

int main()
{
  test_initialize();

  test_timer();
  test_factory();
  test_random();
  test_logger();
  test_string_helper();
  test_dataframe();
  
  test_finalize();
}