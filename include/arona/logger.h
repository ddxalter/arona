#ifndef ARONA_LOGGER_H_
#define ARONA_LOGGER_H_

#include<string>
#include<fstream>
#include<iostream>

namespace arona {

class Logger
{
public:
  using OpenMode = unsigned long;
  static constexpr OpenMode Append = 1ul << 0;
  static constexpr OpenMode Trunc = 1ul << 1;
  static constexpr OpenMode UseCerr = 1ul << 2;
  Logger(const std::string& path, const OpenMode mode = Append)
    : ofs_(path, std::ios_base::out | ((Append & mode) ? std::ios_base::app : 0) | ((Trunc & mode) ? std::ios_base::trunc : 0))
    , use_cerr_(UseCerr & mode)
  {
    if(!ofs_.is_open())
    {
      throw std::runtime_error("arona::Logger: failed to open a log file '" + path + "'.");
    }
  }
  ~Logger()
  {
    if(ofs_.is_open())
    {
      ofs_.close();
    }
  }
  template<class T>
  inline Logger& operator<<(const T& x)
  {
    if(use_cerr_)
    {
      std::cerr << x;
    }
    ofs_ << x;
    return *this;
  }
  Logger& operator<<(std::ostream& (*io)(std::ostream&))
  {
    if(use_cerr_)
    {
      io(std::cerr);
    }
    io(ofs_);
    return *this;
  }
private:
  std::ofstream ofs_;
  bool use_cerr_;
};

} // namespace arona

#endif // ARONA_LOGGER_H_
