#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace sketch {

class MunroPatersonSketch {
 public:
  using ElementType = int64_t;

  struct Parameters {
    uint64_t k;
  };

  MunroPatersonSketch() = default;

  explicit MunroPatersonSketch(Parameters params);

  void Add(ElementType value);

  void Finalize();

  // expected 1-indexing (for example, min value has k = 1)
  std::pair<ElementType, ElementType> KthRange(uint64_t kth) const;

private:
  uint64_t k_;
  std::vector<std::pair<std::vector<ElementType>, uint64_t>> s_;
};

}  // namespace sketch
