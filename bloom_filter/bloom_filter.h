#pragma once

#include <cstdint>
#include <vector>

namespace sketch {

class BloomFilter {
 public:
  using ElementType = int64_t;

  struct Parameters {
    uint64_t array_size;
    uint64_t hash_func_count;
  };

  explicit BloomFilter(Parameters params);

  void Add(const ElementType& elem);

  bool Estimate(const ElementType& elem) const;
 private:
  std::vector<bool> b_;
  std::vector<std::pair<uint64_t, uint64_t>> h_;
};

}  // namespace sketch
