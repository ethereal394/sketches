#pragma once

#include <cstdint>
#include <cstring>
#include <random>
#include <vector>
#include <random>

namespace sketch {

class SecondMomentSketch {
 public:
  struct Parameters {
    uint64_t seed;
  };

  explicit SecondMomentSketch(Parameters params);

  void Add(int64_t value);

  int64_t Estimate() const;

  std::vector<uint8_t> Serialize() const;

  static SecondMomentSketch Deserialize(const std::vector<uint8_t>& bytes);

private:
  uint64_t seed_;
  std::mt19937_64 rnd_;
  uint64_t a_;
  uint64_t b_;
  uint64_t c_;
  uint64_t d_;
  int64_t t_;
  const int64_t mod_ = 1'000'000'007;
};

}  // namespace sketch
