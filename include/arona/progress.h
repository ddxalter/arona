#ifndef ARONA_PROGRESS_H_
#define ARONA_PROGRESS_H_

#include<iostream>

namespace arona {

struct Progress
{
  Progress(const int i, const int n, const int w = 100)
    : w(w), f(i * w / (n - 1)), r(f != (i - 1) * w / (n - 1)) {}
  const int w; // width
  const int f; // fill
  const bool r; // need reprint or not
};

inline std::ostream& operator << (std::ostream& stream, Progress&& p)
{
  if(p.r)
  {
    stream << "\r[";
    for(int i = 0; i < p.f; ++i)
    {
      stream << "=";
    }
    for(int i = p.f; i < p.w; ++i)
    {
      stream << " ";
    }
    stream << "] " << p.f * 100 / p.w << "%";
    if(p.f == 100)
    {
      stream << "\n";
    }
    std::flush(stream);
  }
  return stream;
}

} // namespace arona

#endif // ARONA_PROGRESS_H_
