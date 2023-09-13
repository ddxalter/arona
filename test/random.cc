#include"test/test.h"

#include"arona/random.h"
#include<vector>
#include<iostream>
#include<numeric>

bool test_uniform(std::size_t n_samples)
{
  bool result = true;
  for(std::size_t i = 0; i < n_samples; ++i)
  {
    float x = arona::Random::uniform();
    result = result && (0.f <= x && x < 1.f);
  }
  return result;
}

bool test_uniform_real(float l, float h, std::size_t n_samples)
{
  bool result = true;
  for(std::size_t i = 0; i < n_samples; ++i)
  {
    float x = arona::Random::uniform_real(l, h);
    result = result && (l <= x && x < h);
  }
  return result;
}

bool test_uniform_int(int l, int h, std::size_t n_samples)
{
  bool result = true;
  for(std::size_t i = 0; i < n_samples; ++i)
  {
    float x = arona::Random::uniform_int(l, h);
    result = result && (l <= x && x <= h);
  }
  return result;
}

bool test_normal(float m, float s, std::size_t n_samples)
{
  std::vector<float> samples(n_samples);
  float sample_mean = 0;
  float sample_stddev = 0;
  for(std::size_t i = 0; i < n_samples; ++i)
  {
    sample_mean += (samples[i] = arona::Random::normal(m, s));
  }
  sample_mean = sample_mean / static_cast<float>(n_samples);
  for(std::size_t i = 0; i < n_samples; ++i)
  {
    sample_stddev += (samples[i] - sample_mean) * (samples[i] - sample_mean);
  }   
  sample_stddev = std::sqrt(sample_stddev / static_cast<float>(n_samples));
  const float epsilon = 2.0f * s / std::sqrt(static_cast<float>(n_samples));
  return std::abs(sample_mean - m) < epsilon && std::abs(sample_stddev - s) < epsilon;
}

bool test_choice(std::size_t n_dist, std::size_t n_samples, float epsilon)
{
  bool result = true;
  std::vector<float> dist(n_dist);
  double sum = 0;
  for(auto& p : dist) sum += (p = arona::Random::uniform());
  for(auto& p : dist) p /= sum;

  std::vector<std::size_t> indices(n_dist);
  std::iota(indices.begin(), indices.end(), 0);
  std::vector<int> counts(n_dist, 0);

  for(int i = 0; i < n_samples; ++i)
  {
    counts[arona::Random::choice(dist, indices)] += 1;
  }

  for(int i = 0; i < n_dist; ++i)
  {
    result = result && (std::abs(dist[i] - static_cast<float>(counts[i]) / static_cast<float>(n_samples)) < epsilon);
  }
  return result;
}

void test_random()
{
  // test uniform() with n_samples
  test_case("arona::Random::uniform()", test_uniform(1000));
  // test uniform_real() with n_sample
  test_case("arona::Random::uniform_real(0, 1)", test_uniform_real(0, 1, 1000));
  test_case("arona::Random::uniform_real(-1, 0)", test_uniform_real(-1, 0, 1000));
  test_case("arona::Random::uniform_real(-1, 1)", test_uniform_real(-1, 1, 1000));
  // test uniform_int() with n_sample
  test_case("arona::Random::uniform_int(0, 1)", test_uniform_int(0, 1, 1000));
  test_case("arona::Random::uniform_int(-1, 0)", test_uniform_int(-1, 0, 1000));
  test_case("arona::Random::uniform_int(-1, 1)", test_uniform_int(-1, 1, 1000));
  // test normal() with n_sample
  test_case("arona::Random::normal(0, 1)", test_normal(0, 1, 1000));
  test_case("arona::Random::normal(1, 0.1)", test_normal(1, 0.1, 1000));
  test_case("arona::Random::normal(-1, 0.1)", test_normal(-1, 0.1, 1000));
  // test choice(probs, values) with n_categories, n_samples, epsilon
  test_case("arona::Random::choice(probs, values)", test_choice(10, 10000, 0.01));
}