#ifndef ARONA_STATIC_HELPER_H_
#define ARONA_STATIC_HELPER_H_

#include<cstddef>
#include<utility>
#include<type_traits>
#include<tuple>

namespace arona {

template<class ... Args>
using void_t = void;

using std::enable_if;

template<bool Condition, class Type = void>
using enable_if_t = typename enable_if<Condition, Type>::type;

template<class Default, class AlwaysVoid, template <class ...> class Op, class ... Args>
struct detected_impl
{
  using value_t = std::false_type;
  using type = Default;
};

template<class Default, template <class ...> class Op, class ... Args>
struct detected_impl <Default, void_t<Op<Args ...>>, Op, Args ...>
{
  using value_t = std::true_type;
  using type = Op<Args ...>;
};

template<template <class ...> class Op, class ... Args>
using is_detected = typename detected_impl<void, void, Op, Args ...>::value_t;

template<template <class ...> class Op, class ... Args>
using is_detected_t = typename detected_impl<void, void, Op, Args ...>::type;

template<std::size_t ... Indices>
struct index_sequence {};

template<std::size_t N, std::size_t ... Indices>
struct make_index_sequence_impl : make_index_sequence_impl<N - 1, N - 1, Indices ...> {};

template<std::size_t ... Indices>
struct make_index_sequence_impl<0, Indices ...> : index_sequence<Indices ...> {};

template<std::size_t N>
using make_index_sequence = make_index_sequence_impl<N>;

template<class ... Types>
using index_sequence_for = make_index_sequence_impl<sizeof ... (Types)>;

template<std::size_t Index, class ... Types>
using element_of = std::tuple_element<Index, std::tuple<Types ...>>;

template<std::size_t Index, class ... Types>
using element_of_t = typename element_of<Index, Types ...>::type;

}

#endif // ARONA_STATIC_HELPER_H_