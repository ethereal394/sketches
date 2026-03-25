#pragma once

#include <cstdint>
#include <cstring>
#include <random>
#include <vector>

namespace sketch {

class ReservoirSampling {
 public:
  struct Parameters {
    uint64_t k;
    uint64_t seed;
  };

  ReservoirSampling() = default;

  explicit ReservoirSampling(Parameters params);

  void Add(int64_t value);

  std::vector<int64_t> Sample() const;

 private:
  uint64_t cnt_ = 0;
  uint64_t k_;
  std::vector<int64_t> sample_;
  std::mt19937 rnd_;
};

}  // namespace sketch
