#include"test/test.h"
#include"arona/dataframe.h"
#include"arona/tuple_helper.h"
#include<iostream>

void test_dataframe()
{
  {
    arona::DataFrame<int, float, double> df;
    df.push({1, 2, 3.14});
    df.push({4, 5, 6.28});
    std::stringstream ss;
    std::get<1>(df[0]) = 1.23;
    arona::tuple_to_stream(df[0], ss);
    test_case("arona::DataFrame::operator[]", ss.str()=="1 1.23 3.14");
  }

  {
    arona::DataFrame<int, float> df1;
    arona::DataFrame<int, float> df2;
    arona::DataFrame<double> df3;
    df1.push({1, 2.3});
    df2.push({4, 5.6});
    df3.push({3.14});
    df3.push({6.28});
    auto df12 = arona::concat(df1, df2);
    auto df123 = arona::merge(df12, df3);
    auto df4 = arona::extract<0,2>(df123);

    std::stringstream ss1;
    std::stringstream ss2;
    arona::tuple_to_stream(df12[0], ss1);
    arona::tuple_to_stream(df12[1], ss2);
    test_case("arona::DataFrame concat", ss1.str()=="1 2.3" && ss2.str()=="4 5.6");

    ss1.str("");
    ss2.str("");
    arona::tuple_to_stream(df123[0], ss1);
    arona::tuple_to_stream(df123[1], ss2);

    test_case("arona::DataFrame merge", ss1.str()=="1 2.3 3.14" && ss2.str()=="4 5.6 6.28");
    
    ss1.str("");
    ss2.str("");
    arona::tuple_to_stream(df4[0], ss1);
    arona::tuple_to_stream(df4[1], ss2);

    test_case("arona::DataFrame extract", ss1.str()=="1 3.14" && ss2.str()=="4 6.28");
  }

  {
    std::stringstream csv{"1,1.1\n2,2.1"};
    arona::DataFrame<int, float> df;
    df.read_csv(csv, ',');

    std::stringstream ss1;
    std::stringstream ss2;
    arona::tuple_to_stream(df[0], ss1);
    arona::tuple_to_stream(df[1], ss2);

    test_case("arona::DataFrame::read_csv", ss1.str()=="1 1.1" && ss2.str()=="2 2.1");
    
    csv.str("");
    csv.clear();
    df.dump_csv(csv, ' ');
    csv.seekg(0);

    test_case("arona::DataFrame::dump_csv", csv.str()=="1 1.1\n2 2.1\n");


  }

}