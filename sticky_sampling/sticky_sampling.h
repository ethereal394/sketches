#pragma once

#include <cstdint>
#include <unordered_map>
#include <random>

namespace sketch {

class StickySamplingSketch {
 public:
  using ElementType = int64_t;
  using CounterType = uint64_t;

  struct Parameters {
    double s;
    double eps;
    double delta;
  };

  explicit StickySamplingSketch(Parameters params);

  void Add(const ElementType& elem);

  CounterType Estimate(const ElementType& elem) const;

 private:
  std::unordered_map<ElementType, CounterType> cnt_;
  int r_;
  int t_;
  int now_;
  std::mt19937 rnd_;
};

}  // namespace sketch
