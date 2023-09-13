#ifndef ARONA_FORMAT_H_
#define ARONA_FORMAT_H_

#include<cstdio>
#include<string>

namespace arona {

class Format
{
public:
  std::string fmt;
  
  Format() = default;
  Format(const std::string& fmt) : fmt(fmt) {}
  Format(const char* fmt) : fmt(fmt) {}
  Format(const Format&) = default;
  Format(Format&&) = default;

  template<class ... Args>
  std::string operator()(Args ... args)
  {
    int n = std::snprintf(nullptr, 0, fmt.c_str(), convert(args) ...);
    char buffer[n];
    std::snprintf(buffer, n + 1, fmt.c_str(), convert(args) ...);
    return buffer;
  }
private:
  template<class T> T convert(const T& x) { return x; }
  const char* convert(const std::string& x) { return x.c_str(); }
  const char* convert(const bool& x) { return x ? "true" : "false"; }
};

} // namespace arona
  
#endif // ARONA_FORMAT_H_
