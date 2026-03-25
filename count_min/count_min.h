#pragma once

#include <cstdint>
#include <vector>

namespace sketch {

class CountMinSketch {
 public:
  using ElementType = int64_t;
  using CounterType = int64_t;

  struct Parameters {
    uint64_t buffers_count;
    uint64_t buffer_size;
  };

  explicit CountMinSketch(Parameters params);

  void Add(const ElementType& elem, CounterType weight);

  CounterType Estimate(const ElementType& elem) const;
 private:
  std::vector<std::vector<CounterType>> count_;
  std::vector<std::pair<uint64_t, uint64_t>> h_;
};

}  // namespace sketch
