#ifndef ARONA_DATAFRAME_H_
#define ARONA_DATAFRAME_H_

#include<cstddef>
#include<vector>
#include<tuple>
#include<iostream>
#include<sstream>
#include<type_traits>

#include"arona/static_helper.h"
#include"arona/tuple_helper.h"

namespace arona {

template<class ... Args>
class DataFrame
{
public:
  using RowType = std::tuple<Args ...>;
  using TableType = std::vector<RowType>;

  std::size_t size() const noexcept
  {
    return table_.size();
  }
  RowType& push(const RowType& row)
  {
    table_.emplace_back(row);
    return table_.back();
  }
  RowType pop()
  {
    RowType row = table_.back();
    table_.pop_back();
    return row;
  }
  RowType& operator[](std::size_t i)
  {
    return table_[i];
  }
  const RowType& operator[](std::size_t i) const
  {
    return table_[i];
  }
  std::ostream& dump_csv(std::ostream& stream, const char sep = ' ') const
  {
    for(std::size_t i = 0; i < table_.size(); ++i)
    {
      tuple_to_stream(table_[i], stream, sep);
      stream << '\n';
    }
    stream.flush();
    return stream;
  }
  std::istream& read_csv(std::istream& stream, const char sep = ' ')
  {
    std::string line;
    while(std::getline(stream, line))
    {
      if(sep != ' ') std::replace(line.begin(), line.end(), sep, ' ');
      std::istringstream iss{line};
      RowType row;
      tuple_from_stream(row, iss);
      push(row);
    }
    return stream;
  }
private:
  TableType table_;
};

template<class ... Df1Types, class ... Df2Types>
inline auto merge(const DataFrame<Df1Types ...>& df1, const DataFrame<Df2Types ...>& df2)
  -> DataFrame<Df1Types ..., Df2Types ...>
{
  DataFrame<Df1Types ..., Df2Types ...> df;
  for(std::size_t i = 0; i < df1.size(); ++i)
  {
    df.push(std::tuple_cat(df1[i], df2[i]));
  }
  return df;
}

template<std::size_t ... ColumnIndices, class ... SrcDfTypes>
inline auto extract(const DataFrame<SrcDfTypes ...>& src)
  -> DataFrame<element_of_t<ColumnIndices, SrcDfTypes ...> ...>
{
  DataFrame<element_of_t<ColumnIndices, SrcDfTypes ...> ...> df;
  for(std::size_t i = 0; i < src.size(); ++i)
  {
    df.push({std::get<ColumnIndices>(src[i]) ...});
  }
  return df;
}

template<class ... DfTypes>
inline auto concat(const DataFrame<DfTypes ...>& df1, const DataFrame<DfTypes ...>& df2)
  -> DataFrame<DfTypes ...>
{
  DataFrame<DfTypes ...> df;
  for(std::size_t i = 0; i < df1.size(); ++i) df.push(df1[i]);
  for(std::size_t i = 0; i < df2.size(); ++i) df.push(df2[i]);
  return df;
}

} // namespace arona

#endif // ARONA_DATAFRAME_H_