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
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = std::chrono::time_point<Clock>;
  using Records = std::unordered_map<std::string, Clock::time_point>;
public:
  static void start(const std::string& timer_label = "")
  {
    records_[timer_label] = Clock::now();
  }
  static int stop(const std::string& timer_label = "")
  {
    auto elapsed = (Clock::now() - records_[timer_label]);
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  }
  static void clear()
  {
    records.clear();
  }
  static std::time_t now()
  {
    return std::time(nullptr);
  }
  static std::time_t launched()
  {
    return launched_time_;
  }
  static std::string as_string(const std::time_t& t = now(),
                               const std::string& ym = "-",
                               const std::string& md = "-",
                               const std::string& dh = "_",
                               const std::string& hm = "-",
                               const std::string& ms = "-")
  {
    std::tm* lt = std::localtime(&t);
    std::stringstream ss;
    ss << lt->tm_year + 1900
       << ym << std::setw(2) << std::setfill('0') << lt->tm_mon + 1
       << md << std::setw(2) << std::setfill('0') << lt->tm_mday
       << dh << std::setw(2) << std::setfill('0') << lt->tm_hour
       << hm << std::setw(2) << std::setfill('0') << lt->tm_min
       << ms << std::setw(2) << std::setfill('0') << lt->tm_sec;
    return ss.str();
  }
private:
  static const std::time_t launched_time_;
  static Records records_;
};
const std::time_t launched_time_ = Timer::now();
Timer::Records Timer::records_;

} // namespace arona

#endif // ARONA_ARONA_H_
