#include"test/test.h"

#include"arona/timer.h"

#include<iostream>

void test_timer()
{
  arona::Timer::start("good");
  auto good = arona::Timer::stop("good");
  auto bad = arona::Timer::stop("bad");
  
  test_case("arona::Timer", (good != -1) && (bad == -1));
}

