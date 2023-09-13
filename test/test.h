#ifndef ARONA_TEST_TEST_H_
#define ARONA_TEST_TEST_H_

#include<string>

void test_initialize();
void test_finalize();
bool test_case(const std::string& case_name, bool case_result);

#endif // ARONA_TEST_TEST_H_