#ifndef ARONA_LOGGER_H_
#define ARONA_LOGGER_H_

#include<string>
#include<fstream>
#include<iostream>

namespace arona {

class Logger
{
public:
  Logger(const std::string path, const bool append, const bool use_cerr)
    : ofs(path, openmode(append))
    , use_cerr(use_cerr)
  {
  }
  Logger(const std::string path, const std::string mode = "ae")
    : ofs(path, openmode(mode))
    , use_cerr(contains(mode, "e"))
  {
  }
  ~Logger()
  {
    ofs.close();
  }
  template<class T>
  inline Logger& operator<<(const T& x)
  {
    if(use_cerr) std::cerr << x;
    ofs << x;
    return *this;
  }
  Logger& operator<<(std::ostream& (*io)(std::ostream&))
  {
    if(use_cerr) io(std::cerr);
    io(ofs);
    return *this;
  }
private:
  template<typename T>
  inline bool contains(const std::string& str, const T& c)
  {
    return str.find(c) != std::string::npos;
  }
  inline std::ios_base::openmode openmode(const bool append)
  {
    return (append ? std::ios_base::app : std::ios_base::trunc) | std::ios_base::out;
  }
  inline std::ios_base::openmode openmode(const std::string& mode)
  {
    return openmode(contains(mode, 'a'));
  }
  std::ofstream ofs;
  bool use_cerr;
};

} // namespace arona

#endif // ARONA_LOGGER_H_
