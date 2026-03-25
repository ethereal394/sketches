#include "count_min.h"
#include <random>

namespace sketch {

CountMinSketch::CountMinSketch(Parameters params) {
  count_.resize(params.buffers_count, std::vector<CounterType>(params.buffer_size, 0));
  h_.resize(params.buffers_count);
  std::mt19937_64 rnd(1337);
  for (size_t i = 0; i < count_.size(); ++i) {
    h_[i].first = rnd();
    if (h_[i].first & 1) {
      ++h_[i].first;
    }
    h_[i].second = rnd();
  }
}

void CountMinSketch::Add(const ElementType& elem, CounterType weight) {
  for (size_t i = 0; i < count_.size(); ++i) {
    count_[i][(h_[i].first * static_cast<uint64_t>(elem - std::numeric_limits<ElementType>::min()) + h_[i].second) % count_[i].size()] += weight;
  }
}

CountMinSketch::CounterType CountMinSketch::Estimate(const ElementType& elem) const {
  CounterType min = std::numeric_limits<CounterType>::max();
  for (size_t i = 0; i < count_.size(); ++i) {
    min = std::min(min, count_[i][(h_[i].first * static_cast<uint64_t>(elem - std::numeric_limits<ElementType>::min()) + h_[i].second) % count_[i].size()]);
  }
  return min;
}

}  // namespace sketch