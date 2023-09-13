#ifndef ARONA_RANDOM_H_
#define ARONA_RANDOM_H_

#include<cstddef>
#include<random>
#include<vector>

namespace arona {

class Random
{
public:
  using RNG = std::mt19937;
  static RNG& rng() { static RNG rng_; return rng_; }
  static void seed(std::size_t seed) { rng().seed(seed); }
  static float uniform() { return std::uniform_real_distribution<float>{0.0, 1.0}(rng()); }
  static float uniform_real(float l, float h) { return std::uniform_real_distribution<float>{l, h}(rng()); }
  static int uniform_int(int l, int h) { return std::uniform_int_distribution<int>{l, h}(rng()); }
  static float normal(float m, float s) { return std::normal_distribution<float>{m, s}(rng()); }
  static bool bernoulli(float p) { return uniform() < p; }

  static std::size_t choice(std::size_t n)
  {
    return uniform_int(0, n - 1);
  }

  template<class T>
  static std::size_t choice(const T& probs)
  {
    return std::discrete_distribution<typename T::value_type>{probs.begin(), probs.end()}(rng());
  }

  template<class T, class U>
  static typename U::value_type choice(const T& probs, const U& values)
  {
    assert(probs.size() == values.size());
    std::size_t index = choice(probs);
    return values[index];
  }

  static std::vector<std::size_t> permutation(std::size_t n)
  {
    std::vector<std::size_t> result(n);
    std::iota(result.begin(), result.end(), 0ul);
    std::shuffle(result.begin(), result.end(), rng());
    return result;
  }
};

} // namespace arona

#endif // ARONA_RANDOM_H_