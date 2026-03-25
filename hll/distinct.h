#pragma once

#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>

namespace sketch {

class DistinctSketch {
public:
  struct Parameters {
    uint64_t memory_limit_bytes;
  };

  DistinctSketch();

  DistinctSketch(Parameters params);

  void Append(int64_t value);

  double Estimate() const;

private:
  uint64_t A_;
  uint64_t B_;
  std::vector<uint8_t> min_hash_;
  uint64_t k_;
};

}  // namespace sketch