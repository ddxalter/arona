#ifndef ARONA_STRING_HELPER_H_
#define ARONA_STRING_HELPER_H_

#include<string>
#include<vector>

namespace arona {

inline std::vector<std::string> split(const std::string& str, const std::string& sep) noexcept
{
  std::vector<std::string> result;
  std::string::size_type pos = 0;
  std::string::size_type found = 0;
  while((found = str.find(sep, pos)) != std::string::npos)
  {
    result.emplace_back(str.substr(pos, found - pos));
    pos = found + sep.length();
  }
  result.emplace_back(str.substr(pos));
  return result;
}

inline std::vector<std::string> split_skipping(const std::string& from_str, const std::string& by_chars) noexcept
{
  std::vector<std::string> result;
  std::string::size_type pos = 0;
  std::string::size_type found = 0;
  while((pos = from_str.find_first_not_of(by_chars, found)) != std::string::npos &&
        (found = from_str.find_first_of(by_chars, pos)) != std::string::npos)
  {
    result.emplace_back(from_str.substr(pos, found - pos));
  }
  if(pos != std::string::npos)
  {
    result.emplace_back(from_str.substr(pos));
  }
  return result;
}

inline std::string ltrim_all(const std::string& from_str, const std::string& by_chars) noexcept
{
  std::string::size_type pos = from_str.find_first_not_of(by_chars);
  return pos != std::string::npos ? from_str.substr(pos) : "";
}

inline std::string rtrim_all(const std::string& from_str, const std::string& by_chars) noexcept
{
  std::string::size_type pos = from_str.find_last_not_of(by_chars);
  return pos != std::string::npos ? from_str.substr(0, pos + 1) : "";
}

inline std::string trim_all(const std::string& from_str, const std::string& by_chars) noexcept
{
  std::string::size_type pos = from_str.find_first_not_of(by_chars);
  return pos != std::string::npos ? from_str.substr(pos, from_str.find_last_not_of(by_chars) - pos + 1) : "";
}

template<class T>
inline std::string join(const std::string& sep, const T& strs) noexcept
{
  std::string result;
  for(std::size_t i = 0; i < strs.size(); ++i)
  {
    result += (i != 0 ? sep : "") + strs[i];
  }
  return result;
}

template<class T>
inline T to_value(const std::string& s) noexcept;

template<>
inline int to_value<int>(const std::string& s) noexcept
{
  return std::stoi(s);
}
template<>
inline long long to_value<long long>(const std::string& s) noexcept
{
  return std::stoll(s);
}
template<>
inline unsigned long to_value<unsigned long>(const std::string& s) noexcept
{
  return std::stoul(s);
}
template<>
inline unsigned long long to_value<unsigned long long>(const std::string& s) noexcept
{
  return std::stoull(s);
}
template<>
inline float to_value<float>(const std::string& s) noexcept
{
  return std::stof(s);
}
template<>
inline double to_value<double>(const std::string& s) noexcept
{
  return std::stod(s);
}
template<>
inline std::string to_value<std::string>(const std::string& s) noexcept
{
  return s;
}
template<>
inline const char* to_value<const char*>(const std::string& s) noexcept
{
  return s.c_str();
}
template<>
inline bool to_value<bool>(const std::string& s) noexcept
{
  return s == "true";
}

} // namespace arona

#endif // ARONA_STRING_HELPER_H_
