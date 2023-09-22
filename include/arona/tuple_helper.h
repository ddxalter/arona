#ifndef ARONA_TUPLE_HELPER_H_
#define ARONA_TUPLE_HELPER_H_

#include<cstddef>
#include<tuple>
#include<ostream>
#include<istream>

#include"arona/static_helper.h"

namespace arona {

template<std::size_t N = 0, class Functor, class ... ElementTypes>
auto for_each(std::tuple<ElementTypes ...>& t, Functor&& functor)
-> enable_if_t<N == sizeof ... (ElementTypes), void> {}

template<std::size_t N = 0, class Functor, class ... ElementTypes>
auto for_each(std::tuple<ElementTypes ...>& t, Functor&& functor)
-> enable_if_t<N != sizeof ... (ElementTypes), void>
{
  functor(std::get<N>(t));
  for_each<N + 1>(t, std::forward<Functor>(functor));
}

template<std::size_t N = 0, class Functor, class ... ElementTypes>
auto for_each(const std::tuple<ElementTypes ...>& t, Functor&& functor)
-> enable_if_t<N == sizeof ... (ElementTypes), void> {}

template<std::size_t N = 0, class Functor, class ... ElementTypes>
auto for_each(const std::tuple<ElementTypes ...>& t, Functor&& functor)
-> enable_if_t<N != sizeof ... (ElementTypes), void>
{
  functor(std::get<N>(t));
  for_each<N + 1>(t, std::forward<Functor>(functor));
}

template<std::size_t N, class ... ElementTypes>
inline auto tuple_to_stream(const std::tuple<ElementTypes ...>& t, std::ostream& stream, const char sep = ' ')
  -> enable_if_t<N == sizeof ... (ElementTypes), void> {}

template<std::size_t N = 0, class ... ElementTypes>
inline auto tuple_to_stream(const std::tuple<ElementTypes ...>& t, std::ostream& stream, const char sep = ' ')
  -> enable_if_t<N != sizeof ... (ElementTypes), void>
{
  (N > 0 ? stream << sep : stream) << std::get<N>(t);
  tuple_to_stream<N + 1>(t, stream, sep);
}

template<std::size_t N, class ... ElementTypes>
inline auto tuple_from_stream(std::tuple<ElementTypes ...>& t, std::istream& stream)
  -> enable_if_t<N == sizeof ... (ElementTypes), void> {}

template<std::size_t N = 0, class ... ElementTypes>
inline auto tuple_from_stream(std::tuple<ElementTypes ...>& t, std::istream& stream)
  -> enable_if_t<N != sizeof ... (ElementTypes), void>
{
  stream >> std::get<N>(t);
  tuple_from_stream<N + 1>(t, stream);
}

} // namespace arona

#endif // ARONA_TUPLE_HELPER_H_
