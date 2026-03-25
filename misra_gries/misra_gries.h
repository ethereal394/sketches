#pragma once

#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <vector>

namespace sketch {

class MisraGriesSketch {
 public:
  using ElementType = int64_t;
  using CounterType = uint64_t;

  struct Parameters {
    uint64_t memory_limit_bytes;
  };

  MisraGriesSketch() = default;

  explicit MisraGriesSketch(Parameters params);

  void Append(const ElementType& value);

  std::unordered_map<ElementType, CounterType> Candidates() const;

  CounterType Estimate(const ElementType& value);

 private:
  std::unordered_map<ElementType, CounterType> count_;
  uint64_t k_;
};

}  // namespace sketch
