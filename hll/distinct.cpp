#include "distinct.h"
#include <bit>

namespace sketch {

DistinctSketch::DistinctSketch() {
  std::mt19937_64 rnd(228);
  A_ = rnd();
  if (~A_ & 1) {
    ++A_;
  }
  B_ = rnd();
}

DistinctSketch::DistinctSketch(Parameters params) : DistinctSketch() {
  k_ = (63 - std::countl_zero(params.memory_limit_bytes));
  min_hash_.resize(1ull << k_, 0);
}

void DistinctSketch::Append(int64_t value) {
  uint64_t h = A_ * static_cast<uint64_t>(value - std::numeric_limits<int64_t>::min()) + B_;
  uint64_t b = h & ((1 << k_) - 1);
  uint64_t x = h >> k_;
  min_hash_[b] = std::max(min_hash_[b], static_cast<uint8_t>(1 + std::countl_zero(x) - k_));
}

double DistinctSketch::Estimate() const {
  double s = 0;
  int cnt = 0;
  for (auto i : min_hash_) {
    if (i != 0) {
      s += 1.0 / (1ull << (i - 1));
      ++cnt;
    }
  }
  if (cnt == 0) {
    return 0;
  }
  return cnt * cnt / s;
}

}  // namespace sketch