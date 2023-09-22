#include"test/test.h"

#include"arona/factory.h"

#include<iostream>
#include<vector>

struct Base
{
  virtual ~Base() = default;
  virtual std::vector<std::string> func() = 0;
};
using Factory = arona::Factory<Base, std::vector<std::string>>;

struct Derived : Base
{
  Derived(std::vector<std::string> strs) : strs(strs) {}
  std::vector<std::string> func() { return strs; }
  std::vector<std::string> strs;
};
Factory::Register<Derived> reg_derived("derived");

void test_factory()
{
  auto ans = std::vector<std::string>{"test", "arona", "factory"};
  auto obj = Factory::create("derived", {"test", "arona", "factory"});
  auto result =  obj->func();
  bool flag = true;
  for(std::size_t i = 0; i < ans.size();++i)
  {
    flag = flag && (ans[i] == result[i]);
  }
  delete obj;
  test_case("arona::Factory", flag);
}