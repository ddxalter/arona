#include"test/test.h"
#include"arona/logger.h"

#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

bool test_append()
{
  // First Logger instance
  {
    arona::Logger logger("test_append.log", arona::Logger::Append);
    logger << "test1\n";
  }

  // Second Logger instance
  {
    arona::Logger logger("test_append.log", arona::Logger::Append);
    logger << "test2\n";
  }

  std::ifstream ifs("test_append.log");
  if (!ifs.is_open()) {
    std::cerr << "Fatal: 'test_append' could not open the log file for reading." << std::endl;
    return false;
  }

  std::string line1, line2;
  std::getline(ifs, line1);
  std::getline(ifs, line2);
  
  // Close the file and remove it
  ifs.close();
  if (std::remove("test_append.log") != 0)
  {
    std::cerr << "Fatal: 'test_append' could not remove the log file." << std::endl;
    return false;
  }

  return line1 == "test1" && line2 == "test2";
}

bool test_dir_not_exist()
{
  try
  {
    // this must throw exception
    arona::Logger logger("dir_not_exist/test.log");
  }
  catch (std::exception& e)
  {
    // exception was thrown correctly
    return true;
  }
  // exception was not thrown for the invalid argument
  return false;
}



void test_logger()
{
  test_case("arona::Logger(\"test_append.log\", arona::Logger::Append)", test_append());
  test_case("arona::Logger(\"dir_not_exist/test.log\")", test_dir_not_exist());
}