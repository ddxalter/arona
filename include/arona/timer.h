#ifndef ARONA_TIMER_H_
#define ARONA_TIMER_H_

#include<ctime>

#include<chrono>
#include<string>
#include<iomanip>
#include<sstream>
#include<unordered_map>

namespace arona {

class Timer
{
protected:
  using Clock = std::chrono::system_clock;
  using TimePoint = std::chrono::time_point<Clock>;
  using Records = std::unordered_map<std::string, TimePoint>;
public:
  struct TimeFormat
  {
    const std::string ym;
    const std::string md;
    const std::string dh;
    const std::string hm;
    const std::string ms;
  };
  static bool init()
  {
    initialize_time();
    return true;
  }
  static TimePoint initialize_time()
  {
    static TimePoint initialized_time_ = Clock::now();
    return initialized_time_;
  }
  static void start(const std::string& timer_label = "")
  {
    records()[timer_label] = Clock::now();
  }
  static int stop(const std::string& timer_label = "")
  {
    auto itr = records().find(timer_label);
    if(itr == records().end()) return -1;
    auto elapsed = (Clock::now() - itr->second);
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  }
  static void clear()
  {
    records().clear();
  }
  static TimePoint now()
  {
    return Clock::now();
  }
  static std::string to_string(const TimePoint t = now(),
                               const TimeFormat fmt = {"-","-","_","-","-"})
  {
    std::time_t tt = Clock::to_time_t(t);
    std::tm* lt = std::localtime(&tt);
    std::stringstream ss;
    ss << lt->tm_year + 1900
       << fmt.ym << std::setw(2) << std::setfill('0') << lt->tm_mon + 1
       << fmt.md << std::setw(2) << std::setfill('0') << lt->tm_mday
       << fmt.dh << std::setw(2) << std::setfill('0') << lt->tm_hour
       << fmt.hm << std::setw(2) << std::setfill('0') << lt->tm_min
       << fmt.ms << std::setw(2) << std::setfill('0') << lt->tm_sec;
    return ss.str();
  }
private:
  static Records& records() { static Records records_; return records_; }
};

} // namespace arona

#endif // ARONA_TIMER_H_
